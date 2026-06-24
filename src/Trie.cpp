#include "../include/Trie.h"
#include <algorithm>
#include <cctype>

Trie::Trie() {
    raiz = new TrieNode();
}

std::string Trie::aMinusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return resultado;
}

void Trie::insertar(const std::string& palabra, Listing* alojamiento) {
    TrieNode* actual = raiz;
    std::string palabraMin = aMinusculas(palabra);

    for (char letra : palabraMin) {
        // Convertimos el caracter a su codigo ASCII (0-255)
        unsigned char indice = static_cast<unsigned char>(letra);
        
        // Si el camino para esta letra esta vacio, creamos un nuevo nodo a mano
        if (actual->hijos[indice] == nullptr) {
            actual->hijos[indice] = new TrieNode();
        }
        actual = actual->hijos[indice];
    }
    // Guardamos el alojamiento al final de la palabra
    actual->alojamientos.push_back(alojamiento);
}

void Trie::recolectar(TrieNode* nodo, std::vector<Listing*>& resultados) {
    if (!nodo) return;
    
    // Agregar los alojamientos guardados en este nodo exacto
    for (Listing* aloj : nodo->alojamientos) {
        resultados.push_back(aloj);
    }
    
    // Recorremos los 256 caminos posibles de forma recursiva (DFS)
    for (int i = 0; i < 256; i++) {
        if (nodo->hijos[i] != nullptr) {
            recolectar(nodo->hijos[i], resultados);
        }
    }
}

std::vector<Listing*> Trie::buscarPorPrefijo(const std::string& prefijo) {
    TrieNode* actual = raiz;
    std::vector<Listing*> resultados;
    std::string prefijoMin = aMinusculas(prefijo);

    // Navegar letra por letra hasta el final del prefijo ingresado
    for (char letra : prefijoMin) {
        unsigned char indice = static_cast<unsigned char>(letra);
        
        // Si chocamos con un camino vacío (nulo), la palabra no existe
        if (actual->hijos[indice] == nullptr) {
            return resultados; // Retorna el vector vacío rápidamente
        }
        actual = actual->hijos[indice];
    }

    // Una vez llegamos al final del prefijo, recolectamos todas las ramificaciones
    recolectar(actual, resultados);
    return resultados;
}