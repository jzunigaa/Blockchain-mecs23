#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <unordered_map>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

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

Blockchain::Blockchain(int prefijo)
    : prefijo(prefijo), head(nullptr), tail(nullptr), bstRoot(nullptr) {}

Blockchain::~Blockchain() {
  ListNode *current = head;
  while (current != nullptr) {
    ListNode *next = current->next;
    delete current;
    current = next;
  }
}

void Blockchain::agregarBloque(const std::vector<Transaction> &transactions) {
  std::string prevHash = (tail != nullptr) ? tail->block.hash : "";
  Block block(tail != nullptr ? tail->block.index + 1 : 0, prevHash,
              transactions);

  // Incrementar el índice después de crear el bloque
  int index = block.index;

  if (head == nullptr) {
    head = new ListNode(block);
    tail = head;
  } else {
    ListNode *newBlock = new ListNode(block);
    newBlock->prev = tail;
    tail->next = newBlock;
    tail = newBlock;
  }

  insertarEnTabla(transactions);
  insertarByDate(transactions);

  insertarEnBST(block, bstRoot);
  tail->block.minarBloque(prefijo);
}

void Blockchain::insertarEnTabla(const std::vector<Transaction> &transactions) {
  unordered_map<std::string, std::vector<Transaction>>::iterator it;
  //emisor
  for(int i = 0; i < transactions.size(); i++){
    std::string key = transactions[i].emisor;
    it = personTable.find(key);
    if (it != personTable.end()) {
      it->second.push_back(transactions[i]);
    }
    else{
      vector<Transaction> in_list;
      in_list.push_back(transactions[i]);
      personTable.insert(make_pair(key, in_list));
    }
  }

  //receptor
  for(int i = 0; i < transactions.size(); i++){
    std::string key = transactions[i].receptor;
    it = personTable.find(key);
    if (it != personTable.end()) {
      it->second.push_back(transactions[i]);
    }
    else{
      vector<Transaction> in_list;
      in_list.push_back(transactions[i]);
      personTable.insert(make_pair(key, in_list));
    }
  }
}

void Blockchain::insertarByDate(const std::vector<Transaction> &transactions){
  map<string,vector<Transaction> >::iterator it;
    for(int i = 0; i < transactions.size(); i++){
        string key = transactions[i].fecha;
        it = dateMap.find(key);
        if(it != dateMap.end()){
            it->second.push_back(transactions[i]);
        }
        else{
            vector<Transaction> in_list;
            in_list.push_back(transactions[i]);
            dateMap.insert(make_pair(key,in_list));
        }
    }
}

void Blockchain::insertarEnBST(const Block &block, BSTNode *&node) {
  if (node == nullptr) {
    node = new BSTNode(block);
    return;
  }

  if (block.transactions.front().fecha <
      node->block.transactions.front().fecha) {
    insertarEnBST(block, node->left);
  } else {
    insertarEnBST(block, node->right);
  }
}

void Blockchain::imprimirBlockchain() {
  ListNode *current = head;
  int transactionNumber = 1; // Contador de transacciones

  while (current != nullptr) {
    std::cout << std::endl;
    std::cout << "Bloque #" << current->block.index << std::endl;
    std::cout << "============================================================="
                 "============="
              << std::endl;
    for (const Transaction &transaction : current->block.transactions) {
      std::cout << "Transacción #" << transactionNumber
                << std::endl; // Mostrar número de transacción
      std::cout << "Fecha: " << transaction.fecha << std::endl;
      std::cout << "Emisor: " << transaction.emisor << std::endl;
      std::cout << "Receptor: " << transaction.receptor << std::endl;
      std::cout << "Monto: " << transaction.monto << std::endl;
      std::cout << "Ciudad: " << transaction.ciudad << std::endl;
      std::cout << "Hash: " << current->block.hash << std::endl;
      std::cout << "Hash anterior: " << current->block.prevHash << std::endl;
      std::cout << "-----------------------" << std::endl;
      transactionNumber++; // Incrementar el número de transacción
    }
    current = current->next;
  }
}

