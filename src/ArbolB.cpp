#include "../include/ArbolB.h"
#include <iostream>

ArbolB::ArbolB() {
    raiz = nullptr;
}

ArbolB::~ArbolB() {
    destruirSubarbol(raiz);
}

void ArbolB::destruirSubarbol(NodoB* nodo) {
    if (nodo != nullptr) {
        if (!nodo->hoja) {
            for (int i = 0; i <= nodo->num_claves; i++) {
                destruirSubarbol(nodo->hijos[i]);
            }
        }
        delete nodo;
    }
}

ArbolAVL* ArbolB::buscar(std::string fecha) {
    if (raiz == nullptr)
        return nullptr;
    return raiz->buscar(fecha);
}

void ArbolB::insertar(std::string fecha, Lote* lote) {
    if (raiz == nullptr) {
        raiz = new NodoB(true);
        raiz->fechas[0] = fecha;
        raiz->arboles_avl[0] = new ArbolAVL();
        raiz->arboles_avl[0]->insertarLote(lote);
        raiz->num_claves = 1;
    } else {
        // Si la fecha ya existe, solo insertamos el lote en el AVL [cite: 47, 50]
        ArbolAVL* avl_existente = buscar(fecha);
        if (avl_existente != nullptr) {
            avl_existente->insertarLote(lote);
            return;
        }

        // Si la raíz está llena, dividimos
        if (raiz->num_claves == raiz->MAX_CLAVES) {
            NodoB* s = new NodoB(false);
            s->hijos[0] = raiz;
            s->dividirHijo(0, raiz);

            int i = 0;
            if (s->fechas[0] < fecha)
                i++;

            s->hijos[i]->insertarNoLleno(fecha, lote);
            raiz = s;
        } else {
            raiz->insertarNoLleno(fecha, lote);
        }
    }
}

void ArbolB::recorrerInOrder() {
    if (raiz != nullptr)
        raiz->recorrerInOrder();
}

NodoB* ArbolB::getRaiz() {
    return raiz;
}