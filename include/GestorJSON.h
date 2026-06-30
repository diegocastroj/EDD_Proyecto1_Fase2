#ifndef GESTOR_JSON_H
#define GESTOR_JSON_H

#include <string>
#include "ArbolB.h"
#include "ListaFincas.h"

class GestorJSON {
private:
    std::string extraerValorString(const std::string& contenido, size_t& pos, const std::string& clave);
    int extraerValorInt(const std::string& contenido, size_t& pos, const std::string& clave);

public:
    void cargarDatos(const std::string& rutaArchivo, ArbolB* arbolB, ListaFincas* listaFincas);
};

#endif