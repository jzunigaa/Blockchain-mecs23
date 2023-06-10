#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include "sha256.h"
#include <sstream>

struct Transaction {
    std::string emisor;
    std::string receptor;
    double monto;
    std::string fecha;
    std::string ciudad;
    std::string hash;

    void calcularHash();
    std::string toString();
};

struct Block {
    int index;
    std::string prevHash;
    std::vector<Transaction> transactions;
    int nonce;
    std::string hash;

    Block(int index, const std::string& prevHash, const std::vector<Transaction>& transactions);
    void calcularHash(int prefijo);
    void minarBloque(int prefijo);
};

Block::Block(int index, const std::string& prevHash, const std::vector<Transaction>& transactions)
    : index(index),
      prevHash(prevHash),
      transactions(transactions),
      nonce(0),
      hash("") {}

void Block::calcularHash(int prefijo) {
    std::stringstream ss;
    ss << index << prevHash;
    for (const Transaction& transaction : transactions) {
        ss << transaction.emisor << transaction.receptor << transaction.monto
           << transaction.fecha << transaction.ciudad;
    }
    ss << nonce;

    std::string datos = ss.str();
    hash = sha256(datos);

    std::string target(prefijo, '0');
    while (hash.substr(0, prefijo) != target) {
        nonce++;
        ss.str("");
        ss << index << prevHash;
        for (const Transaction& transaction : transactions) {
            ss << transaction.emisor << transaction.receptor << transaction.monto
               << transaction.fecha << transaction.ciudad;
        }
        ss << nonce;
        datos = ss.str();
        hash = sha256(datos);
    }
}

void Block::minarBloque(int prefijo) {
    calcularHash(prefijo);
}

void Transaction::calcularHash() {
    std::stringstream ss;
    ss << emisor << receptor << monto << fecha << ciudad;
    std::string datos = ss.str();
    hash = sha256(datos);
}

std::string Transaction::toString(){
    std::string out = "";
    out += "data:{\n";
    out += "\tEmisor: " + emisor + "\n";
    out += "\tReceptor: " + receptor + "\n";
    out += "\tMonto: " + std::to_string(monto) + "\n";
    out += "\tFecha: " + fecha + "\n";
    out += "\tLugar: " + ciudad + "\n";
    out += "}\n";
    return out;
   }


#endif  // BLOCK_H
