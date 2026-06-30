#ifndef ARBOL_B_H
#define ARBOL_B_H

#include "NodoB.h"
#include <string>

class ArbolB {
private:
    NodoB* raiz;
    void destruirSubarbol(NodoB* nodo);

public:
    ArbolB();
    ~ArbolB();

    void insertar(std::string fecha, Lote* lote);
    ArbolAVL* buscar(std::string fecha);
    void recorrerInOrder();
    
    NodoB* getRaiz(); // Lo necesitaremos para los reportes de Graphviz
};

#endif