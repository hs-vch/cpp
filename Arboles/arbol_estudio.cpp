#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;


//Clase Nodo, valor dato, punteros

class Nodo
{
    public:
        int dato;
        Nodo *izquierdoPtr;
        Nodo *derechoPtr;
};

//Clase Arbol metodos 

class Arbol{

    private: 
        Nodo *raizPtr;
        bool esVacio();


    public:
        Arbol();
        ~Arbol();

        Nodo *regresaRaiz();
        void insertarNodo(int valor, Nodo *&nodoPtr);
        void muestraAcostado(int nivel, Nodo *nodoPtr);        
        bool busqueda (int x, Nodo *nodoPtr);
        Nodo *buscarMenor (Nodo *nodoPtr);
        Nodo *buscarMayor (Nodo *nodoPtr);
        void eliminarPredecesor (int x, Nodo *&nodoPtr);
        void eliminarSucesor (int x, Nodo *&nodoPtr);
        void preOrden(Nodo *nodoPtr);
        void inOrden(Nodo *nodoPtr);
        void postOrden(Nodo *nodoPtr);

        void recorridoNiveles(Nodo *nodoPtr);
        int altura(Nodo *nodoPtr);
        int contarHojas(Nodo *nodoPtr);
        int contarNodos(Nodo *nodoPtr);
        bool esCompleto(Nodo *nodoPtr);
        bool esLLeno(Nodo *nodoPtr);
        void podarArbol(Nodo *&nodoPtr);
};


//constructor

Arbol :: Arbol(){

    raizPtr = NULL;
}

//destructor

Arbol ::~Arbol(){
    podarArbol(raizPtr);
}

//metodo que corrobora si está vacio

bool Arbol::esVacio(){
    return raizPtr == NULL;
}

//metodo que accede a la raiz del arbol

Nodo *Arbol::regresaRaiz(){
    return raizPtr;
}

//Metodo insertar nodo

void Arbol::insertarNodo(int valor, Nodo *&nodoPtr){ 

    //Aquí se crea el nuevo nodo

    if (nodoPtr == NULL){

        nodoPtr = new Nodo();
        nodoPtr -> dato = valor;
        nodoPtr -> izquierdoPtr = NULL;
        nodoPtr -> derechoPtr = NULL;
    }

    //aquí se asigna si su valor es menor o mayor al nodo actual en el que estamos
    else if(valor < nodoPtr -> dato)
        insertarNodo (valor, nodoPtr -> izquierdoPtr);
    else if (valor > nodoPtr -> dato)
        insertarNodo (valor, nodoPtr -> derechoPtr);
}


// Metodo imprimir horizontal (giro de 90 grados mas o menos)
void Arbol :: muestraAcostado(int nivel, Nodo *nodoPtr){ 
    
    if (nodoPtr == NULL) 
     return; 
    
    muestraAcostado (nivel+1, nodoPtr -> derechoPtr); // primero imprime el numero a la derecha, espacio

    for(int i=0; i<nivel; i++)
        cout << " "; 
    
    cout << nodoPtr -> dato << endl; 

    muestraAcostado ( nivel+1, nodoPtr->izquierdoPtr); 
}



//Recorrido inOrden
void Arbol::inOrden(Nodo *nodoPtr){ 
    if(nodoPtr == NULL)
        return;


    inOrden(nodoPtr->izquierdoPtr);
    cout << nodoPtr -> dato << " - ";
    inOrden(nodoPtr->derechoPtr);
}


//Recorrido preOrden

void Arbol::preOrden(Nodo *nodoPtr){
    if(nodoPtr == NULL)
        return;


    cout << nodoPtr -> dato << " - ";
    preOrden(nodoPtr->izquierdoPtr);
    preOrden(nodoPtr->derechoPtr);
}

void Arbol::postOrden(Nodo *nodoPtr){ //Recorrido postOrden
    if(nodoPtr == NULL)
        return;

    postOrden(nodoPtr->izquierdoPtr);
    postOrden(nodoPtr->derechoPtr);
    cout << nodoPtr -> dato << " - ";
}



bool Arbol::busqueda(int x, Nodo *nodoPtr){

    if(nodoPtr == NULL)
        return false;
    else if(x < nodoPtr -> dato)
        return busqueda(x, nodoPtr -> izquierdoPtr);
    else if(x > nodoPtr->dato)
        return busqueda(x, nodoPtr->derechoPtr);
    else    
        return true;
}


// eliminar arbol

