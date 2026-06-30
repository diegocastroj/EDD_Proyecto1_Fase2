#include "../include/GeneradorHash.h"
#include <sstream>
#include <iomanip>

std::string GeneradorHash::generarHash(const std::string& entrada) {
    unsigned long long hash = 5381;
    
    // Algoritmo tipo DJB2 modificado
    for (char c : entrada) {
        hash = ((hash << 5) + hash) + c; 
    }
    
    // Generar una segunda parte para alcanzar los 32 caracteres (128 bits visuales)
    unsigned long long hash2 = 0;
    for (int i = entrada.length() - 1; i >= 0; i--) {
        hash2 = ((hash2 << 4) + hash2) ^ entrada[i];
    }

    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(16) << hash;
    ss << std::hex << std::setfill('0') << std::setw(16) << hash2;
    
    return ss.str();
}