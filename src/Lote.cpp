#include "../include/Lote.h"
#include <iostream>

Lote::Lote(std::string c_lote, std::string c_finca, std::string n_finca, int cant_sacos, std::string t_cafe) {
    codigo_lote = c_lote;
    codigo_finca = c_finca;
    nombre_finca = n_finca;
    sacos = cant_sacos;
    tipo_cafe = t_cafe;
    estado = "recibido"; 
    hash_certificado = ""; 
}

void Lote::avanzarEstado(std::string nuevo_estado, std::string timestamp) {
    estado = nuevo_estado;
    historial.insertar(nuevo_estado, timestamp);
}

void Lote::imprimirLote() const {
    std::cout << "LOTE: " << codigo_lote << "\n";
    std::cout << "Finca: " << nombre_finca << " (" << codigo_finca << ")\n";
    std::cout << "Sacos: " << sacos << "\n";
    std::cout << "Tipo de café: " << tipo_cafe << "\n";
    std::cout << "Estado actual: " << estado << "\n";
    std::cout << "Historial de estados:\n";
    historial.imprimirHistorial();
}