void Arbol::podarArbol (Nodo *&nodoPtr){
    if (nodoPtr == NULL)
        return;
    
    podarArbol(nodoPtr ->izquierdoPtr);

    podarArbol(nodoPtr->derechoPtr);

    delete nodoPtr;
    nodoPtr = NULL;
}



Nodo *Arbol:: buscarMenor(Nodo* nodoPtr){//Metodo de busqueda menor
    if (nodoPtr == NULL)
        return NULL;
    else if(nodoPtr -> izquierdoPtr == NULL)
        return nodoPtr;
    else 
        return buscarMenor(nodoPtr-> izquierdoPtr);
}

Nodo *Arbol:: buscarMayor(Nodo* nodoPtr){//Metodo de busqueda mayor
    if (nodoPtr == NULL)
        return NULL;
    else if(nodoPtr -> derechoPtr == NULL)
        return nodoPtr;
    else 
        return buscarMayor(nodoPtr-> derechoPtr);
}



void Arbol ::eliminarPredecesor(int x, Nodo *&nodoPtr){
    if (nodoPtr == NULL)
        return;
    else if (x < nodoPtr -> dato)
        eliminarPredecesor(x, nodoPtr->izquierdoPtr);
    else if(x > nodoPtr -> dato)
        eliminarPredecesor(x, nodoPtr -> derechoPtr);
    else if (nodoPtr -> izquierdoPtr && nodoPtr->derechoPtr)
    {
        Nodo* mayor = buscarMayor(nodoPtr -> izquierdoPtr);
        nodoPtr->dato = mayor -> dato;
        eliminarPredecesor(mayor->dato, nodoPtr->izquierdoPtr);
    }
    else
    {
        Nodo *temp = nodoPtr;
        if (nodoPtr -> izquierdoPtr == NULL)
        
            nodoPtr = nodoPtr -> derechoPtr;
        else if (nodoPtr -> derechoPtr == NULL)
            nodoPtr = nodoPtr-> izquierdoPtr;
        
        //Elimina el nodo
        delete temp;
    }
    
}

void Arbol::eliminarSucesor(int x, Nodo *&nodoPtr){

    if(nodoPtr == NULL)
        return;
    else if(x < nodoPtr -> dato)
        eliminarSucesor(x, nodoPtr -> izquierdoPtr);
    else if(x > nodoPtr -> dato)
        eliminarSucesor(x, nodoPtr -> derechoPtr);
    else if (nodoPtr -> izquierdoPtr && nodoPtr -> derechoPtr)
    {
        Nodo * menor = buscarMenor(nodoPtr ->derechoPtr);
        nodoPtr -> dato = menor -> dato;
        eliminarSucesor (menor->dato, nodoPtr->derechoPtr);
    }
    else
    {
        Nodo *temp = nodoPtr;
        if(nodoPtr -> izquierdoPtr == NULL)
            nodoPtr = nodoPtr -> derechoPtr;
        else if (nodoPtr -> derechoPtr == NULL)
            nodoPtr = nodoPtr -> izquierdoPtr;

        //Elimina el nodo hoja
        delete temp;
    }
}


int Arbol ::altura(Nodo *nodoPtr)
{
    if(nodoPtr == NULL)
        return 0;

    return ( 1 + max(altura(nodoPtr -> izquierdoPtr), altura(nodoPtr->derechoPtr)));

}

int Arbol :: contarHojas(Nodo * nodoPtr)
{
    if(nodoPtr == NULL)
        return 0;
    if(nodoPtr->derechoPtr==NULL && nodoPtr->izquierdoPtr==NULL)
        return 1;
    else 
        return contarHojas(nodoPtr->izquierdoPtr) + contarHojas(nodoPtr->derechoPtr);      
}

int Arbol :: contarNodos (Nodo *nodoPtr)
{
    if (nodoPtr == NULL)
        return 0;
    
    return 1 + contarNodos (nodoPtr -> izquierdoPtr) + contarNodos(nodoPtr -> derechoPtr);
    
}


