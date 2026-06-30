#include "../include/GestorCertificados.h"
#include "../include/GeneradorHash.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Cifrado básico: Desplazamiento de +3 caracteres (Caesar)
std::string GestorCertificados::encriptar(const std::string& texto) {
    std::string resultado = texto;
    for (char& c : resultado) {
        c = c + 3;
    }
    return resultado;
}

std::string GestorCertificados::desencriptar(const std::string& texto) {
    std::string resultado = texto;
    for (char& c : resultado) {
        c = c - 3;
    }
    return resultado;
}

std::string GestorCertificados::generarCertificado(Lote* lote, ListaFincas* fincas, std::string fecha) {
    // 1. Avanzar estado a certificado emitido
    lote->avanzarEstado("certificado emitido", fecha);
    
    // 2. Preparar el contenido original
    std::stringstream contenido;
    contenido << "CERTIFICADO DE ENTREGA EDD COFFEETRACK\n";
    contenido << "Fecha          : " << fecha << "\n";
    contenido << "Codigo lote    : " << lote->codigo_lote << "\n";
    contenido << "Finca          : " << lote->nombre_finca << "\n";
    contenido << "Region         : " << fincas->obtenerRegion(lote->codigo_finca) << "\n"; // Necesitamos agregar este método rápido a ListaFincas
    contenido << "Tipo de cafe   : " << lote->tipo_cafe << "\n";
    contenido << "Sacos          : " << lote->sacos << "\n";
    contenido << "Estado final   : " << lote->estado << "\n";
    
    // 3. Obtener el hash del contenido (sin incluir el hash mismo)
    std::string hash_contenido = GeneradorHash::generarHash(contenido.str());
    
    // 4. Agregar el hash al contenido y guardar en el lote
    contenido << "Hash de contenido: " << hash_contenido << "\n";
    lote->hash_certificado = hash_contenido;
    
    // 5. Encriptar el texto completo
    std::string texto_encriptado = encriptar(contenido.str());
    
    // 6. Obtener el nombre del archivo (hash del codigo_lote)
    std::string hash_nombre = GeneradorHash::generarHash(lote->codigo_lote);
    std::string ruta_archivo = "certificados/" + hash_nombre + ".txt";
    
    // 7. Escribir el archivo físico
    std::ofstream archivo(ruta_archivo);
    if (archivo.is_open()) {
        archivo << texto_encriptado;
        archivo.close();
        std::cout << "Certificado generado: " << ruta_archivo << "\n";
    } else {
        std::cerr << "Error al crear el certificado en " << ruta_archivo << "\n";
    }
    
    return hash_contenido;
}

void GestorCertificados::desencriptarYMostrar(std::string nombreArchivo) {
    std::string ruta_archivo = "certificados/" + nombreArchivo;
    std::ifstream archivo(ruta_archivo);
    
    if (!archivo.is_open()) {
        std::cerr << "Error: No se encontro el archivo " << ruta_archivo << "\n";
        return;
    }
    
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    archivo.close();
    
    std::cout << "\n--- CONTENIDO DESENCRIPTADO ---\n";
    std::cout << desencriptar(buffer.str()) << "\n";
    std::cout << "-------------------------------\n";
}