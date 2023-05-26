#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <iostream>
#include <map> //Implemented as a BST
#include <unordered_map> //Implemented as a hash table
#include <vector>
#include <functional>
#include <time.h>
#include "Transferencia.h"
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

private:
  string getHashCode(string data){
    std::hash<string> hash_fn;
    size_t hash_code = hash_fn(data);
    return to_string(hash_code);
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

  vector<Transferencia> find_by_name(string name){//O(n
    vector<Transferencia> output;
    unordered_map<string, vector<Transferencia> >::iterator it;
    it = this->bc_name_id.find(name); //O(1)
    for(Transferencia t : it->second)
      output.push_back(t);
    return output;
  }

  // Blockchain find_by_range(long begin, long end){
      
  // }
  
  string getData(){
    return this->data;
  }

};
#endif