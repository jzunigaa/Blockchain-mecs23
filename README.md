# SISTEMA DE TRANSACCIONES CON BLOCKCHAIN EN C++

Proyecto 01 del curso Estructuras de Datos, Maestría en Computer Science - UTEC 2023.

#### 1. Introducción
------------
El presente proyecto se encuentra desarrollado en C++ y tiene como objetivo principal simular un sistema de transacciones bancarias simples que almacenan la información al interior de una blockchain y otras estructuras que permitan la búsqueda eficiente de los datos almacenados...


#### 2. Descripción del caso de estudio planteado
------------
El proyecto requiere un sistema que permita registrar de forma segura y sencilla, transacciones que almacenen datos como: el nombre del emisor, nombre del receptor, monto de la transacción, fecha de la transacción y lugar de la transacción. Se requiere implementar una estructura blockchain que brinde seguridad al sistema y múltiples estructuras de indexación para la recuperación eficiente de informaicón. Estas transacciones se agrupan en bloques y se registran en la blockchain.

#### 3. Importancia del Blockchain en el dominio de datos elegido
------------
El blockchain es importante en el dominio de transferencia de dinero porque proporciona una forma segura y confiable de registrar las transacciones. La estructura descentralizada (no se aplicó en este proyecto) y las técnicas de encriptación de la blockchain garantizan la integridad de los datos y evitan la manipulación de las transacciones.


#### 4. Explicación de la estructura de datos del Blockchain y la estrategia para asegurar la integridad de su contenido
------------
La estructura de datos del blockchain se implementa utilizando una **lista cirucular doblemente enlazada** de bloques. Ésta se utiliza para mantener un orden secuencial de los bloques en el Blockchain, donde cada nodo de la lista enlazada contiene un bloque y enlaces al nodo anterior (prev) y siguiente (next). Además, el uso de head y tail en la lista enlazada brinda ventajas en términos de eficiencia y rendimiento. Al tener referencias directas al inicio y al final de la lista, se pueden realizar operaciones de inserción y eliminación de manera más eficiente, ya que no es necesario recorrer la lista completa en cada operación.

```cpp
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
```


Cada bloque de transacciones se representa mediante la estructura Block, que contiene información como el índice del bloque, el hash del bloque anterior, las transacciones incluidas en el bloque, el nonce (número utilizado en la minería) y el hash del bloque actual.

```cpp
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
```

Para asegurar la integridad del contenido, se utiliza el algoritmo de prueba de trabajo (proof of work). El proof of work implica calcular un hash para cada bloque de manera que cumpla con ciertos requisitos. En este caso, se busca un hash que tenga 4 ceros al principio. Para lograr esto, se incrementa el nonce y se recalcula el hash hasta encontrar un hash válido.

```cpp
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
```
Además, para ilustrar el efecto de recálculo en cascada, se consideró la posibilidad de modificar la información según el bloque y transacción que se indique.

```cpp
void Blockchain::recalcularHashesCascada(ListNode *node) {
  while (node != nullptr) {
    node->block.calcularHash(prefijo);
    node = node->next;
  }
}
```


#### 5. Explicación de cada una de las estructuras de datos utilizada en su aplicación de acuerdo a los criterios de búsqueda
------------
Se utilizan estructuras de datos para permitir búsquedas eficientes de bloques de transacciones en el blockchain basadas en diferentes criterios, como nombre, rango de fechas, monto máximo, etc. Las estructuras utilizadas son tablas hash, árbol binario de búsqueda.

#### Búsqueda por nombre

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

#### Búsqueda por fechas

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
#### Búsqueda por montos
Para realizar la búsqueda por montos, primero se insertan los registros en un BST, a través del método insertarEnBST. Cada bloque se inserta en el árbol de acuerdo con la fecha de la primera transacción en ese bloque. De esta manera, los bloques se organizan en orden cronológico dentro del árbol.

```cpp
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
```
**- Búsqueda por monto máximo**
La búsqueda por monto máximo consiste en encontrar todas las transacciones que tengan un monto menor o igual a un valor máximo especificado. En este caso, se recorre la estructura de datos y se compara el monto de cada transacción con el valor máximo. Todas las transacciones que cumplan con este criterio se consideran resultados de la búsqueda.

