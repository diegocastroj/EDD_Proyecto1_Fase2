#ifndef ARBOL_AVL_H
#define ARBOL_AVL_H

#include "NodoAVL.h"
#include <string>

class ArbolAVL {
private:
    NodoAVL* raiz;

    // Métodos utilitarios
    int obtenerAltura(NodoAVL* nodo);
    int obtenerBalance(NodoAVL* nodo);
    
    // Rotaciones
    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    
    // Operaciones recursivas
    NodoAVL* insertar(NodoAVL* nodo, Lote* lote);
    NodoAVL* buscar(NodoAVL* nodo, std::string codigo_lote);
    void inOrder(NodoAVL* nodo);
    void destruirArbol(NodoAVL* nodo);

public:
    ArbolAVL();
    ~ArbolAVL();
    
    void insertarLote(Lote* lote);
    Lote* buscarLote(std::string codigo_lote);
    void imprimirInOrder();
    
    // Getter necesario para reportes de Graphviz (Opción 6.2)
    NodoAVL* getRaiz();
};

#endif
