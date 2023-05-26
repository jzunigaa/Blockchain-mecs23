#ifndef TRANSFERENCIA_H
#define TRANSFERENCIA_H
#include <iostream>
#include "Usuario.h"

class Transferencia {
private:
  Usuario emisor;
  Usuario receptor;
  double monto;
  string fecha;
  string lugar;

public:
  Transferencia(){}

  Transferencia(Usuario emisor, Usuario receptor, double monto, string fecha, string lugar){
    this->emisor = emisor;
    this->receptor = receptor;
    this->monto = monto;
    this->fecha = fecha;
    this->lugar = lugar;
  }

  string toString(){
    string out = "";
    out += "data:{\n";
    out += "\tEmisor: " + this->getEmisor().toString() + "\n";
    out += "\tReceptor: " + this->getReceptor().toString() + "\n";
    out += "\tMonto: " + to_string(this->getMonto()) + "\n";
    out += "\tFecha: " + this->getFecha() + "\n";
    out += "\tLugar: " + this->getLugar() + "\n";
    out += "}\n";
    return out;
   }
  
  void setEmisor(Usuario emisor){
    this->emisor = emisor;
  }

  void setReceptor(Usuario receptor){
    this->receptor = receptor;
  }

  void setMonto(double monto){
    this->monto = monto;
  }

  void setFecha(string fecha){
    this->fecha = fecha;
  }

  void setLugar(string lugar){
    this->lugar = lugar;
  }

  Usuario getEmisor(){
    return this->emisor;
  }

  Usuario getReceptor(){
    return this->receptor;
  }

  double getMonto(){
    return this->monto;
  }

  string getFecha(){
    return this->fecha;
  }

  string getLugar(){
    return this->lugar;
  }

};
#endif