void Blockchain::ingresarRegistro() {
  std::vector<Transaction> transactions;
  char rpt;
  int i = 1;

  do {
    std::string emisor, receptor, fecha, ciudad;
    double monto;

    std::cout << "\nTransaccion: "<< i<< endl;
    std::cout << "Ingrese el emisor: ";
    std::cin.ignore();
    std::getline(std::cin, emisor);
    std::cout << "Ingrese el receptor: ";
    std::getline(std::cin, receptor);
    std::cout << "Ingrese el monto: ";
    std::cin >> monto;
    std::cout << "Ingrese la fecha: ";
    std::cin.ignore();
    std::getline(std::cin, fecha);
    std::cout << "Ingrese la ciudad: ";
    std::getline(std::cin, ciudad);

    Transaction transaction{emisor, receptor, monto, fecha, ciudad};
    transaction.calcularHash();
    transactions.push_back(transaction);
    i++;

    do{
      cout << "\n¿Desea registrar otra transaccion? (Y / N)  ";
      cin >> rpt;
    }while (rpt != 'Y' && rpt != 'N');

  } while (rpt == 'Y' && transactions.size() < 5);

  agregarBloque(transactions);

  cout << "\n!Las transacciones fueron cargadas exitosamente!";
}

void Blockchain::cargarDesdeCSV(const std::string &archivo) {
  std::ifstream file(archivo);
  if (!file) {
    std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
    return;
  }

  std::vector<Transaction> transactions;
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string emisor, receptor, fecha, ciudad, montoStr;
    double monto;

    std::getline(ss, emisor, ',');
    std::getline(ss, receptor, ',');
    std::getline(ss, montoStr, ',');
    std::getline(ss, fecha, ',');
    std::getline(ss, ciudad, ',');

    try {
        monto = std::stod(montoStr);
    } catch (const std::exception& e) {
        std::cerr << "Error al leer el monto en la línea: " << line <<
    std::endl; continue;
    }

    Transaction transaction{emisor, receptor, monto, fecha, ciudad};
    transaction.calcularHash();
    transactions.push_back(transaction);

    if (transactions.size() == 5) {
      agregarBloque(transactions);
      transactions.clear();
    }
  }

  if (!transactions.empty()) {
    agregarBloque(transactions);
  }

  std::cout << "Registros cargados desde el archivo CSV." << std::endl;
}

void Blockchain::actualizarRegistro(int bloque, int transaccion,
                                    const std::string &emisor,
                                    const std::string &receptor, double monto,
                                    const std::string &fecha,
                                    const std::string &ciudad) {
  ListNode *current = head;
  while (current != nullptr && current->block.index != bloque) {
    current = current->next;
  }

  if (current == nullptr) {
    std::cout << "El bloque especificado no existe." << std::endl;
    return;
  }

  if (transaccion < 0 || transaccion >= current->block.transactions.size()) {
    std::cout << "El número de transacción especificado no es válido."
              << std::endl;
    return;
  }

  Transaction &transaction = current->block.transactions[transaccion];
  transaction.emisor = emisor;
  transaction.receptor = receptor;
  transaction.monto = monto;
  transaction.fecha = fecha;
  transaction.ciudad = ciudad;
  transaction.calcularHash();

  vector<Transaction> t_list;
  t_list.push_back(transaction);

  eliminarDeTabla(t_list);
  eliminarDeBST(current->block);

  insertarEnTabla(t_list);
  insertarEnBST(current->block, bstRoot);

  recalcularHashesCascada(current->next);
}

void Blockchain::eliminarDeTabla(std::vector<Transaction> &transactions) {
  unordered_map<std::string, std::vector<Transaction>>::iterator it;
  vector<Transaction>::iterator it_t;
  for(it_t = transactions.begin(); it_t != transactions.end(); ++it_t){
    std::string key = it_t->emisor;
    it = personTable.find(key);
    if (it != personTable.end()) {
      transactions.erase(it_t);
    }
  }
}

void Blockchain::eliminarDeBST(const Block &block) {
  eliminarDeBSTAux(bstRoot, block);
}

void Blockchain::eliminarDeBSTAux(BSTNode*& node, const Block& block) {
    if (node == nullptr) {
        return;
    }

    if (node->block.index == block.index && node->block.prevHash == block.prevHash) {
        BSTNode* toDelete = node;
        if (node->left == nullptr) {
            node = node->right;
        } else if (node->right == nullptr) {
            node = node->left;
        } else {
            BSTNode* successorParent = node;
            BSTNode* successor = node->right;
            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }
            node->block = successor->block;
            if (successorParent == node) {
                successorParent->right = successor->right;
            } else {
                successorParent->left = successor->right;
            }
        }
        delete toDelete;
        return;
    }

    if (block.index < node->block.index || (block.index == node->block.index && block.prevHash < node->block.prevHash)) {
        eliminarDeBSTAux(node->left, block);
    } else {
        eliminarDeBSTAux(node->right, block);
    }
}

