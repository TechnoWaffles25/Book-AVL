#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "BPlusNode.h" // Asegúrate de incluir los nodos aquí.

// Order 50-100

struct BPlusTree {
    BPlusNode *root;
    int order; // Orden del árbol B+, determina el número máximo de claves por nodo
    BPlusLeafNode *firstLeaf; // Puntero al primer nodo hoja, útil para iteraciones

    // Constructor
    BPlusTree(int order) : order(order), root(nullptr), firstLeaf(nullptr) {}

    // Destructor
    ~BPlusTree() {
        // Implementar la lógica para eliminar correctamente el árbol
        deleteTree(root);
    }

    void insert(const string& key, int documentId, int position);
    void search(const string& key, vector<int>& documentIds, vector<vector<int>>& positions) const;
    vector<PostingList> rangeSearch(const string& lowerBound, const string& upperBound) const;
    void splitNode(BPlusNode* node);
    void promoteKey(BPlusNode* child, BPlusNode* parent, const string& key);
    void deleteKey(const string& key, int documentId, int position);
    void updateKey(const string& key, int documentId, int position);
    void iterateLeaves() const;
    void rebalanceAfterDelete(BPlusNode* node);


private:
    // Método auxiliar para eliminar el árbol
    void deleteTree(BPlusNode *node) {
        if (node) {
            if (!node->isLeaf) {
                BPlusInternalNode *internalNode = static_cast<BPlusInternalNode *>(node);
                for (BPlusNode *child : internalNode->children) {
                    deleteTree(child);
                }
            }
            delete node;
        }
    }
};

#endif // BPLUSTREE_H