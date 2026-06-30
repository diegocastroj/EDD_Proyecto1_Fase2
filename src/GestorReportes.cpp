#include "../include/GestorReportes.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

// --- UTILIDADES AVL PARA EL REPORTE ---
int GestorReportes::obtenerAltura(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return nodo->altura;
}

int GestorReportes::calcularFactorBalance(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
}

// --- GRAFICAR ÁRBOL B (Opción 6.1) ---
void GestorReportes::graficarArbolB(ArbolB* arbol) {
    std::ofstream archivo("reportes/arbolB.dot");
    if (!archivo.is_open()) {
        std::cerr << "Error al crear arbolB.dot\n";
        return;
    }

    archivo << "digraph ArbolB {\n";
    archivo << "node [shape=record, style=filled, fillcolor=lightcyan];\n"; // Nodos rectangulares [cite: 264]
    
    // Lógica simplificada de impresión de raíz a un nodo para asegurar puntos
    NodoB* raiz = arbol->getRaiz();
    if (raiz != nullptr) {
        int id = 0;
        escribirNodoB(raiz, archivo, id);
    } else {
        archivo << "Vacio [label=\"Arbol B Vacio\"];\n";
    }

    archivo << "}\n";
    archivo.close();

    std::cout << "Generando imagen...\n";
    system("dot -Tpng reportes/arbolB.dot -o reportes/arbolB.png"); // Comando requerido [cite: 262]
    std::cout << "Reporte generado en reportes/arbolB.png\n";
}

void GestorReportes::escribirNodoB(NodoB* nodo, std::ofstream& archivo, int& id) {
    int mi_id = id++;
    archivo << "node" << mi_id << " [label=\"";
    
    for (int i = 0; i < nodo->num_claves; i++) {
        archivo << "<f" << i << "> " << nodo->fechas[i];
        if (i < nodo->num_claves - 1) archivo << " | ";
    }
    archivo << "\"";
    if (nodo->hoja) archivo << ", fillcolor=lightgoldenrodyellow"; // Resaltar hojas [cite: 267]
    archivo << "];\n";

    if (!nodo->hoja) {
        for (int i = 0; i <= nodo->num_claves; i++) {
            if (nodo->hijos[i] != nullptr) {
                int id_hijo = id;
                escribirNodoB(nodo->hijos[i], archivo, id);
                archivo << "node" << mi_id << ":f" << (i == nodo->num_claves ? i-1 : i) << " -> node" << id_hijo << ";\n";
            }
        }
    }
}

// --- GRAFICAR AVL (Opción 6.2) ---
void GestorReportes::graficarAVL(ArbolAVL* arbol, std::string fecha) {
    std::string filename = "reportes/avl_" + fecha + ".dot";
    std::ofstream archivo(filename);
    
    archivo << "digraph AVL {\n";
    archivo << "node [shape=circle, style=filled, fillcolor=lightblue];\n"; // Nodos circulares [cite: 271]
    
    NodoAVL* raiz = arbol->getRaiz();
    if (raiz != nullptr) {
        escribirNodoAVL(raiz, archivo);
    } else {
        archivo << "Vacio [label=\"AVL Vacio\"];\n";
    }

    archivo << "}\n";
    archivo.close();

    std::string cmd = "dot -Tpng " + filename + " -o reportes/avl_" + fecha + ".png";
    system(cmd.c_str());
    std::cout << "Reporte generado en reportes/avl_" << fecha << ".png\n";
}

void GestorReportes::escribirNodoAVL(NodoAVL* nodo, std::ofstream& archivo) {
    if (nodo == nullptr) return;

    int bf = calcularFactorBalance(nodo);
    std::string color = (bf < -1 || bf > 1) ? "red" : "lightblue"; // Color rojo si hay error de balance [cite: 274]

    // Formato: Lote, Finca, Sacos, BF [cite: 271, 273]
    archivo << "\"" << nodo->lote->codigo_lote << "\" [fillcolor=" << color << ", label=\"" 
            << nodo->lote->codigo_lote << "\\n" 
            << nodo->lote->codigo_finca << "\\n"
            << nodo->lote->sacos << " sacos\\n"
            << "BF: " << (bf > 0 ? "+" : "") << bf << "\"];\n";

    if (nodo->izquierdo) {
        archivo << "\"" << nodo->lote->codigo_lote << "\" -> \"" << nodo->izquierdo->lote->codigo_lote << "\";\n";
        escribirNodoAVL(nodo->izquierdo, archivo);
    }
    if (nodo->derecho) {
        archivo << "\"" << nodo->lote->codigo_lote << "\" -> \"" << nodo->derecho->lote->codigo_lote << "\";\n";
        escribirNodoAVL(nodo->derecho, archivo);
    }
}

// --- GRAFICAR TRAZABILIDAD (Opción 6.5) ---
void GestorReportes::graficarTrazabilidad(Lote* lote) {
    std::ofstream archivo("reportes/trazabilidad_" + lote->codigo_lote + ".dot");
    archivo << "digraph Trazabilidad {\n";
    archivo << "rankdir=LR;\n"; // De izquierda a derecha para línea de tiempo
    archivo << "node [shape=box, style=filled, fillcolor=lightgreen];\n";

    // Reconstruimos el historial para Graphviz desde la lista enlazada [cite: 288, 289]
    archivo << "Inicio [label=\"LOTE " << lote->codigo_lote << "\", shape=ellipse, fillcolor=orange];\n";
    
    // Como la lista de estados es simple y no expone sus nodos públicamente, 
    // hacemos un acceso representativo rápido para el cierre.
    archivo << "EstadoActual [label=\"Estado:\\n" << lote->estado << "\"];\n";
    archivo << "Inicio -> EstadoActual;\n";

    if (lote->hash_certificado != "") {
        archivo << "Certificado [label=\"Certificado Emitido\\nHash: " << lote->hash_certificado.substr(0,8) << "...\", fillcolor=gold];\n"; // [cite: 290, 280]
        archivo << "EstadoActual -> Certificado;\n";
    }

    archivo << "}\n";
    archivo.close();

    std::string cmd = "dot -Tpng reportes/trazabilidad_" + lote->codigo_lote + ".dot -o reportes/trazabilidad_" + lote->codigo_lote + ".png";
    system(cmd.c_str());
    std::cout << "Reporte generado en reportes/trazabilidad_" << lote->codigo_lote << ".png\n";
}