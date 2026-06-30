#include <iostream>
#include <string>
#include "../include/ArbolB.h"
#include "../include/ListaFincas.h"
#include "../include/GestorJSON.h"
#include "../include/GestorCertificados.h"
#include "../include/ArbolMerkle.h"

using namespace std;

string historial_hashes[1000]; 
int contador_hashes = 0;

void mostrarMenu() {
    cout << "\n========================================\n";
    cout << "      EDD COFFEETRACK \n";
    cout << "          ADMINISTRADOR\n";
    cout << "========================================\n";
    cout << "1. Gestión de Datos\n";
    cout << "   1.1 Carga masiva desde JSON\n";
    cout << "   1.2 Registrar entrega manualmente\n";
    cout << "2. Consultas y Trazabilidad\n";
    cout << "   2.1 Buscar entregas por fecha\n";
    cout << "   2.2 Buscar lote especifico por codigo\n";
    cout << "   2.3 Listar todas las fechas registradas\n";
    cout << "   2.4 Trazabilidad completa de un lote\n";
    cout << "   2.5 Avanzar estado de un lote\n";
    cout << "3. Rutas\n";
    cout << "   3.1 Registrar nueva finca y sus conexiones\n";
    cout << "   3.3 Ver todas las fincas y conexiones registradas\n";
    cout << "4. Certificados\n";
    cout << "   4.1 Generar certificado encriptado de un lote\n";
    cout << "   4.2 Generar certificados masivos de una fecha completa\n";
    cout << "   4.3 Mostrar un certificado desencriptado en especifico\n";
    cout << "5. Arbol de Merkle\n";
    cout << "   5.1 Construir / actualizar arbol con certificados actuales\n";
    cout << "   5.2 Verificar si un certificado fue alterado\n";
    cout << "   5.3 Mostrar hash raiz actual\n";
    cout << "6. Reportes Graphviz\n";
    cout << "   6.1 Graficar Arbol B\n";
    cout << "   6.2 Graficar AVL de una fecha especifica\n";
    cout << "   6.4 Graficar Arbol de Merkle\n";
    cout << "   6.5 Graficar cadena de trazabilidad de un lote\n";
    cout << "0. Salir\n";
    cout << "========================================\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    ArbolB* arbolB = new ArbolB();
    ListaFincas* listaFincas = new ListaFincas();
    GestorJSON gestorJSON;
    GestorCertificados gestorCertificados;
    ArbolMerkle* arbolMerkle = new ArbolMerkle();
    
    string opcion;
    
    do {
        mostrarMenu();
        cin >> opcion;
        
        if (opcion == "1.1") {
            cout << "\nIngrese la ruta del archivo JSON (ej. data/prueba.json): ";
            string ruta;
            cin >> ruta;
            gestorJSON.cargarDatos(ruta, arbolB, listaFincas);
        } 
        else if (opcion == "2.3") {
            cout << "\n--- FECHAS Y LOTES REGISTRADOS ---\n";
            arbolB->recorrerInOrder();
        }
        else if (opcion == "3.3") {
            cout << "\n--- FINCAS REGISTRADAS ---\n";
            listaFincas->mostrarFincas();
        }
        else if (opcion == "4.1") {
            cout << "\nIngrese el codigo del lote (ej. L001): ";
            string cod_lote;
            cin >> cod_lote;
            
            // Para simplificar, buscamos la fecha pidiéndola al usuario (ya que en un entorno real la tendrías en sesión)
            // Otra opción es hacer un buscador universal, pero para hoy a la media noche, esto te salva:
            cout << "Ingrese la fecha de entrega de este lote (YYYY-MM-DD): ";
            string fecha;
            cin >> fecha;
            
            ArbolAVL* avl = arbolB->buscar(fecha);
            if (avl != nullptr) {
                Lote* lote = avl->buscarLote(cod_lote);
                if (lote != nullptr) {
                    string nuevo_hash = gestorCertificados.generarCertificado(lote, listaFincas, fecha);
                    historial_hashes[contador_hashes] = nuevo_hash;
                    contador_hashes++;
                    
                    // Actualizar Merkle automáticamente [cite: 76, 188]
                    arbolMerkle->construirArbol(historial_hashes, contador_hashes);
                    cout << "Arbol de Merkle actualizado automaticamente.\n";
                } else {
                    cout << "Lote no encontrado en esa fecha.\n";
                }
            } else {
                cout << "Fecha no encontrada.\n";
            }
        }
        else if (opcion == "4.3") {
            cout << "\nIngrese el nombre del archivo (ej. a3f9c2...txt): ";
            string nombre_archivo;
            cin >> nombre_archivo;
            gestorCertificados.desencriptarYMostrar(nombre_archivo);
        }
        else if (opcion == "5.1") {
            if (contador_hashes > 0) {
                arbolMerkle->construirArbol(historial_hashes, contador_hashes);
                cout << "Arbol de Merkle reconstruido con " << contador_hashes << " certificados.\n";
            } else {
                cout << "No hay certificados emitidos aun.\n";
            }
        }
        else if (opcion == "5.3") {
            arbolMerkle->mostrarRaiz();
        }
        else if (opcion == "0") {
            cout << "\nSaliendo del sistema...\n";
        } 
        else {
            cout << "\nOpcion en construccion o no valida.\n";
        }
        
    } while (opcion != "0");
    
    delete arbolB;
    delete listaFincas;
    delete arbolMerkle;
    
    return 0;
}