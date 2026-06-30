#include "../include/NodoB.h"
#include <iostream>

NodoB::NodoB(bool es_hoja) {
    MAX_CLAVES = 6;
    hoja = es_hoja;
    num_claves = 0;
    
    // Asignamos memoria (MAX_CLAVES + 1 para manejar el desbordamiento antes de dividir)
    fechas = new std::string[MAX_CLAVES + 1];
    arboles_avl = new ArbolAVL*[MAX_CLAVES + 1];
    hijos = new NodoB*[MAX_CLAVES + 2];

    for (int i = 0; i < MAX_CLAVES + 2; i++) {
        hijos[i] = nullptr;
    }
}

NodoB::~NodoB() {
    for (int i = 0; i < num_claves; i++) {
        delete arboles_avl[i];
    }
    delete[] fechas;
    delete[] arboles_avl;
    delete[] hijos;
}

ArbolAVL* NodoB::buscar(std::string fecha) {
    int i = 0;
    while (i < num_claves && fecha > fechas[i])
        i++;

    if (i < num_claves && fechas[i] == fecha)
        return arboles_avl[i]; // Retornamos el AVL de esa fecha [cite: 47]

    if (hoja)
        return nullptr;

    return hijos[i]->buscar(fecha);
}

void NodoB::insertarNoLleno(std::string fecha, Lote* lote) {
    int i = num_claves - 1;

    if (hoja) {
        // Encontrar la ubicación y mover las llaves mayores a la derecha
        while (i >= 0 && fechas[i] > fecha) {
            fechas[i + 1] = fechas[i];
            arboles_avl[i + 1] = arboles_avl[i];
            i--;
        }
        // Insertar la nueva fecha y su AVL
        fechas[i + 1] = fecha;
        arboles_avl[i + 1] = new ArbolAVL();
        arboles_avl[i + 1]->insertarLote(lote);
        num_claves++;
    } else {
        // Encontrar el hijo correspondiente
        while (i >= 0 && fechas[i] > fecha)
            i--;

        i++; // Bajamos por este hijo
        if (hijos[i]->num_claves == MAX_CLAVES) {
            dividirHijo(i, hijos[i]);

            if (fechas[i] < fecha)
                i++;
        }
        hijos[i]->insertarNoLleno(fecha, lote);
    }
}

void NodoB::dividirHijo(int i, NodoB* y) {
    NodoB* z = new NodoB(y->hoja);
    z->num_claves = 2; // Extraemos 2 claves (índices 4 y 5) 

    // Copiar claves 4 y 5 a z
    for (int j = 0; j < 2; j++) {
        z->fechas[j] = y->fechas[j + 4];
        z->arboles_avl[j] = y->arboles_avl[j + 4];
    }

    // Copiar hijos si no es hoja
    if (!y->hoja) {
        for (int j = 0; j < 3; j++) {
            z->hijos[j] = y->hijos[j + 4];
        }
    }

    y->num_claves = 3; // y se queda con las claves 0, 1 y 2 

    // Mover hijos en el nodo actual para insertar z
    for (int j = num_claves; j >= i + 1; j--) {
        hijos[j + 1] = hijos[j];
    }
    hijos[i + 1] = z;

    // Mover claves en el nodo actual para subir la clave central (índice 3)
    for (int j = num_claves - 1; j >= i; j--) {
        fechas[j + 1] = fechas[j];
        arboles_avl[j + 1] = arboles_avl[j];
    }

    fechas[i] = y->fechas[3];
    arboles_avl[i] = y->arboles_avl[3];
    num_claves++;
}

void NodoB::recorrerInOrder() {
    int i;
    for (i = 0; i < num_claves; i++) {
        if (!hoja)
            hijos[i]->recorrerInOrder();
        
        std::cout << "Fecha: " << fechas[i] << " -> Contiene lotes:\n";
        arboles_avl[i]->imprimirInOrder();
        std::cout << "---------------------------\n";
    }
    if (!hoja)
        hijos[i]->recorrerInOrder();
}