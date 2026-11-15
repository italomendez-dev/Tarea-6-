#include <iostream>
#include <stack>
#include <utility>
#include <algorithm>
using namespace std;

struct Nodo {
    int dato;
    Nodo *izq = nullptr, *der = nullptr;
    Nodo(int valor) : dato(valor) {}
};
class BST {
    Nodo* raiz = nullptr;
public:
    void insertar(int valor) {
        Nodo** actual = &raiz;
        while (*actual != nullptr) {
            if (valor == (*actual)->dato) return;

            actual = valor < (*actual)->dato
                ? &(*actual)->izq : &(*actual)->der;
        }
        *actual = new Nodo(valor);
    }
    void eliminar(int valor) {
        Nodo** enlace = &raiz;
        while (*enlace && (*enlace)->dato != valor) {
            enlace = valor < (*enlace)->dato
                ? &(*enlace)->izq : &(*enlace)->der;
        }
        if (!*enlace) return;
        Nodo* borrar = *enlace;
        if (borrar->izq && borrar->der) {
            Nodo** sucesor = &borrar->der;
            while ((*sucesor)->izq)
                sucesor = &(*sucesor)->izq;
            borrar->dato = (*sucesor)->dato;
            borrar = *sucesor;
            *sucesor = borrar->der;
        } else {
            *enlace = borrar->izq ? borrar->izq : borrar->der;
        }
        delete borrar;
    }
    void inOrder() const {
        stack<Nodo*> pila;
        Nodo* actual = raiz;
        while (actual || !pila.empty()) {
            while (actual) {
                pila.push(actual);
                actual = actual->izq;
            }
            actual = pila.top();
            pila.pop();
            cout << actual->dato << " ";
            actual = actual->der;
        }
        cout << endl;
    }
    int altura() const {
        if (!raiz) return -1;
        stack<pair<Nodo*, int>> pila;
        pila.push({raiz, 0});
        int mayor = 0;
        while (!pila.empty()) {
            auto [nodo, nivel] = pila.top();
            pila.pop();
            mayor = max(mayor, nivel);
            if (nodo->izq)
                pila.push({nodo->izq, nivel + 1});
            if (nodo->der)
                pila.push({nodo->der, nivel + 1});
        }
        return mayor;
    }
    ~BST() {
        stack<Nodo*> pila;
        if (raiz) pila.push(raiz);
        while (!pila.empty()) {
            Nodo* nodo = pila.top();
            pila.pop();
            if (nodo->izq) pila.push(nodo->izq);
            if (nodo->der) pila.push(nodo->der);
            delete nodo;
        }
    }
};

int main() {
    BST arbol;
    for (int i = 1; i <= 20; i++)
        arbol.insertar(i);

    cout << "Altura inicial: " << arbol.altura() << endl;

    arbol.eliminar(5);
    arbol.eliminar(15);

    cout << "In-order despues de eliminar 5 y 15: ";
    arbol.inOrder();

    cout << "Altura final: " << arbol.altura() << endl;
}