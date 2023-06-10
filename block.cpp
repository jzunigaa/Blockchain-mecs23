#include "block.h"
#include "sha256.h"

#include <sstream>

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
