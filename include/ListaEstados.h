#ifndef LISTA_ESTADOS_H
#define LISTA_ESTADOS_H

#include <string>
#include <iostream>

struct NodoEstado {
    std::string estado;
    std::string timestamp;
    NodoEstado* siguiente;

    NodoEstado(std::string est, std::string ts) : estado(est), timestamp(ts), siguiente(nullptr) {}
};

class ListaEstados {
private:
    NodoEstado* cabeza;
public:
    ListaEstados();
    ~ListaEstados();
    void insertar(std::string estado, std::string timestamp);
    void imprimirHistorial() const;
};

#endif