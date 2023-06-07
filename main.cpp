/*#include <iostream>
#include <vector>
#include "Usuario.h"
#include "Transferencia.h"
#include "Blockchain.h"
#define FOR(i, n) for(int i=0; i<n; i++)
using namespace std;

   // Authors: Proyecto 1 - Grupal - UTEC

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

    //Busqueda por fecha (obtener Transferencias por fecha)
    string date = "23-05-2023";
    c = 0;
    transferencias = block_chain.find_by_date(date);
    cout << "+++ Transferencias en la fecha: " + date << " +++" << endl;
    for(Transferencia t : transferencias){
        cout << "#" << ++c << endl;
        cout << t.toString() << endl;
    }

    //Busqueda por rango de fechas (obtener Transferencias en un rango de fechas)
    string startDate = "19-05-2023";
    string endDate = "23-05-2023";
    c = 0;
    vector<vector<Transferencia>> transferencias_list = block_chain.getTransactionsInRange(startDate,endDate);
    cout << "+++ Transferencias realizadas entre " + startDate <<" y "<<endDate << " +++" << endl;
    for(vector<Transferencia> t_list : transferencias_list){
        for(Transferencia t : t_list){
            cout << "#" << ++c << endl;
            cout << t.toString() << endl;
        }
    }

  // Búsqueda por rango de monto
  long begin = 700;
  long end = 900;
  int c2 = 0;
  vector<Transferencia> transferencias_rango =
      block_chain.find_by_range(begin, end);
  cout << "+++ Transferencias dentro del rango de monto [" << begin << ", "
       << end << "] +++" << endl;
  for (Transferencia t : transferencias_rango) {
    cout << "#" << ++c2 << endl;
    cout << t.toString() << endl;
  }

  // Búsqueda máximo
  string name_max = "Pepito";
  int c3 = 0;
  Transferencia transferencia_max = block_chain.find_max_by_name(name_max);
  cout << "+++ Transferencia del monto maximo +++" << endl;
  cout << "#" << ++c3 << endl;
  cout << transferencia_max.toString() << endl;

  // Búsqueda mínimo
  string name_min = "Pepito";
  int c4 = 0;
  Transferencia transferencia_min = block_chain.find_min_by_name(name_min);
  cout << "+++ Transferencia del monto minimo +++" << endl;
  cout << "#" << ++c4 << endl;
  cout << transferencia_min.toString() << endl;

    return 0;
}
*/

#include "Blockchain.h"
#include "Transferencia.h"
#include "Usuario.h"
#include <iostream>
#include <vector>
#define FOR(i, n) for (int i = 0; i < n; i++)
using namespace std;
/*
    Authors: Proyecto 1 - Grupal - UTEC
*/

Blockchain block_chain;

// 1.Mostrar Bloques
void MostrarBloques() {
  //Blockchain block_chain;
  for (auto item : block_chain.block_list)
    cout << item.second.getData() << endl;
}

//Registro usuarios
Usuario registrousuarios(){
    string nomUsuario;
    string apUsuario;
    string dniUsuario;

    cout<<"Nombre del usuario: ";
    cin>>nomUsuario;
    cout<<"apellido del usuario: ";
    cin>>apUsuario;
    cout<<"DNI del usuario";
    cin>>dniUsuario;

    Usuario u (nomUsuario,apUsuario,dniUsuario);
    return u;
}

// 2. Registro de nueva transferencia
void registroTransferencia(vector<Transferencia> &transferencias){
    /*do {
        cout<<"¿Desea registrar usuario para la transferencia? (Y / N)"<<endl;
        cin>>char rpta;
        if(rpta == 'Y' || rpta == 'y'){
            registrousuarios(usuarios);
        }
    } while (rpta == 'Y' || rpta == 'y');
    */
    string fecha;
    double monto;
    string lugar;

    cout<<"Ingrese los datos del emisor";
    Usuario u1 = registrousuarios();

    cout<<"Ingrese los datos del receptor";
    Usuario u2 = registrousuarios();

    cout<<"Ingrese los datos de la transferencia:"<<endl;
    cout<<"Ingrese monto: ";
    cin>>monto;

    cout<<"\nIngrese fecha (dd-mm-yyyy): ";
    cin>>fecha;

    cout<<"\nIngrese lugar: ";
    cin>>lugar;

    Transferencia t(u1,u2,monto,fecha,lugar);
    transferencias.push_back(t);

    block_chain.add_block(transferencias);
}


