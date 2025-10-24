/*Implementa una agenda de contactos simple utilizando una lista enlazada. El
programa debe permitir:

> Insertar contacto: Agrega un nuevo contacto (nombre y tel ́efono) a la lista.
> Eliminar contacto: Elimina un contacto por su nombre.
> Mostrar contactos: Muestra todos los contactos en la agenda.
*/

#include <iostream>
#include <string>
using namespace std;

// Nodo de la lista enlazada
struct Contacto {
    string nombre;
    string telefono;
    Contacto* next;
};

// Clase Agenda
class Agenda {
private:
    Contacto* head;

public:
    Agenda() { head = nullptr; }

    // Insertar contacto al inicio de la lista
    void insertarContacto(const string& nombre, const string& telefono) {
        Contacto* nuevo = new Contacto();
        nuevo->nombre = nombre;
        nuevo->telefono = telefono;
        nuevo->next = head;
        head = nuevo;
        cout << "Contacto agregado: " << nombre << " - " << telefono << endl;
    }

    // Eliminar contacto por nombre
    void eliminarContacto(const string& nombre) {
        if (head == nullptr) {
            cout << "La agenda está vacía.\n";
            return;
        }

        // Si el contacto está en la cabeza
        if (head->nombre == nombre) {
            Contacto* temp = head;
            head = head->next;
            delete temp;
            cout << "Contacto " << nombre << " eliminado.\n";
            return;
        }

        // Buscar en el resto de la lista
        Contacto* actual = head;
        while (actual->next != nullptr && actual->next->nombre != nombre) {
            actual = actual->next;
        }

        if (actual->next == nullptr) {
            cout << "Contacto no encontrado.\n";
        } else {
            Contacto* temp = actual->next;
            actual->next = temp->next;
            delete temp;
            cout << "Contacto " << nombre << " eliminado.\n";
        }
    }

    // Mostrar todos los contactos
    void mostrarContactos() {
        if (head == nullptr) {
            cout << "La agenda está vacía.\n";
            return;
        }

        cout << "\n--- Lista de Contactos ---\n";
        Contacto* actual = head;
        while (actual != nullptr) {
            cout << "Nombre: " << actual->nombre << ", Teléfono: " << actual->telefono << endl;
            actual = actual->next;
        }
        cout << "---------------------------\n";
    }
};

// ==========================
// Programa principal con menú
// ==========================
int main() {
    Agenda agenda;
    int opcion;
    string nombre, telefono;

    do {
        cout << "\n===== MENU AGENDA =====\n";
        cout << "1. Insertar contacto\n";
        cout << "2. Eliminar contacto\n";
        cout << "3. Mostrar contactos\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // limpiar buffer

        switch (opcion) {
            case 1:
                cout << "Ingrese nombre: ";
                getline(cin, nombre);
                cout << "Ingrese teléfono: ";
                getline(cin, telefono);
                agenda.insertarContacto(nombre, telefono);
                break;

            case 2:
                cout << "Ingrese el nombre del contacto a eliminar: ";
                getline(cin, nombre);
                agenda.eliminarContacto(nombre);
                break;

            case 3:
                agenda.mostrarContactos();
                break;

            case 4:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 4);

    return 0;
}