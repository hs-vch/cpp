/*
Escribe un programa que cuente la frecuencia de cada palabra en un texto. Utiliza
una tabla hash para almacenar las palabras y su frecuencia.
*/

#include <iostream>
#include <unordered_map>
#include <sstream>  // Para dividir el texto en palabras
using namespace std;

int main() {
    string texto;
    cout << "1 Ingrese un texto : ";
    getline(cin, texto);  // Leer toda la línea, incluyendo espacios

    unordered_map<string, int> frecuencia;
    string palabra;

    // Usamos stringstream para separar por espacios
    stringstream ss(texto);
    while (ss >> palabra) {
        frecuencia[palabra]++;  // Aumenta el contador de la palabra
    }

    cout << "2 Frecuencia de palabras :" << endl;
    for (auto& par : frecuencia) {
        cout << par.first << " : " << par.second << endl;
    }

    return 0;
}
