#include "blockchain.h"
#include <iostream>
#include<string>

using namespace std;

void BuscarNombre(std::string nombre, Blockchain blockchain){
  std::vector<Transaction> _transactions = blockchain.buscarPorNombre(nombre);
      int c = 0;
      std::cout << "\nTransacciones encontrados para '" << nombre << "':" << std::endl;
      for (Transaction t : _transactions) {
        std::cout << "#" << ++c << endl;
        std::cout << t.toString() << endl;
      }
};

void BuscarFecha(std::string fecha, Blockchain blockchain){
  int c = 0;
  vector<Transaction> transferencias = blockchain.buscarPorFecha(fecha);
  cout << "+++ Transferencias en la fecha: " + fecha << " +++" << endl;
  for (Transaction t : transferencias) {
    cout << "#" << ++c << endl;
    cout << t.toString() << endl;
  }
}

void BuscarRangofechas(std::string startDate, std::string endDate, Blockchain blockchain){
  int c = 0;
  vector<vector<Transaction>> transferencias_list =
      blockchain.buscarPorRangoDeFechas(startDate, endDate);
  cout << "+++ Transferencias realizadas entre " + startDate << " y " << endDate
       << " +++" << endl;
  for (vector<Transaction> t_list : transferencias_list) {
    for (Transaction t : t_list) {
      cout << "#" << ++c << endl;
      cout << t.toString() << endl;
    }
  }
}

