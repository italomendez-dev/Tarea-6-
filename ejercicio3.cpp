//
// Created by Italo Mendez on 15/11/2026.
//
#include <iostream>
#include <stack>
using namespace std;

struct Nodo {
    int dato;
    Nodo *izq, *der;

    Nodo(int valor, Nodo* i = nullptr, Nodo* d = nullptr)
        : dato(valor), izq(i), der(d) {}
};

struct Estado {
    Nodo* nodo;
    long long suma;
    bool salida;
};

bool buscarCamino(Nodo* raiz, long long k, stack<int>& camino) {
    while (!camino.empty())
        camino.pop();

    if (!raiz) return false;

    stack<Estado> pendientes;
    pendientes.push({raiz, 0, false});

    while (!pendientes.empty()) {
        Estado e = pendientes.top();
        pendientes.pop();

        if (e.salida) {
            camino.pop();
            continue;
        }

        Nodo* n = e.nodo;
        long long suma = e.suma + n->dato;

        camino.push(n->dato);

        if (!n->izq && !n->der && suma == k)
            return true;

        // Al terminar sus hijos, retiramos el nodo del camino.
        pendientes.push({n, suma, true});

        // El izquierdo se procesa primero por el orden LIFO.
        if (n->der)
            pendientes.push({n->der, suma, false});

        if (n->izq)
            pendientes.push({n->izq, suma, false});
    }

    return false;
}

void mostrar(stack<int> camino) {
    stack<int> orden;

    while (!camino.empty()) {
        orden.push(camino.top());
        camino.pop();
    }

    while (!orden.empty()) {
        cout << orden.top();
        orden.pop();

        if (!orden.empty())
            cout << " -> ";
    }

    cout << endl;
}

void liberar(Nodo* raiz) {
    stack<Nodo*> pila;

    if (raiz) pila.push(raiz);

    while (!pila.empty()) {
        Nodo* n = pila.top();
        pila.pop();

        if (n->izq) pila.push(n->izq);
        if (n->der) pila.push(n->der);

        delete n;
    }
}

int main() {
    Nodo* raiz = new Nodo(5,
        new Nodo(4,
            new Nodo(11, new Nodo(7), new Nodo(2))),
        new Nodo(8,
            new Nodo(13),
            new Nodo(4, nullptr, new Nodo(1)))
    );

    for (int k : {22, 100}) {
        stack<int> camino;

        cout << "K = " << k << ": ";

        if (buscarCamino(raiz, k, camino))
            mostrar(camino);
        else
            cout << "No existe camino raiz-hoja.\n";
    }

    liberar(raiz);
}