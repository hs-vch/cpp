/*
Representa un polinomio usando una lista enlazada, donde cada nodo almacena
el coeficiente y el exponente de un termino. El programa debe permitir sumar dos polinomios.
*/


#include <iostream>
using namespace std;

// Nodo para representar un término del polinomio
struct Termino {
    int coef;
    int exp;
    Termino* next;
};

// Clase Polinomio
class Polinomio {
private:
    Termino* head;

public:
    Polinomio() { head = nullptr; }

    // Insertar término al inicio
    void insertar(int coef, int exp) {
        if (coef == 0) return; // no guardamos términos nulos
        Termino* nuevo = new Termino();
        nuevo->coef = coef;
        nuevo->exp = exp;
        nuevo->next = head;
        head = nuevo;
    }

    // Mostrar polinomio
    void mostrar() {
        if (head == nullptr) {
            cout << "0";
            return;
        }
        Termino* actual = head;
        bool primero = true;
        while (actual != nullptr) {
            if (!primero && actual->coef > 0) cout << " + ";
            if (actual->coef < 0) cout << " - ";
            cout << (actual->coef < 0 ? -actual->coef : actual->coef) << "x^" << actual->exp;
            primero = false;
            actual = actual->next;
        }
        cout << endl;
    }

    // Sumar dos polinomios
    static Polinomio sumar(Polinomio& p1, Polinomio& p2) {
        Polinomio resultado;
        Termino* t1 = p1.head;
        Termino* t2 = p2.head;

        // Recorremos ambos polinomios
        while (t1 != nullptr || t2 != nullptr) {
            if (t2 == nullptr || (t1 != nullptr && t1->exp > t2->exp)) {
                resultado.insertar(t1->coef, t1->exp);
                t1 = t1->next;
            }
            else if (t1 == nullptr || t2->exp > t1->exp) {
                resultado.insertar(t2->coef, t2->exp);
                t2 = t2->next;
            }
            else {
                int sumaCoef = t1->coef + t2->coef;
                if (sumaCoef != 0) resultado.insertar(sumaCoef, t1->exp);
                t1 = t1->next;
                t2 = t2->next;
            }
        }
        return resultado;
    }

    // Leer polinomio desde consola
    void leer() {
        int c, e;
        while (true) {
            cout << "Ingrese coeficiente y exponente (0 0 para terminar): ";
            cin >> c >> e;
            if (c == 0 && e == 0) break;
            insertar(c, e);
        }
    }
};

// =====================
// Programa principal
// =====================
int main() {
    Polinomio p1, p2;

    cout << "Polinomio 1:" << endl;
    p1.leer();

    cout << "\nPolinomio 2:" << endl;
    p2.leer();

    cout << "\nPolinomio resultante: ";
    Polinomio resultado = Polinomio::sumar(p1, p2);
    resultado.mostrar();

    return 0;
}
