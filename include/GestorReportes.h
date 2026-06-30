#ifndef GESTOR_REPORTES_H
#define GESTOR_REPORTES_H

#include "ArbolB.h"
#include "ArbolMerkle.h"
#include "Lote.h"
#include <string>

class GestorReportes {
private:
    void escribirNodoB(NodoB* nodo, std::ofstream& archivo, int& id);
    void escribirNodoAVL(NodoAVL* nodo, std::ofstream& archivo);
    int calcularFactorBalance(NodoAVL* nodo);
    int obtenerAltura(NodoAVL* nodo);

public:
    void graficarArbolB(ArbolB* arbol);
    void graficarAVL(ArbolAVL* arbol, std::string fecha);
    void graficarTrazabilidad(Lote* lote);
};

#endif