int main() {
  Blockchain blockchain(4);

  int opcion;
  char rpta;

  do {
    std::cout << std::endl;
    // std::cout << "======= MENU =======\n";
    std::cout << "======================================" << std::endl;
    std::cout << "||\tBienvenido a su Cajero Virtual\t||" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "1. Agregar transacción\n";
    std::cout << "2. Cargar desde CSV\n";
    std::cout << "3. Imprimir blockchain\n";
    std::cout << "4. Actualizar transacción\n";
    std::cout << "5. Buscar por nombre\n";
    std::cout << "6. Buscar por fecha\n";
    std::cout << "7. Buscar por rango de fechas\n";
    std::cout << "8. Buscar por monto máximo\n";
    std::cout << "9. Buscar por monto mínimo\n";
    std::cout << "10. Buscar por rango de monto\n";
    std::cout << "11. Salir\n\n";
    std::cout << "Ingrese una opción: ";
    std::cin >> opcion;
    std::cout << std::endl;

    switch (opcion) {
    case 1:
      blockchain.ingresarRegistro();
      break;
    case 2:
      blockchain.cargarDesdeCSV("transacciones.csv");
      break;
    case 3:
      blockchain.imprimirBlockchain();
      break;
    case 4: {
      int bloque;
      std::cout << "Ingrese el bloque: ";
      std::cin >> bloque;
      int transaccion;
      std::cout << "Ingrese el número de transacción: ";
      std::cin >> transaccion;
      std::string emisor;
      std::cout << "Emisor: ";
      std::cin >> emisor;
      std::string receptor;
      std::cout << "Receptor: ";
      std::cin >> receptor;
      double monto;
      std::cout << "Monto: ";
      std::cin >> monto;
      std::string fecha;
      std::cout << "Fecha: ";
      std::cin >> fecha;
      std::string ciudad;
      std::cout << "Ciudad: ";
      std::cin >> ciudad;
      blockchain.actualizarRegistro(bloque, transaccion, emisor, receptor,
                                    monto, fecha, ciudad);

      blockchain.imprimirBlockchain();
      break;
    }
    case 5: {
      std::string nombre;
      std::cout << "Ingrese el nombre: ";
      std::cin.ignore();
      std::getline(std::cin,nombre);
      BuscarNombre(nombre, blockchain);
      std::cout << std::endl;
      break;
    }
    case 6:{
      std::string fecha;
      std::cout<<"Ingrese fecha: ";
      std::cin.ignore();
      std::getline(std::cin, fecha);
      BuscarFecha(fecha, blockchain);
      std::cout << std::endl;
      break;
    }
    case 7: {
      std::string fechaInicio, fechaFin;
      std::cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
      std::cin.ignore();
      std::getline(std::cin, fechaInicio);
      std::cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
      std::getline(std::cin, fechaFin);
      BuscarRangofechas(fechaInicio,fechaFin,blockchain);
      std::cout << std::endl;
      break;
    }
    case 8: {
      double montoMax;
      int i = 0;
      std::cout << "Ingrese el monto máximo: ";
      std::cin >> montoMax;
      std::vector<Transaction> bloquesMontoMax =
          blockchain.buscarPorMontoMaximo(montoMax);
      std::cout << "Bloques encontrados con monto máximo de " << montoMax << ":"
                << std::endl;
      for (const Transaction &transaccion : bloquesMontoMax) {
        std::cout << "\nTransacción #" << i
                << std::endl;
        std::cout << "Fecha: " << transaccion.fecha << std::endl;
        std::cout << "Fecha: " << transaccion.fecha << std::endl;
        std::cout << "Emisor: " << transaccion.emisor << std::endl;
        std::cout << "Receptor: " << transaccion.receptor << std::endl;
        std::cout << "Monto: " << transaccion.monto << std::endl;
        std::cout << "Ciudad: " << transaccion.ciudad << std::endl << "\n";
        //std::cout << std::endl;
        i++;
      }
      std::cout << std::endl;
      break;
    }
    case 9: {
      double montoMin;
      int i = 0;
      std::cout << "Ingrese el monto mínimo: ";
      std::cin >> montoMin;
      std::vector<Transaction> bloquesMontoMin =
          blockchain.buscarPorMontoMinimo(montoMin);
      std::cout << "Bloques encontrados con monto mínimo de " << montoMin << ":"
                << std::endl;
      for (const Transaction &transaccion : bloquesMontoMin) {
        std::cout << "\nTransacción #" << i
                << std::endl;
        std::cout << "Fecha: " << transaccion.fecha << std::endl;
        std::cout << "Fecha: " << transaccion.fecha << std::endl;
        std::cout << "Emisor: " << transaccion.emisor << std::endl;
        std::cout << "Receptor: " << transaccion.receptor << std::endl;
        std::cout << "Monto: " << transaccion.monto << std::endl;
        std::cout << "Ciudad: " << transaccion.ciudad << std::endl << "\n";
        //std::cout << std::endl;
        i++;
      }
      std::cout << std::endl;
      break;
    }
    case 10: {
      double montoMin, montoMax;
      int i = 0;
      std::cout << "Ingrese el monto mínimo: ";
      std::cin >> montoMin;
      std::cout << "Ingrese el monto máximo: ";
      std::cin >> montoMax;
      std::vector<Transaction> bloquesRangoMonto =
          blockchain.buscarPorRangoDeMonto(montoMin, montoMax);
      std::cout << "Bloques encontrados para el rango de monto [" << montoMin
                << ", " << montoMax << "]:" << std::endl;
      for (const Transaction &transaccion : bloquesRangoMonto) {
        std::cout << "\nTransacción #" << i
                << std::endl;
        std::cout << "Fecha: " << transaccion.fecha << std::endl;
        std::cout << "Fecha: " << transaccion.fecha << std::endl;
        std::cout << "Emisor: " << transaccion.emisor << std::endl;
        std::cout << "Receptor: " << transaccion.receptor << std::endl;
        std::cout << "Monto: " << transaccion.monto << std::endl;
        std::cout << "Ciudad: " << transaccion.ciudad << std::endl << "\n";
        //std::cout << std::endl;
        i++;
      }
      std::cout << std::endl;
      break;
    }
    case 11:
      std::cout << "Saliendo..." << std::endl;
      break;
    default:
      std::cout << "Opción inválida. Intente nuevamente." << std::endl;
    }

    do{
      cout << "\n¿Desea realizar otra operacion? (Y / N)  ";
      cin >> rpta;
    }while (rpta != 'Y' && rpta != 'N');

  } while (rpta == 'Y');

  return 0;
}
