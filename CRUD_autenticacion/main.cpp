#include <iostream>
#include <fstream>
#include <cstdlib>
#include "usuarios.h"
#include "bitacora.h"
#include "aplicaciones.h"   // nuestra clase Bodega

using namespace std;

Usuarios sesion;

void menuInformes() {
    int op;
    do {
        system("cls");
        cout << "\n\t\t============================================\n";
        cout << "\t\t           SUBMENÚ DE INFORMES\n";
        cout << "\t\t============================================\n";
        cout << "\t\t1. Generar reporte de bodegas (TXT)\n";
        cout << "\t\t2. Regresar al menú principal\n";
        cout << "\t\t--------------------------------------------\n";
        cout << "\t\tOpción: ";
        cin >> op;
        cin.ignore();

        if (op == 1) {
            // Generar reporte desde el archivo binario bodega.dat a un TXT
            ifstream file("bodega.dat", ios::binary);
            ofstream reporte("reporte_bodegas.txt");
            if (!file) {
                reporte << "No hay bodegas registradas.\n";
            } else {
                RegistroBodega reg;
                reporte << "=== REPORTE DE BODEGAS ===\n";
                while (file.read(reinterpret_cast<char*>(&reg), sizeof(RegistroBodega))) {
                    reporte << "ID: " << reg.id << " | Nombre: " << reg.nombre << " | Estatus: " << reg.estatus << endl;
                }
            }
            file.close();
            reporte.close();

            cout << "\nReporte generado: reporte_bodegas.txt\n";
            cout << "\n--- CONTENIDO ---\n";
            ifstream ver("reporte_bodegas.txt");
            string linea;
            while (getline(ver, linea)) cout << linea << endl;
            ver.close();
            system("pause");
        }
    } while (op != 2);
}

void menuSeguridad() {
    int op;
    do {
        system("cls");
        cout << "\n\t\t============================================\n";
        cout << "\t\t           SUBMENÚ DE SEGURIDAD\n";
        cout << "\t\t============================================\n";
        cout << "\t\t1. Consultar bitácora\n";
        cout << "\t\t2. Regresar al menú principal\n";
        cout << "\t\t--------------------------------------------\n";
        cout << "\t\tOpción: ";
        cin >> op;
        cin.ignore();

        if (op == 1) {
            Bitacora::mostrarTodos();
        }
    } while (op != 2);
}

void menuGeneral() {
    int opcion;
    do {
        system("cls");
        cout << "\n\t\t==================================================\n";
        cout << "\t\t    SISTEMA DE GESTIÓN - MENÚ PRINCIPAL\n";
        cout << "\t\t==================================================\n";
        cout << "\t\tUsuario: " << sesion.getNombreCompleto()
             << " | Carné: " << sesion.getCarnet() << endl;
        cout << "\t\t--------------------------------------------------\n";
        cout << "\t\t1. Catálogos (CRUD de bodegas)\n";
        cout << "\t\t2. Informes (generar reporte TXT)\n";
        cout << "\t\t3. Seguridad (bitácora)\n";
        cout << "\t\t4. Salir del sistema\n";
        cout << "\t\t--------------------------------------------------\n";
        cout << "\t\tOpción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                Bodega bodega(sesion.getNombreUsuario());
                bodega.menu();
                break;
            }
            case 2:
                menuInformes();
                break;
            case 3:
                menuSeguridad();
                break;
            case 4:
                cout << "\nSaliendo...\n";
                Bitacora::registrar(sesion.getNombreUsuario(), "LOGOUT", "100");
                break;
            default:
                cout << "\nOpción no válida.\n";
                system("pause");
        }
    } while (opcion != 4);
}

int main() {
    Usuarios::crearArchivoSiNoExiste();
    if (sesion.login()) {
        menuGeneral();
    }
    return 0;
}
