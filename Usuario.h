#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
using namespace std;

class Usuario {
private:
  string nombre;
  string apellido;
  string dni;

public:
  Usuario(){}
  Usuario(string nombre, string apellido, string dni){
    this->nombre = nombre;
    this->apellido = apellido;
    this->dni = dni;
  }
  
  string toString(){
    string out = "";
    out += this->nombre + " " + this->apellido + " ("+ this->dni +")";
    return out;
  }

  void setNombre(string nombre){
    this->nombre = nombre;
  }

  void setApellido(string apellido){
    this->apellido = apellido;
  }

  void setDni(string dni){
    this->dni = dni;
  }

  string getNombre(){
    return this->nombre;
  }

  string getApellido(){
    return this->apellido;
  }

  string getDni(){
    return this->dni;
  }

};
#endif