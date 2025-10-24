/*
Implementa un directorio telef ́onico utilizando una tabla hash. El programa debe
permitir:
> Agregar contacto: Almacena un nombre (clave) y un n ́umero de tel ́efono (valor).
> Buscar contacto: Busca un n ́umero de tel ́efono a partir de un nombre.
*/

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    unordered_map<string, string> directorio; // nombre -> teléfono
    int opcion;

    do {
        cout << "\n1. Agregar contacto\n";
        cout << "2. Buscar contacto\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion : ";
        cin >> opcion;
        cin.ignore(); // limpiar buffer

        if (opcion == 1) {
            string nombre, telefono;
            cout << "Ingrese nombre : ";
            getline(cin, nombre);
            cout << "Ingrese telefono : ";
            getline(cin, telefono);

            directorio[nombre] = telefono;
            cout << "Contacto agregado." << endl;

        } else if (opcion == 2) {
            string nombre;
            cout << "Ingrese nombre a buscar : ";
            getline(cin, nombre);

            auto it = directorio.find(nombre);
            if (it != directorio.end()) {
                cout << "Telefono : " << it->second << endl;
            } else {
                cout << "Contacto no encontrado." << endl;
            }

        } else if (opcion == 3) {
            cout << "Saliendo..." << endl;
        } else {
            cout << "Opcion invalida." << endl;
        }

    } while (opcion != 3);

    return 0;
}
