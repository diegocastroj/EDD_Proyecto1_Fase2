#include "../include/ListaEstados.h"

ListaEstados::ListaEstados() : cabeza(nullptr) {}

ListaEstados::~ListaEstados() {
    NodoEstado* actual = cabeza;
    while (actual != nullptr) {
        NodoEstado* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaEstados::insertar(std::string estado, std::string timestamp) {
    NodoEstado* nuevo = new NodoEstado(estado, timestamp);
    if (!cabeza) {
        cabeza = nuevo;
    } else {
        NodoEstado* actual = cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void ListaEstados::imprimirHistorial() const {
    NodoEstado* actual = cabeza;
    while (actual) {
        std::cout << "[" << actual->timestamp << "] " << actual->estado << std::endl;
        actual = actual->siguiente;
    }
}