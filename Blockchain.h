#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <iostream>
#include <map> //Implemented as a BST
#include <unordered_map> //Implemented as a hash table
#include <vector>
#include <functional>
#include <time.h>
#include "Transferencia.h"
#include "SHA256.h"
using namespace std;

class Blockchain {
private:
  long bc_id;
  string nonce;
  string data; //simular un json
  string bc_prev_hash;
  string bc_curr_hash;
  int max_registros;
  vector<Transferencia> trans_list;
  unordered_map<string, vector<Transferencia> > bc_name_id;
  unordered_map<string, vector<Transferencia> > bc_dni_id;
  map<string,vector<Transferencia> > bc_date_id;

private:
  string getHashCode(string data){
    SHA256 hash_code;
    hash_code.update(data);
    uint8_t* digest = hash_code.digest();
    return SHA256::toString(digest);
  }

  string mining(int id){
    int num;
    srand(time(nullptr));
    num = 1000000 + (rand()*id) % (1000000);
    return to_string(num);
  }

  void addMapByName(vector<Transferencia> trans_list){//O(n)
    unordered_map<string, vector<Transferencia> >::iterator it;
    //Emisor
    for(int i = 0; i < trans_list.size(); i++){
        string key = trans_list[i].getEmisor().getNombre();
        it = bc_name_id.find(key);
        if(it != bc_name_id.end())
            it->second.push_back(trans_list[i]);
        else{
            vector<Transferencia> in_list;
            in_list.push_back(trans_list[i]);
            bc_name_id.insert(make_pair(key, in_list));
        }
    }
    //Receptor
    for(int i = 0; i < trans_list.size(); i++){
        string key = trans_list[i].getReceptor().getNombre();
        it = bc_name_id.find(key);
        if(it != bc_name_id.end())
            it->second.push_back(trans_list[i]);
        else{
            vector<Transferencia> in_list;
            in_list.push_back(trans_list[i]);
            bc_name_id.insert(make_pair(key, in_list));
        }
    }
  }

  void addMapByDni(vector<Transferencia> trans_list){//O(n)
    unordered_map<string, vector<Transferencia> >::iterator it;
    //Emisor
    for(int i = 0; i < trans_list.size(); i++){
        string key = trans_list[i].getEmisor().getDni();
        it = bc_dni_id.find(key);
        if(it != bc_dni_id.end())
            it->second.push_back(trans_list[i]);
        else{
            vector<Transferencia> in_list;
            in_list.push_back(trans_list[i]);
            bc_dni_id.insert(make_pair(key, in_list));
        }
    }
    //Receptor
    for(int i = 0; i < trans_list.size(); i++){
        string key = trans_list[i].getReceptor().getDni();
        it = bc_dni_id.find(key);
        if(it != bc_dni_id.end())
            it->second.push_back(trans_list[i]);
        else{
            vector<Transferencia> in_list;
            in_list.push_back(trans_list[i]);
            bc_dni_id.insert(make_pair(key, in_list));
        }
    }
  }

  void addMapByDate(vector<Transferencia> trans_list){
    map<string,vector<Transferencia> >::iterator it;
    for(int i = 0; i < trans_list.size(); i++){
        string key = trans_list[i].getFecha();
        it = bc_date_id.find(key);
        if(it != bc_date_id.end()){
            it->second.push_back(trans_list[i]);
        }
        else{
            vector<Transferencia> in_list;
            in_list.push_back(trans_list[i]);
            bc_date_id.insert(make_pair(key,in_list));
        }
    }
  }

public:
  map<long, Blockchain> block_list; //it works like a BST

  Blockchain(){
    this->bc_id = 0;
    this->max_registros = 10;
  }

