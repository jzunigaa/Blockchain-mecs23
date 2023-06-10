#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <unordered_map>
#include <set>
#include <vector>
#include <map>
#include<string>

struct ListNode {
    Block block;
    ListNode* next;
    ListNode* prev;

    ListNode(const Block& block) : block(block), next(nullptr), prev(nullptr) {}
};

struct BSTNode {
    Block block;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Block& block) : block(block), left(nullptr), right(nullptr) {}
};

class Blockchain {
private:
    int prefijo;
    ListNode* head;
    ListNode* tail;
    std::unordered_map<std::string, std::vector<Transaction>> personTable;
    std::map<std::string, std::vector<Transaction>> dateMap;
    BSTNode* bstRoot;
    BSTNode* obtenerSucesor(BSTNode* node);

public:
    Blockchain(int prefijo);
    ~Blockchain();

    void agregarBloque(const std::vector<Transaction>& transactions);
    void insertarEnTabla(const std::vector<Transaction> &transactions);
    void insertarByDate(const std::vector<Transaction> &transactions);
    void insertarEnBST(const Block& block, BSTNode*& node);
    void imprimirBlockchain();
    void ingresarRegistro();
    void cargarDesdeCSV(const std::string& archivo);
    void actualizarRegistro(int bloque, int transaccion, const std::string& emisor, const std::string& receptor, double monto, const std::string& fecha, const std::string& ciudad);
    void eliminarDeTabla(std::vector<Transaction> &transactions);
    void eliminarDeBST(const Block &block);
    void eliminarDeBSTAux(BSTNode *&node, const Block &block);
    void recalcularHashesCascada(ListNode *node);

    std::vector<Transaction> buscarPorNombre(const std::string& nombre);
    std::vector<Transaction> buscarPorFecha(const std::string& fecha);
    std::vector<std::vector<Transaction>> buscarPorRangoDeFechas(std::string startDate, std::string endDate);
    std::vector<Transaction> buscarPorMontoMaximo(double montoMax);
    std::vector<Transaction> buscarPorMontoMinimo(double montoMin);
    std::vector<Transaction> buscarPorRangoDeMonto(double montoMin, double montoMax);

private:
    void buscarPorMontoMaximoAux(BSTNode* node, double montoMax, std::vector<Transaction>& transaccionesEncontradas);
void buscarPorMontoMinimoAux(BSTNode* node, double montoMin, std::vector<Transaction>& transaccionesEncontradas);
void buscarPorRangoDeMontoAux(BSTNode* node, double montoMin, double montoMax, std::vector<Transaction>& transaccionesEncontradas);
};

#endif  // BLOCKCHAIN_H
