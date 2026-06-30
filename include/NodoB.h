#ifndef NODOB_H
#define NODOB_H

#include <string>
#include "ArbolAVL.h"

class NodoB {
public:
    std::string* fechas;        // Arreglo de claves (fechas YYYY-MM-DD)
    ArbolAVL** arboles_avl;     // Arreglo de punteros a los árboles AVL
    NodoB** hijos;              // Arreglo de punteros a hijos
    int num_claves;             // Cantidad actual de claves
    bool hoja;                  // Indica si es nodo hoja
    int MAX_CLAVES;             // Máximo de claves (6)

    NodoB(bool es_hoja);
    ~NodoB();

    void recorrerInOrder();
    ArbolAVL* buscar(std::string fecha);
    void insertarNoLleno(std::string fecha, Lote* lote);
    void dividirHijo(int i, NodoB* y);
};

#endif