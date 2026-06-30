#ifndef NODO_AVL_H
#define NODO_AVL_H

#include "Lote.h"

class NodoAVL {
public:
    Lote* lote;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(Lote* l) {
        lote = l;
        izquierdo = nullptr;
        derecho = nullptr;
        altura = 1; // Un nodo nuevo se inserta inicialmente como hoja con altura 1
    }
    
    ~NodoAVL() {
        delete lote; // Liberamos la memoria del lote cuando se destruya el nodo
    }
};

#endif