// 3.

// 4.Busqueda por DNI (obtener Transferencias por DNI)
void BuscarDNI(string dni) {
  // string dni = "78955516";
  //Blockchain block_chain;
  int c = 0;
  vector<Transferencia> transferencias = block_chain.find_by_dni(dni);
  cout << "+++ Transferencias del DNI: " + dni << " +++" << endl;
  for (Transferencia t : transferencias) {
    cout << "#" << ++c << endl;
    cout << t.toString() << endl;
  }
}

// 5.Busqueda por nombre (obtener Transferencias por nombre)
void BuscarNombre(string name) {
  // string name = "Ana";
  //Blockchain block_chain;
  int c = 0;
  vector<Transferencia> transferencias = block_chain.find_by_name(name);
  cout << "+++ Transferencias de " + name << " +++" << endl;
  for (Transferencia t : transferencias) {
    cout << "#" << ++c << endl;
    cout << t.toString() << endl;
  }
}

// 6.Busqueda por fecha (obtener Transferencias por fecha)
void BuscarFecha(string date) {
  // string date = "23-05-2023";
  //Blockchain block_chain;
  int c = 0;
  vector<Transferencia> transferencias = block_chain.find_by_date(date);
  cout << "+++ Transferencias en la fecha: " + date << " +++" << endl;
  for (Transferencia t : transferencias) {
    cout << "#" << ++c << endl;
    cout << t.toString() << endl;
  }
}

// 7.Busqueda por rango de fechas (obtener Transferencias en un rango de fechas)
void BuscarRangoFecha(string startDate, string endDate) {
  // string startDate = "19-05-2023";
  // string endDate = "23-05-2023";
  //Blockchain block_chain;
  int c = 0;
  vector<vector<Transferencia>> transferencias_list =
      block_chain.getTransactionsInRange(startDate, endDate);
  cout << "+++ Transferencias realizadas entre " + startDate << " y " << endDate
       << " +++" << endl;
  for (vector<Transferencia> t_list : transferencias_list) {
    for (Transferencia t : t_list) {
      cout << "#" << ++c << endl;
      cout << t.toString() << endl;
    }
  }
}

// 8.Búsqueda monto máximo
void BuscarMontoMaximo(string name) {
  // string name_max = "Pepito";
  int c = 0;
  //Blockchain block_chain;
  Transferencia transferencia_max = block_chain.find_max_by_name(name);
  cout << "+++ Transferencia del monto maximo +++" << endl;
  cout << "#" << ++c << endl;
  cout << transferencia_max.toString() << endl;
}

// 9.Búsqueda monto mínimo
void BuscarMontoMinimo(string name) {
  // string name_min = "Pepito";
  int c = 0;
  //Blockchain block_chain;
  Transferencia transferencia_min = block_chain.find_min_by_name(name);
  cout << "+++ Transferencia del monto minimo +++" << endl;
  cout << "#" << ++c << endl;
  cout << transferencia_min.toString() << endl;
}

// 10.Búsqueda por rango de monto
void BuscarRangoMonto(long begin, long end) {
  // long begin = 700;
  // long end = 900;
  int c = 0;
  //Blockchain block_chain;
  vector<Transferencia> transferencias_rango =
      block_chain.find_by_range(begin, end);
  cout << "+++ Transferencias dentro del rango de monto [" << begin << ", "
       << end << "] +++" << endl;
  for (Transferencia t : transferencias_rango) {
    cout << "#" << ++c << endl;
    cout << t.toString() << endl;
  }
}