```cpp
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
```

**- Búsqueda por monto mínimo**
La búsqueda por monto mínimo, por otro lado, implica encontrar todas las transacciones que tengan un monto mayor o igual a un valor mínimo dado. Similar a la búsqueda por monto máximo, se recorre la estructura de datos y se compara el monto de cada transacción con el valor mínimo. Todas las transacciones que cumplan con este criterio se consideran resultados de la búsqueda.

```cpp
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
```

**- Búsqueda por rango de monto**
La búsqueda por rango de monto se utiliza para encontrar transacciones cuyos montos estén dentro de un rango específico, definido por un valor mínimo y un valor máximo. Durante esta búsqueda, se recorre la estructura de datos y se comparan los montos de las transacciones con los límites del rango. Todas las transacciones cuyos montos estén dentro del rango se consideran resultados de la búsqueda.

```cpp
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
```

#### 6. Análisis de la complejidad en notación Big O de los métodos del Blockchain
------------
La complejidad en notación Big O de los métodos del Blockchain se puede resumir de la siguiente manera:

**- agregarBloque**
O(n), donde n es el número de transacciones en el bloque.

**- insertarEnTabla**
O(n), donde n es el número de transacciones.

**- insertarByDate**
O(log n), donde n es el número de fechas en el mapa.

**- insertarEnBST**
O(log n), donde n es el número de nodos en el árbol.

**- imprimirBlockchain**
O(n), donde n es el número total de transacciones en todos los bloques.

**- ingresarRegistro**
O(m), donde m es el número de transacciones ingresadas por el usuario.

**- cargarDesdeCSV**
O(k), donde "k" es el número total de registros en el archivo CSV. Esto se debe a que se recorren todos los registros y se crean bloques cada vez que se acumulan 5 transacciones.

**- actualizarRegistro**
O(n), donde n es el número total de bloques en la cadena.

**- eliminarDeTabla**
O(n), donde n es el número de transacciones a eliminar.

**- eliminarDeBST**
O(log n), donde n es el número de nodos en el árbol.

**- recalcularHashesCascada**
O(m), donde m es el número de bloques en la cadena.

**- buscarPorNombre**
O(1) en el mejor caso y O(n) en el peor caso, donde n es el número de transacciones asociadas al nombre especificado.

**- buscarPorFecha**
O(1) en el mejor caso y O(n) en el peor caso, donde n es el número de transacciones asociadas a la fecha especificada.

**- buscarPorRangoDeFecha**
O(log n), donde n es el número total de fechas en el map.

**- buscarPorMontoMáximo**
O(log n), el valor máximo se encuentra en el nodo más a la derecha del árbol.

**- buscarPorMontoMínimo**
O(log n), el valor mínimo se encuentra en el nodo más a la derecha del árbol.

**- buscarPorRangoDeMonto**
O(log n), en promedio requerirá examinar un número de nodos proporcional a la altura del árbol, lo cual es logarítmico en relación al número total de nodos.

#### 7. Conclusiones
------------
- Blockchain proporciona un alto nivel de seguridad debido a su estructura y a la criptografía utilizada para asegurar las transacciones. Cada bloque contiene un hash que enlaza con el bloque anterior, lo que dificulta la manipulación de los datos.

- La implementación del proof of work, es un proceso para encontrar el nonce correcto que cumple con ciertos requisitos de dificultad. Esto asegura que la creación de nuevos bloques sea un proceso que requiere tiempo y esfuerzo, lo que dificulta la manipulación de la cadena.

- Se pueden implementar operaciones eficientes para buscar transacciones por emisor, receptor, rango de fechas y monto máximo. Esto facilita la búsqueda y el análisis de transacciones específicas en la cadena de bloques.

#### 8. Referencias bibliográficas
------------
- IBM - ¿Tecnología Blockchain?
https://www.ibm.com/es-es/topics/blockchain

- -NUCLIO - ¿Cómo aplican la tecnología blockchain los bancos?
https://nuclio.school/como-aplican-la-tecnologia-blockchain-los-bancos/

- GITHUB - PicsoSHA2
https://github.com/okdshin/PicoSHA2/blob/master/picosha2.h
