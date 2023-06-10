# SISTEMA DE TRANSACCIONES CON BLOCKCHAIN EN C++
**Table of Contents**

[TOCM]

[TOC]
## Introducción
El presente proyecto se encuentra desarrollado en c++ y tiene como objetivo principal el simular un sistema de transacciones bancarias simples que almacenan la información al interior de una blockchain y otras estructuras que permitan la búsqueda eficiente de los datos almacenados.

## Descripción del caso de estudio
El proyecto requiere un sistema que permita registrar de forma segura transacciones sencillas que almacenen datos como: el nombre del emisor, nombre del receptor, monto de la transacción, fecha de la transacción y lugar de la transacción. Se requiere implementar una estructura blockchain que brinde seguridad al sistema y multiples estructuras de indexación para la recuperación eficiente de informaicón.

## Importancia del Blockchain en el dominio de datos
## Estructura del Blockchain
## Estructuras para búsquedas
### Búsqueda por nombre
Para realizar la búsqueda por nomres primero se indexan los datos en una tabla hash que usa como key el nombre de la persona y como value un vector de transacciones.

Para el caso del proyecto la persona puede ser un emisor, un receptor o ambos (en diferentes transacciones).

En el siguiente código se muestra el método para indexar los datos en la tabla hash.

```cpp
void Blockchain::insertarEnTabla(const vector<Transaction> &transactions) {
  unordered_map<string, vector<Transaction>>::iterator it;
  //emisor
  for(int i = 0; i < transactions.size(); i++){
    string key = transactions[i].emisor;
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
    string key = transactions[i].receptor;
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
```
Para ejecutar la búsqueda se llama al método del blockchain denominado `buscarPorNombre(string &nombre)` que recibe el nombre buscado y retorna un vector de transacciones asociados a dicho nombre.

```cpp
vector<Transaction> Blockchain::buscarPorNombre(const string &nombre) {
  vector<Transaction> _transactions;
  unordered_map<string, std::vector<Transaction>>::iterator it = personTable.find(nombre);
  if (it != personTable.end()) {
    _transactions = it->second;
    }
  return _transactions;
}
```
### Búsqueda por fechas
Para realizar la búsqueda por fechas primero se indexan los datos en una arbol binario de busqueda que usa como key la fecha de la transaccion y como value un vector de transacciones asociados a la fecha ingresada.

Para el caso del proyecto la fecha se registra en el formato 'YYYY-MM-DD'.

En el siguiente código se muestra el método para indexar los datos en el arbol binario de búsqueda.
```cpp
void Blockchain::insertarByDate(const vector<Transaction> &transactions){
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
```
**- Búsqueda por una fecha exacta**
Para ejecutar la búsqueda se llama al método del blockchain denominado `buscarPorFecha(string& fecha)` que recibe la fecha buscada y retorna un vector de transacciones asociados a dicha fecha.
```cpp
vector<Transaction> Blockchain::buscarPorFecha(const string& fecha){
    vector<Transaction> output;
    map<string, vector<Transaction> >::iterator it;
    it = this->dateMap.find(fecha);
    if(it != dateMap.end()){
        output = it->second;
    }
    return output;
  }
```
**- Búsqueda por un rango de fechas**
Para ejecutar la búsqueda por rango se llama al método del blockchain denominado `buscarPorRangoDeFechas(string startDate, string endDate)` que recibe una fecha inicial y una fecha final y retorna un vector de transacciones con fechas en el rango seleccionado.
```cpp
vector<vector<Transaction>> Blockchain::buscarPorRangoDeFechas(string startDate, string endDate) {
    vector<vector<Transaction>> output;
    map<string, vector<Transaction> >::iterator start;
    map<string, vector<Transaction> >::iterator _end;
    start = dateMap.lower_bound(startDate);
    _end = dateMap.upper_bound(endDate);
    for ( map<string, vector<Transaction> >::iterator it = start; it != _end; ++it) {
        output.push_back(it->second);
    }
    return output;
}

```

## Complejidad de los métodos
## Conclusiones
## Referencias bibliográficas
