/*
Escribe un programa que determine si una cadena de texto que contiene par ́entesis
(), corchetes [] y llaves {} est ́a balanceada. Una cadena est ́a balanceada si cada s ́ımbolo de apertura
tiene su correspondiente s ́ımbolo de cierre en el orden correcto.
*/

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

    // Agrega un elemento a la cima
    void push(char newData) {
        NodePila* newNode = new NodePila();
        newNode->data = newData;
        newNode->next = head;
        head = newNode;
    }

    // Elimina el elemento de la cima
    void pop() {
        if (head == nullptr) return;
        NodePila* temp = head;
        head = head->next;
        delete temp;
    }

    // Devuelve el elemento de la cima
    char top() {
        if (head == nullptr) return '\0';
        return head->data;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

// Función para validar balanceo
bool estaBalanceado(const string& expr) {
    Pila pila;

    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            pila.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (pila.isEmpty()) return false;

            char top = pila.top();
            pila.pop();

            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return pila.isEmpty();
}

// Programa principal
int main() {
    string expresion;

    cout << "1 Ingrese la expresion : ";
    getline(cin, expresion); // permite leer con espacios

    if (estaBalanceado(expresion)) {
        cout << "2 La expresion esta balanceada." << endl;
    } else {
        cout << "2 La expresion NO esta balanceada." << endl;
    }

    return 0;
}


