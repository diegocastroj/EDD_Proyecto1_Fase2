#ifndef GENERADOR_HASH_H
#define GENERADOR_HASH_H

#include <string>

class GeneradorHash {
public:
    static std::string generarHash(const std::string& entrada);
};

#endif