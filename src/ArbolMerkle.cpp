#include "../include/ArbolMerkle.h"
#include "../include/GeneradorHash.h"
#include <iostream>

ArbolMerkle::ArbolMerkle() : raiz(nullptr) {}

ArbolMerkle::~ArbolMerkle() {
    destruirArbol(raiz);
}

void ArbolMerkle::destruirArbol(NodoMerkle* nodo) {
    if (nodo != nullptr) {
        destruirArbol(nodo->izquierdo);
        destruirArbol(nodo->derecho);
        delete nodo;
    }
}

std::string ArbolMerkle::obtenerHashRaiz() {
    if (raiz == nullptr) return "Arbol Vacio";
    return raiz->hash;
}

void ArbolMerkle::mostrarRaiz() {
    std::cout << "Hash Raiz actual del Arbol de Merkle:\n" << obtenerHashRaiz() << "\n";
}

NodoMerkle* ArbolMerkle::construirNivel(NodoMerkle** nodos, int cantidad) {
    if (cantidad == 1) {
        return nodos[0];
    }

    int nueva_cantidad = (cantidad + 1) / 2; // Maneja cantidades impares automáticamente
    NodoMerkle** nuevos_nodos = new NodoMerkle*[nueva_cantidad];
    int indice = 0;

    for (int i = 0; i < cantidad; i += 2) {
        NodoMerkle* izq = nodos[i];
        NodoMerkle* der = nullptr;

        if (i + 1 < cantidad) {
            der = nodos[i + 1];
        } else {
            // Si es impar, la última hoja se duplica para hashear
            der = new NodoMerkle(izq->hash); 
        }

        std::string hash_combinado = GeneradorHash::generarHash(izq->hash + der->hash);
        NodoMerkle* padre = new NodoMerkle(hash_combinado);
        padre->izquierdo = izq;
        padre->derecho = der;

        nuevos_nodos[indice] = padre;
        indice++;
    }

    NodoMerkle* raiz_nivel = construirNivel(nuevos_nodos, nueva_cantidad);
    delete[] nuevos_nodos; // Liberamos el arreglo temporal de punteros
    
    return raiz_nivel;
}

void ArbolMerkle::construirArbol(std::string* listaHashes, int cantidad) {
    if (cantidad == 0) return;

    if (raiz != nullptr) {
        destruirArbol(raiz);
        raiz = nullptr;
    }

    // Crear las hojas base
    NodoMerkle** nodos_hoja = new NodoMerkle*[cantidad];
    for (int i = 0; i < cantidad; i++) {
        nodos_hoja[i] = new NodoMerkle(listaHashes[i]);
    }

    raiz = construirNivel(nodos_hoja, cantidad);
    delete[] nodos_hoja;
}