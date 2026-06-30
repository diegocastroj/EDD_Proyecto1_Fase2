#ifndef NODO_MERKLE_H
#define NODO_MERKLE_H

#include <string>

class NodoMerkle {
public:
    std::string hash;
    NodoMerkle* izquierdo;
    NodoMerkle* derecho;

    NodoMerkle(std::string h) {
        hash = h;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

#endif