BSTNode *Blockchain::obtenerSucesor(BSTNode *node) {
  BSTNode *current = node;
  while (current && current->left != nullptr) {
    current = current->left;
  }
  return current;
}

void Blockchain::recalcularHashesCascada(ListNode *node) {
  while (node != nullptr) {
    node->block.calcularHash(prefijo);
    node = node->next;
  }
}

std::vector<Transaction> Blockchain::buscarPorNombre(const std::string &nombre) {
  std::vector<Transaction> _transactions;
  std::unordered_map<std::string, std::vector<Transaction>>::iterator it = personTable.find(nombre);
  if (it != personTable.end()) {
    _transactions = it->second;
    }
  return _transactions;
}

std::vector<Transaction> Blockchain::buscarPorFecha(const std::string& fecha){
    vector<Transaction> output;
    map<string, vector<Transaction> >::iterator it;
    it = this->dateMap.find(fecha);
    if(it != dateMap.end()){
        output = it->second;
    }
    return output;
  }

std::vector<std::vector<Transaction>> Blockchain::buscarPorRangoDeFechas(std::string startDate, std::string endDate) {
    vector<vector<Transaction>> output;
    map<string, vector<Transaction> >::iterator start;
    map<string, vector<Transaction> >::iterator _end;
   // map<string, vector<Transferencia> >::iterator it;
    start = dateMap.lower_bound(startDate);
    _end = dateMap.upper_bound(endDate);
    for ( map<string, vector<Transaction> >::iterator it = start; it != _end; ++it) {
        output.push_back(it->second);
    }
    return output;
}

std::vector<Transaction> Blockchain::buscarPorMontoMaximo(double montoMax) {
  std::vector<Transaction> transaccionesEncontradas;
  buscarPorMontoMaximoAux(bstRoot, montoMax, transaccionesEncontradas);
  return transaccionesEncontradas;
}

void Blockchain::buscarPorMontoMaximoAux(BSTNode* node, double montoMax, std::vector<Transaction>& transaccionesEncontradas) {
  if (node == nullptr) {
    return;
  }

  buscarPorMontoMaximoAux(node->left, montoMax, transaccionesEncontradas);

  for (const Transaction& transaction : node->block.transactions) {
    if (transaction.monto <= montoMax) {
      transaccionesEncontradas.push_back(transaction);
    }
  }

  buscarPorMontoMaximoAux(node->right, montoMax, transaccionesEncontradas);
}

std::vector<Transaction> Blockchain::buscarPorMontoMinimo(double montoMin) {
  std::vector<Transaction> transaccionesEncontradas;
  buscarPorMontoMinimoAux(bstRoot, montoMin, transaccionesEncontradas);
  return transaccionesEncontradas;
}

void Blockchain::buscarPorMontoMinimoAux(BSTNode* node, double montoMin, std::vector<Transaction>& transaccionesEncontradas) {
  if (node == nullptr) {
    return;
  }

  buscarPorMontoMinimoAux(node->left, montoMin, transaccionesEncontradas);

  for (const Transaction& transaction : node->block.transactions) {
    if (transaction.monto >= montoMin) {
      transaccionesEncontradas.push_back(transaction);
    }
  }

  buscarPorMontoMinimoAux(node->right, montoMin, transaccionesEncontradas);
}

std::vector<Transaction> Blockchain::buscarPorRangoDeMonto(double montoMin, double montoMax) {
  std::vector<Transaction> transaccionesEncontradas;
  buscarPorRangoDeMontoAux(bstRoot, montoMin, montoMax, transaccionesEncontradas);
  return transaccionesEncontradas;
}

void Blockchain::buscarPorRangoDeMontoAux(BSTNode* node, double montoMin, double montoMax, std::vector<Transaction>& transaccionesEncontradas) {
  if (node == nullptr) {
    return;
  }

  buscarPorRangoDeMontoAux(node->left, montoMin, montoMax, transaccionesEncontradas);

  for (const Transaction& transaction : node->block.transactions) {
    if (transaction.monto >= montoMin && transaction.monto <= montoMax) {
      transaccionesEncontradas.push_back(transaction);
    }
  }

  buscarPorRangoDeMontoAux(node->right, montoMin, montoMax, transaccionesEncontradas);
}

#endif  // BLOCKCHAIN_H
