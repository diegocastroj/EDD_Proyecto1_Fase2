#include "../include/GestorJSON.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Analizador real de cadenas para valores entre comillas
std::string GestorJSON::extraerValorString(const std::string& contenido, size_t& pos, const std::string& clave) {
    size_t pClave = contenido.find("\"" + clave + "\"", pos);
    if (pClave == std::string::npos) return "";
    
    size_t pDosPuntos = contenido.find(":", pClave);
    size_t pComilla1 = contenido.find("\"", pDosPuntos);
    size_t pComilla2 = contenido.find("\"", pComilla1 + 1);
    
    pos = pComilla2 + 1; // Avanzar la posición de búsqueda
    return contenido.substr(pComilla1 + 1, pComilla2 - pComilla1 - 1);
}

// Analizador real para extraer valores numéricos
int GestorJSON::extraerValorInt(const std::string& contenido, size_t& pos, const std::string& clave) {
    size_t pClave = contenido.find("\"" + clave + "\"", pos);
    if (pClave == std::string::npos) return 0;
    
    size_t pDosPuntos = contenido.find(":", pClave);
    size_t pInicioNum = contenido.find_first_of("-0123456789", pDosPuntos);
    size_t pFinNum = contenido.find_first_not_of("0123456789", pInicioNum);
    
    pos = pFinNum;
    std::string numStr = contenido.substr(pInicioNum, pFinNum - pInicioNum);
    try {
        return std::stoi(numStr);
    } catch (...) {
        return 0;
    }
}

void GestorJSON::cargarDatos(const std::string& rutaArchivo, ArbolB* arbolB, ListaFincas* listaFincas) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << rutaArchivo << "\n";
        return;
    }

    // Leer todo el archivo en un string
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string contenido = buffer.str();
    archivo.close();

    std::cout << "Analizando archivo JSON...\n";

    // 1. Parsear Fincas (Lectura real del bloque "fincas")
    size_t posFincas = contenido.find("\"fincas\"");
    size_t posEntregas = contenido.find("\"entregas\"");
    
    if (posFincas != std::string::npos) {
        size_t cursor = posFincas;
        size_t limiteFincas = (posEntregas != std::string::npos) ? posEntregas : contenido.length();
        
        while (cursor < limiteFincas) {
            std::string cod = extraerValorString(contenido, cursor, "codigo");
            if (cod.empty() || cursor >= limiteFincas) break;
            
            std::string nom = extraerValorString(contenido, cursor, "nombre");
            std::string reg = extraerValorString(contenido, cursor, "region");
            std::string prop = extraerValorString(contenido, cursor, "propietario");
            
            listaFincas->insertar(cod, nom, reg, prop);
        }
        std::cout << "Fincas cargadas exitosamente.\n";
    }

    // 2. Parsear Entregas
    if (posEntregas != std::string::npos) {
        size_t cursor = posEntregas;
        
        while (cursor < contenido.length()) {
            std::string fechaFull = extraerValorString(contenido, cursor, "fecha");
            if (fechaFull.empty()) break;
            
            // Extraer solo YYYY-MM-DD para el Árbol B
            std::string fechaCorta = fechaFull.substr(0, 10);
            
            std::string codLote = extraerValorString(contenido, cursor, "codigo lote");
            if(codLote.empty()) codLote = extraerValorString(contenido, cursor, "codigo_lote"); // Por si viene con guion bajo
            
            std::string codFinca = extraerValorString(contenido, cursor, "finca");
            int sacos = extraerValorInt(contenido, cursor, "sacos");
            std::string tipoCafe = extraerValorString(contenido, cursor, "tipo cafe");
            if(tipoCafe.empty()) tipoCafe = extraerValorString(contenido, cursor, "tipo_cafe");
            
            std::string estado = extraerValorString(contenido, cursor, "estado");

            // Validar integridad referencial
            if (!listaFincas->existeFinca(codFinca)) {
                std::cerr << "Error: Lote " << codLote << " ignorado. La finca " << codFinca << " no existe.\n";
                continue;
            }

            // Crear el lote e insertarlo en el Árbol B (que internamente lo manda al AVL)
            std::string nombreFinca = listaFincas->obtenerNombreFinca(codFinca);
            Lote* nuevoLote = new Lote(codLote, codFinca, nombreFinca, sacos, tipoCafe);
            nuevoLote->avanzarEstado(estado, fechaFull);
            
            arbolB->insertar(fechaCorta, nuevoLote);
        }
        std::cout << "Entregas procesadas e insertadas en los árboles.\n";
    }
}