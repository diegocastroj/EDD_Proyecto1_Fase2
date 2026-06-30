#ifndef LISTA_FINCAS_H
#define LISTA_FINCAS_H

#include <string>
#include <iostream>

struct NodoFinca {
    std::string codigo;
    std::string nombre;
    std::string region;
    std::string propietario;
    NodoFinca* siguiente;

    NodoFinca(std::string cod, std::string nom, std::string reg, std::string prop) 
        : codigo(cod), nombre(nom), region(reg), propietario(prop), siguiente(nullptr) {}
};

class ListaFincas {
private:
    NodoFinca* cabeza;
public:
    ListaFincas();
    ~ListaFincas();
    
    bool insertar(std::string codigo, std::string nombre, std::string region, std::string propietario);
    bool existeFinca(std::string codigo);
    std::string obtenerNombreFinca(std::string codigo);
    std::string obtenerRegion(std::string codigo);
    void mostrarFincas();
};

#endif