int main() {

  //Blockchain block_chain;
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

  int opc;
  cout << "======================================"<<endl;
  cout<<"||\tBienvenido a su Cajero Virtual\t||" << endl;
  cout << "======================================"<<endl;
  cout << "1. Mostrar todas las transacciones" << endl;
  cout << "2. Ingresar nueva transferencia" << endl;
  cout << "3. Cargar desde un archivo" << endl;
  cout << "4. Buscar por DNI" << endl;
  cout << "5. Buscar por nombre de emisor, receptor" << endl;
  cout << "6. Buscar por fecha" << endl;
  cout << "7. Buscar según un rango de fecha" << endl;
  cout << "8. Buscar el monto máximo según emisor, receptor" << endl;
  cout << "9. Buscar el monto mínimo según emisor, receptor" << endl;
  cout << "10. Buscar según un rango de monto" << endl;
  cout << "11. Salir" << endl;
  cout << "Ingrese opcion: ";
  cin >> opc;
  cout << endl;

switch (opc) {
  case 1: {
    MostrarBloques();
    break;
  }
  case 2: {
    registroTransferencia(trans_list);
    break;
  }
  case 3: {
    // PENDIENTE DE IMPLEMENTAR
    break;
  }
  case 4: {
    string dni;
    cout << "Digite el número de DNI: ";
    cin >> dni;
    BuscarDNI(dni);
    break;
  }
  case 5: {
    string nombre;
    cout << "Digite el nombre: ";
    cin >> nombre;
    BuscarNombre(nombre);
    break;
  }
  case 6: {
    string fecha;
    cout << "Digite la fecha: ";
    cin >> fecha;
    BuscarFecha(fecha);
    break;
  }
  case 7: {
    string fecha_ini;
    cout << "Digite la fecha de inicio: ";
    cin >> fecha_ini;
    string fecha_fin;
    cout << "Digite la fecha de fin: ";
    cin >> fecha_fin;
    BuscarRangoFecha(fecha_ini, fecha_fin);
    break;
  }
  case 8: {
    string nombre;
    cout << "Digite el nombre: ";
    cin >> nombre;
    BuscarMontoMinimo(nombre);
    break;
  }
  case 9: {
    string nombre;
    cout << "Digite el nombre: ";
    cin >> nombre;
    BuscarMontoMaximo(nombre);
    break;
  }
  case 10: {
    long begin;
    cout << "Digite el rango inferior del monto: ";
    cin >> begin;
    long end;
    cout << "Digite el rango superior del monto: ";
    cin >> end;
    BuscarRangoMonto(begin, end);
    break;
  }
  case 11:
    break;
}

char rpta;

do{
    cout<<"¿Desea realizar otra operacion? (Y / N)"<<endl;
    cin>>rpta;
    cout<<endl;

    if (rpta != 'Y'){
        cout<<"El programa ha terminado...";
    }
    cout << "\n\nIngrese opcion: ";
    cin >> opc;
    cout << endl;

    switch (opc) {
      case 1: {
        MostrarBloques();
        break;
      }
      case 2: {
        // PENDIENTE DE IMPLEMENTAR
        break;
      }
      case 3: {
        // PENDIENTE DE IMPLEMENTAR
        break;
      }
      case 4: {
        string dni;
        cout << "Digite el número de DNI: ";
        cin >> dni;
        BuscarDNI(dni);
        break;
      }
      case 5: {
        string nombre;
        cout << "Digite el nombre: ";
        cin >> nombre;
        BuscarNombre(nombre);
        break;
      }
      case 6: {
        string fecha;
        cout << "Digite la fecha: ";
        cin >> fecha;
        BuscarFecha(fecha);
        break;
      }
      case 7: {
        string fecha_ini;
        cout << "Digite la fecha de inicio: ";
        cin >> fecha_ini;
        string fecha_fin;
        cout << "Digite la fecha de fin: ";
        cin >> fecha_fin;
        BuscarRangoFecha(fecha_ini, fecha_fin);
        break;
      }
      case 8: {
        string nombre;
        cout << "Digite el nombre: ";
        cin >> nombre;
        BuscarMontoMinimo(nombre);
        break;
      }
      case 9: {
        string nombre;
        cout << "Digite el nombre: ";
        cin >> nombre;
        BuscarMontoMaximo(nombre);
        break;
      }
      case 10: {
        long begin;
        cout << "Digite el rango inferior del monto: ";
        cin >> begin;
        long end;
        cout << "Digite el rango superior del monto: ";
        cin >> end;
        BuscarRangoMonto(begin, end);
        break;
      }
      case 11:
        break;
}
} while (rpta == 'Y');

  return 0;
}