void Arbol::recorridoNiveles(Nodo *nodoPtr)
{
    Nodo *nodoAuxiliar;                 // Creamos un puntero auxiliar que usaremos para recorrer los nodos.
    queue<Nodo*> colaAuxiliar;          // Creamos una cola de punteros a Nodo. La cola nos ayuda a procesar los nodos en orden de niveles.
    colaAuxiliar.push(nodoPtr);         // Insertamos la raíz del árbol en la cola. Es el primer nodo que procesaremos.

    while (!colaAuxiliar.empty())       // Mientras la cola no esté vacía...
    {
        nodoAuxiliar = colaAuxiliar.front();  // Tomamos el nodo que está al frente de la cola (el "primer" nodo de la cola).
        cout << nodoAuxiliar->dato << " - "; // Imprimimos su dato.
        colaAuxiliar.pop();                   // Lo eliminamos de la cola porque ya lo procesamos.

        if(nodoAuxiliar->izquierdoPtr != NULL)   // Si el nodo tiene hijo izquierdo...
            colaAuxiliar.push(nodoAuxiliar->izquierdoPtr); // Lo agregamos al final de la cola.

        if(nodoAuxiliar->derechoPtr != NULL)     // Si el nodo tiene hijo derecho...
            colaAuxiliar.push(nodoAuxiliar->derechoPtr);   // Lo agregamos al final de la cola.
    }
}

bool Arbol :: esLLeno(Nodo *nodoPtr)
{
    if(nodoPtr == NULL)
        return true;

    if(nodoPtr -> derechoPtr == NULL && nodoPtr -> izquierdoPtr== NULL)
        return true;

    if(nodoPtr -> derechoPtr && nodoPtr -> izquierdoPtr)
        return (esLLeno(nodoPtr->izquierdoPtr) && esLLeno(nodoPtr->derechoPtr));
    
    return false;
}

bool Arbol :: esCompleto(Nodo * nodoPtr)
{
    if(nodoPtr == NULL)
        return true;
    
    Nodo *nodoAuxiliar; 
    queue<Nodo*> colaAuxiliar;
    colaAuxiliar.push(nodoPtr);
    bool nodoNoLleno = false;

    while (! colaAuxiliar.empty())
    {
        nodoAuxiliar = colaAuxiliar.front();
        colaAuxiliar.pop();

        if(nodoAuxiliar ->izquierdoPtr){

            if(nodoNoLleno == true)
                return false;
            colaAuxiliar.push(nodoAuxiliar -> izquierdoPtr);
        }else{
            nodoNoLleno = true;
        }

        if(nodoAuxiliar -> derechoPtr){

            if (nodoNoLleno == true)
                return false;
            colaAuxiliar.push(nodoAuxiliar ->derechoPtr);
        }else{
            nodoNoLleno = true;
        }

    }
    return true;
}


void menu()
{
    system("cls");
    cout <<"\n      [ ARBOL BINARIO DE BÚSQUEDA ]..";
    cout <<"\n   [1] Insertar elemento..";
    cout <<"\n   [2] Buscar un elemento en el arbol..";
    cout <<"\n   [3] Recorrer el arbol en PreOrden..";
    cout <<"\n   [4] Recorrer el arbol en InOrden..";
    cout <<"\n   [5] Recorrer el arbol en PostOrden..";
    cout <<"\n   [6] Eliminar un nodo del arbol PREDECESOR..";
    cout <<"\n   [7] Eliminar un nodo del arbol SUCESOR..";
    cout <<"\n   [8] Recorrer el arbol por niveles (Amplitud)..";
    cout <<"\n   [9] Altura del arbol..";
    cout <<"\n   [10] Cantidad de hojas del arbol..";
    cout <<"\n   [11] Cantidad de nodos del arbol..";
    cout <<"\n   [12] Revisa si es un arbol binario completo..";
    cout <<"\n   [13] Revisa si es un arbol binario lleno..";
    cout <<"\n   [14] Eliminar el arbol..";
    cout <<"\nIngrese una opcion : ";
}


