#include "../include/ListaFincas.h"

ListaFincas::ListaFincas() : cabeza(nullptr) {}

ListaFincas::~ListaFincas() {
    NodoFinca* actual = cabeza;
    while (actual != nullptr) {
        NodoFinca* sig = actual->siguiente;
        delete actual;
        actual = sig;
    }
}

bool ListaFincas::insertar(std::string codigo, std::string nombre, std::string region, std::string propietario) {
    if (existeFinca(codigo)) return false; // Evitar duplicados
    
    NodoFinca* nuevo = new NodoFinca(codigo, nombre, region, propietario);
    if (!cabeza) {
        cabeza = nuevo;
    } else {
        NodoFinca* actual = cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    return true;
}

bool ListaFincas::existeFinca(std::string codigo) {
    NodoFinca* actual = cabeza;
    while (actual) {
        if (actual->codigo == codigo) return true;
        actual = actual->siguiente;
    }
    return false;
}

std::string ListaFincas::obtenerNombreFinca(std::string codigo) {
    NodoFinca* actual = cabeza;
    while (actual) {
        if (actual->codigo == codigo) return actual->nombre;
        actual = actual->siguiente;
    }
    return "Desconocida";
}

void ListaFincas::mostrarFincas() {
    NodoFinca* actual = cabeza;
    while (actual) {
        std::cout << "- " << actual->codigo << ": " << actual->nombre << " (" << actual->propietario << ")\n";
        actual = actual->siguiente;
    }
}