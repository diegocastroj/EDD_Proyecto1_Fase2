#ifndef ARBOL_MERKLE_H
#define ARBOL_MERKLE_H

#include "NodoMerkle.h"
#include <string>

class ArbolMerkle {
private:
    NodoMerkle* raiz;
    void destruirArbol(NodoMerkle* nodo);
    NodoMerkle* construirNivel(NodoMerkle** nodos, int cantidad);

public:
    ArbolMerkle();
    ~ArbolMerkle();
    
    void construirArbol(std::string* listaHashes, int cantidad);
    std::string obtenerHashRaiz();
    void mostrarRaiz();
};

#endif