int main()
{
    int opcion;
    int valor;
    int x;

    Arbol arbolEnteros;
    Nodo *raizArbolPtr = arbolEnteros.regresaRaiz();

    Arbol arbolCopiaEnteros;
    Nodo *raizArbolCopiaPtr = arbolCopiaEnteros.regresaRaiz();


    system("color 1F");

    do
    {
        menu();
        cin >> opcion; 

        switch (opcion)
        {
        case 1:
            cout << "\nIngrese valor entero: ";
            cin >> valor;

            arbolEnteros.insertarNodo(valor, raizArbolPtr);

            cout << "\n Los elementos del arbol con la raiz a la izquierda son:\n\n";
            arbolEnteros.muestraAcostado(0, raizArbolPtr);
            cout << "\n\n";
            system("pause");
            break;

        case 2: 
            if( raizArbolPtr == NULL)
            {
                cout <<"\nEl arbol esta vacio.\n\n";
                system("pause");
                break;
            }

            cout << "\nIngrese valor entero: ";
            cin >> x;

            if(arbolEnteros.busqueda(x, raizArbolPtr) == true)
                cout << "\nElemento " << x << " ha sido encontrado en el arbol\n";
            else
                cout << "\nElemento no encontrado\n";
            
            cout << "\nLos elementos del arbol acostado con la raiz a la izquierda son:\n\n";
            arbolEnteros.muestraAcostado(0, raizArbolPtr );
            cout << "\n\n";
            system("pause");
            break;

        case 3:
            if(raizArbolPtr == NULL)
            {
                cout << "\nEl arbol esta vacio.\n\n";
                system("pause");
                break;
            }
            cout << "\nRecorrido en PreOrden: ";
            arbolEnteros.preOrden(raizArbolPtr);
            cout << "\n\n";
            system("pause");
            break;

        case 4:

            if(raizArbolPtr == NULL)
            {
                cout << "\nEl arbol esta vacio. \n\n";
                system("pause");
                break;
            }

            cout << "\nRecorrido en InOrden: ";
            arbolEnteros.inOrden(raizArbolPtr);
            cout << "\n\n";
            system("pause");
            break;

        case 5:

            if(raizArbolPtr == NULL)
            {
                cout << "\nEl arbol esta vacio.\n\n";
                system("pause");
                break;
            }

            cout << "\nRecorrido en postOrden: ";
            arbolEnteros.postOrden(raizArbolPtr);
            cout << "\n\n";
            system("pause");
            break;

        case 6:
            if(raizArbolPtr == NULL)
            {
                cout << "\nEl arbol esta vacio.\n\n";
                system("pause");
                break;
            }

            cout << "\nIngrese el valor entero a eliminar PREDECEOR: ";
            cin >> x;

            arbolEnteros.eliminarPredecesor(x, raizArbolPtr);

            cout << "\nLos elementos del arbol acostado con la raiz a la izquierda son:\n\n";
            arbolEnteros.muestraAcostado(0, raizArbolPtr);
            cout << "\n\n";
            system("pause");
            break;

        case 7:
            if(raizArbolPtr == NULL)
            {
                cout << "\nEl arbol esta vacio.\n\n";
                system("pause");
                break;
            }

            cout << "\nIngrese el valor entero a eliminar SUCESOR: ";
            cin >> x;

            arbolEnteros.eliminarSucesor(x, raizArbolPtr);

            cout << "\nLos elementos del arbol acostado con la raiz a la izquierda son:\n\n";
            arbolEnteros.muestraAcostado(0, raizArbolPtr);
            cout << "\n\n";
            system("pause");
            break;

        case 8:

            cout << "\nRecorrido por niveles: ";
            arbolEnteros.recorridoNiveles(raizArbolPtr);

            cout << "\n\n";
            system("pause");
            break;

        case 9: 
            cout << "\nLa altura del arbol es: " << arbolEnteros.altura(raizArbolPtr);

            cout << "\n\n";
            system("pause");
            break;

        case 10:

            cout << "\nEl numero de hojas del arbol es: " << arbolEnteros.contarHojas(raizArbolPtr);

            cout << "\n\n";
            system("pause");
            break;

        case 11:

            cout << "\nEl numero de nodos del arbol es: " << arbolEnteros.contarNodos(raizArbolPtr);

            cout << "\n\n";
            system("pause");
            break;

        case 12:

            cout << "\nLos elementos del arbol acostado con la raiz a la izquierda son:\n\n";
            arbolEnteros.muestraAcostado(0, raizArbolPtr);
            cout << "\n\n";

            if(arbolEnteros.esCompleto(raizArbolPtr))
                cout << "\nSi es un arbol binario completo.";
            else
                cout << "\nNo es un arbol binario completo.";

            cout << "\n\n";
            system("pause");
            break;

        case 13:

            cout << "\nLos elementos del arbol acostado con la raiz a la izquierda son:\n\n";
            arbolEnteros.muestraAcostado(0, raizArbolPtr);
            cout << "\n\n";

            if(arbolEnteros.esLLeno(raizArbolPtr))
                cout << "\nSi es un arbol binario lleno.";
            else
                cout << "\nNo es un arbol binario lleno.";

            cout << "\n\n";
            system("pause");
            break;

        case 14:

            arbolEnteros.podarArbol(raizArbolPtr);
            cout << "\nEl arbol ha sido podado.";
            cout <<"\n\n";

            cout << "\n\n";
            system("pause");
            break;
        }

    } while (opcion != 15);

    return 0;
    
}

