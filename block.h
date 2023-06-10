#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

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

#endif  // BLOCK_H
