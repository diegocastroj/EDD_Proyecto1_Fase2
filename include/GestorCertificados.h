#ifndef GESTOR_CERTIFICADOS_H
#define GESTOR_CERTIFICADOS_H

#include "Lote.h"
#include "ListaFincas.h"
#include <string>

class GestorCertificados {
private:
    std::string encriptar(const std::string& texto);
    
public:
    // Hacemos public desencriptar para que la opción 4.3 la pueda usar fácilmente
    std::string desencriptar(const std::string& texto);
    
    // Genera el TXT, lo encripta, actualiza el lote y retorna el hash_contenido
    std::string generarCertificado(Lote* lote, ListaFincas* fincas, std::string fecha);
    
    // Lee un TXT encriptado de la carpeta certificados/ y lo muestra en consola
    void desencriptarYMostrar(std::string nombreArchivo);
};

#endif