  void add_block(vector<Transferencia> trans_list){ //O(n)
    if(trans_list.size() > this->max_registros){
      throw "La cantidad de registros debe ser menor o igual a " + to_string(this->max_registros);
    }

    static string prev_hash_tmp = "00000000000000000000";
    Blockchain new_block;
    new_block.bc_id = ++this->bc_id;
    new_block.nonce = mining(new_block.bc_id);
    addMapByName(trans_list);
    addMapByDni(trans_list);
    addMapByDate(trans_list);

    // for(int i = 0; i < trans_list.size(); i++){
    //   if(i > 0) continue;
      new_block.data = "Bloque #" + to_string(new_block.bc_id) + "\n" +
                       "Registros #" + to_string(trans_list.size()) + "\n" +
                       "nonce: " + new_block.nonce + "\n" + trans_list[0].toString();

      string hash_code = getHashCode(new_block.data);
      new_block.bc_prev_hash = prev_hash_tmp; //para el bloque genesis sera 0s
      new_block.bc_curr_hash = hash_code;
      prev_hash_tmp = new_block.bc_curr_hash;
      new_block.data += ",...\n";
      new_block.data += "Hash Code: " + new_block.bc_curr_hash + "\n" +
                        "Hash Code Prev: " + new_block.bc_prev_hash + "\n"
                        + "--------------------------------------------\n";
    // }
    new_block.trans_list = trans_list;
    block_list.insert(make_pair(this->bc_id, new_block));
  }

  Blockchain find_by_id(long id){
    return block_list[id];
  }

  vector<Transferencia> find_by_name(string name){//O(1)
    vector<Transferencia> output;
    unordered_map<string, vector<Transferencia> >::iterator it;
    it = this->bc_name_id.find(name); //O(1)
    if(it != bc_name_id.end())
      output = it->second;
    return output;
  }

  vector<Transferencia> find_by_dni(string dni){
    vector<Transferencia> output;
    unordered_map<string, vector<Transferencia> >::iterator it;
    it = this->bc_dni_id.find(dni);
    if(it != bc_dni_id.end())
        output = it->second;
    return output;
  }

  vector<Transferencia> find_by_date(string date){
    vector<Transferencia> output;
    map<string, vector<Transferencia> >::iterator it;
    it = this->bc_date_id.find(date);
    if(it != bc_date_id.end()){
        output = it->second;
    }
    return output;
  }

  // Función para buscar los montos de transacciones en un rango de fechas
  vector<vector<Transferencia>> getTransactionsInRange(string startDate, string endDate) {
    vector<vector<Transferencia>> output;
    map<string, vector<Transferencia> >::iterator start;
    map<string, vector<Transferencia> >::iterator _end;
   // map<string, vector<Transferencia> >::iterator it;
    start = this->bc_date_id.lower_bound(startDate);
    _end = this->bc_date_id.upper_bound(endDate);
    for ( map<string, vector<Transferencia> >::iterator it = start; it != _end; ++it) {
        output.push_back(it->second);
    }
    return output;
    }

  // Búsqueda por rango
  vector<Transferencia> find_by_range(long begin, long end) {
    vector<Transferencia> output;

    for (map<long, Blockchain>::iterator blockIt = block_list.begin();
         blockIt != block_list.end(); ++blockIt) {
      Blockchain &block = blockIt->second;
      for (vector<Transferencia>::iterator transIt = block.trans_list.begin();
           transIt != block.trans_list.end(); ++transIt) {
        Transferencia &transaction = *transIt;
        if (transaction.getMonto() >= begin && transaction.getMonto() <= end) {
          output.push_back(transaction);
        }
      }
    }

    return output;
  }

  // Búsqueda del mínimo por usuario
  Transferencia find_max_by_name(string name) {
    Transferencia maxTrans;
    unordered_map<string, vector<Transferencia>>::iterator it =
        bc_name_id.find(name);
    if (it != bc_name_id.end()) {
      vector<Transferencia> &trans_list = it->second;
      maxTrans = trans_list[0];
      for (Transferencia &trans : trans_list) {
        if (trans.getMonto() > maxTrans.getMonto()) {
          maxTrans = trans;
        }
      }
    }
    return maxTrans;
  }

  // Búsqueda del máximo por usuario
  Transferencia find_min_by_name(string name) {
    Transferencia minTrans;
    unordered_map<string, vector<Transferencia>>::iterator it =
        bc_name_id.find(name);
    if (it != bc_name_id.end()) {
      vector<Transferencia> &trans_list = it->second;
      minTrans = trans_list[0];
      for (Transferencia &trans : trans_list) {
        if (trans.getMonto() < minTrans.getMonto()) {
          minTrans = trans;
        }
      }
    }
    return minTrans;
  }

  // Blockchain find_by_range(long begin, long end){

  // }

  string getData(){
    return this->data;
  }

};
#endif
