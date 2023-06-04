#include <iostream>
#include <vector>
#include "Usuario.h"
#include "Transferencia.h"
#include "Blockchain.h"
#define FOR(i, n) for(int i=0; i<n; i++)
using namespace std;
/*
    Authors: Proyecto 1 - Grupal - UTEC
*/
int main() {
    Blockchain block_chain;
    Usuario u1("Marvin", "Minsky", "71480315");
    Usuario u2("Juan", "Perez", "12789345");
    Usuario u3("Ana", "Holeman", "78955516");
    Usuario u4("Pepito", "Grillo", "78934516");
    Transferencia t1(u1, u2, 1000.0, "18-05-2023", "Barranco");
    Transferencia t2(u1, u3, 200.0, "19-05-2023", "Surco");
    Transferencia t3(u1, u2, 520.0, "21-05-2023", "San Isidro");
    Transferencia t4(u3, u1, 890.0, "23-05-2023", "SJM");
    Transferencia t5(u3, u4, 2500.0, "25-05-2023", "Magdalena");

    vector<Transferencia> trans_list;
    trans_list.push_back(t1);
    trans_list.push_back(t2);
    trans_list.push_back(t3);
    trans_list.push_back(t4);
    block_chain.add_block(trans_list);

    vector<Transferencia> trans_list2;
    trans_list2.push_back(t1);
    trans_list2.push_back(t3);
    block_chain.add_block(trans_list2);

    vector<Transferencia> trans_list3;
    trans_list3.push_back(t5);
    trans_list3.push_back(t1);
    block_chain.add_block(trans_list3);

    //Mostrar Bloques
    for(auto item : block_chain.block_list)
        cout << item.second.getData() << endl;

    //Busqueda por nombre (obtener Transferencias por nombre)
    string name = "Ana";
    int c = 0;
    vector<Transferencia> transferencias = block_chain.find_by_name(name);
    cout << "+++ Transferencias de " + name << " +++" << endl;
    for(Transferencia t : transferencias){
        cout << "#" << ++c << endl;
        cout << t.toString() << endl;
    }

    //Busqueda por DNI (obtener Transferencias por DNI)
    string dni = "78955516";
    c = 0;
    transferencias = block_chain.find_by_dni(dni);
    cout << "+++ Transferencias del DNI: " + dni << " +++" << endl;
    for(Transferencia t : transferencias){
        cout << "#" << ++c << endl;
        cout << t.toString() << endl;
    }


    return 0;
}
