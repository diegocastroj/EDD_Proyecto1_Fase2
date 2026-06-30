#include "../include/ArbolAVL.h"
#include <iostream>
#include <algorithm> // Solo para std::max, permitido en cálculos matemáticos básicos

ArbolAVL::ArbolAVL() {
    raiz = nullptr;
}

ArbolAVL::~ArbolAVL() {
    destruirArbol(raiz);
}

void ArbolAVL::destruirArbol(NodoAVL* nodo) {
    if (nodo != nullptr) {
        destruirArbol(nodo->izquierdo);
        destruirArbol(nodo->derecho);
        delete nodo;
    }
}

int ArbolAVL::obtenerAltura(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return nodo->altura;
}

int ArbolAVL::obtenerBalance(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierdo;
    NodoAVL* T2 = x->derecho;

    // Rotación
    x->derecho = y;
    y->izquierdo = T2;

    // Actualizar alturas
    y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return x;
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecho;
    NodoAVL* T2 = y->izquierdo;

    // Rotación
    y->izquierdo = x;
    x->derecho = T2;

    // Actualizar alturas
    x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
    y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

    return y;
}

NodoAVL* ArbolAVL::insertar(NodoAVL* nodo, Lote* lote) {
    // 1. Inserción normal de BST (comparando strings lexicográficamente)
    if (nodo == nullptr)
        return new NodoAVL(lote);

    if (lote->codigo_lote < nodo->lote->codigo_lote)
        nodo->izquierdo = insertar(nodo->izquierdo, lote);
    else if (lote->codigo_lote > nodo->lote->codigo_lote)
        nodo->derecho = insertar(nodo->derecho, lote);
    else
        return nodo; // Lotes con el mismo código no se permiten duplicados

    // 2. Actualizar altura
    nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

    // 3. Obtener el factor de balance
    int balance = obtenerBalance(nodo);

    // 4. Casos de rotación
    // Caso Left Left (LL)
    if (balance > 1 && lote->codigo_lote < nodo->izquierdo->lote->codigo_lote)
        return rotacionDerecha(nodo);

    // Caso Right Right (RR)
    if (balance < -1 && lote->codigo_lote > nodo->derecho->lote->codigo_lote)
        return rotacionIzquierda(nodo);

    // Caso Left Right (LR)
    if (balance > 1 && lote->codigo_lote > nodo->izquierdo->lote->codigo_lote) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    // Caso Right Left (RL)
    if (balance < -1 && lote->codigo_lote < nodo->derecho->lote->codigo_lote) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::insertarLote(Lote* lote) {
    raiz = insertar(raiz, lote);
}

NodoAVL* ArbolAVL::buscar(NodoAVL* nodo, std::string codigo_lote) {
    if (nodo == nullptr || nodo->lote->codigo_lote == codigo_lote)
        return nodo;

    if (nodo->lote->codigo_lote < codigo_lote)
        return buscar(nodo->derecho, codigo_lote);

    return buscar(nodo->izquierdo, codigo_lote);
}

Lote* ArbolAVL::buscarLote(std::string codigo_lote) {
    NodoAVL* resultado = buscar(raiz, codigo_lote);
    if (resultado != nullptr)
        return resultado->lote;
    return nullptr;
}

void ArbolAVL::inOrder(NodoAVL* nodo) {
    if (nodo != nullptr) {
        inOrder(nodo->izquierdo);
        std::cout << "Lote: " << nodo->lote->codigo_lote << " | Finca: " << nodo->lote->nombre_finca << "\n";
        inOrder(nodo->derecho);
    }
}

void ArbolAVL::imprimirInOrder() {
    inOrder(raiz);
}

NodoAVL* ArbolAVL::getRaiz() {
    return raiz;
}