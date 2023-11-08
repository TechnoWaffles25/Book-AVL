#ifndef BPLUSNODE_H
#define BPLUSNODE_H

#include <vector>
#include <string>

using namespace std;

struct PostingList {
    vector<int> documentIds; // IDs de los documentos donde aparece la clave
    vector<vector<int>> positions; // Posiciones de la clave en cada documento
    // Puedes añadir más información aquí como frecuencias, etc.

    // Añade una nueva ocurrencia de la palabra en un documento específico y en una posición específica.
    void addOccurrence(int documentId, int position) {
        // Busca el documento en la lista.
        auto it = find(documentIds.begin(), documentIds.end(), documentId);

        // Si el documento ya está en la lista, añade la nueva posición.
        if (it != documentIds.end()) {
            // Encuentra el índice del documentoId en el vector documentIds.
            size_t index = distance(documentIds.begin(), it);
            // Añade la posición en el vector correspondiente dentro del vector de posiciones.
            positions[index].push_back(position);
        } else {
            // Si el documento no está en la lista, añade el nuevo ID y la nueva posición.
            documentIds.push_back(documentId);
            // Crea un nuevo vector de posiciones para este documentoId y añade la posición.
            positions.push_back(vector<int>{position});
        }
    }

};

struct BPlusNode {
    bool isLeaf;
    vector<string> keys;

    BPlusNode(bool leaf) : isLeaf(leaf) {}
    virtual ~BPlusNode() {}

    int findKeyIndex(const string& key) const {
        for (int i = 0; i < keys.size(); ++i) {
            if (keys[i] >= key) return i;
        }
        return keys.size();
    }
};

struct BPlusInternalNode : public BPlusNode{
    vector<BPlusNode*> children;
    BPlusInternalNode() : BPlusNode(false){}

    ~BPlusInternalNode(){
        for (auto child : children){
            delete child;
        }
    }
};

struct BPlusLeafNode : public BPlusNode {
    vector<PostingList> values; // Los datos reales, listas de publicaciones
    BPlusLeafNode* next; // Un puntero al siguiente nodo hoja para iterar a través de las hojas
    BPlusLeafNode() : BPlusNode(true), next(nullptr) {} // true indica que es un nodo hoja
};
#endif