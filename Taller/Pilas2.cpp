//Utilizando una pila, crea un programa que invierta una cadena de caracteres.

#include <iostream>
#include <string>
using namespace std;

// Nodo para la pila
struct NodePila {
    char data;
    NodePila* next;
};

// Clase Pila
class Pila {
private:
    NodePila* head;

public:
    Pila() { head = nullptr; }

    // Apilar
    void push(char newData) {
        NodePila* newNode = new NodePila();
        newNode->data = newData;
        newNode->next = head;
        head = newNode;
    }

    // Desapilar
    char pop() {
        if (head == nullptr) return '\0'; // pila vacía
        NodePila* temp = head;
        char value = temp->data;
        head = head->next;
        delete temp;
        return value;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

// Función para invertir cadena
string invertirCadena(const string& texto) {
    Pila pila;
    // Apilar todos los caracteres
    for (char c : texto) {
        pila.push(c);
    }

    // Desapilar y reconstruir al revés
    string invertida;
    while (!pila.isEmpty()) {
        invertida += pila.pop();
    }

    return invertida;
}

// Programa principal
int main() {
    string cadena;

    cout << "Ingrese una cadena: ";
    getline(cin, cadena);

    string resultado = invertirCadena(cadena);

    cout << "Cadena invertida: " << resultado << endl;

    return 0;
}
