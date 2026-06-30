#ifndef LOTE_H
#define LOTE_H

#include <string>
#include "ListaEstados.h"

class Lote {
public:
    std::string codigo_lote;      
    std::string codigo_finca;     
    std::string nombre_finca;     
    int sacos;                    
    std::string tipo_cafe;         
    std::string estado;            
    ListaEstados historial;        
    std::string hash_certificado;  

    // Constructor
    Lote(std::string c_lote, std::string c_finca, std::string n_finca, int cant_sacos, std::string t_cafe);
    
    // Métodos
    void avanzarEstado(std::string nuevo_estado, std::string timestamp);
    void imprimirLote() const;
};

#endif