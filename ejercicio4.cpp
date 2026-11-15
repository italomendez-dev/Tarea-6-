//
// Created by Italo Mendez on 15/11/2026.
//
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Nodo {
    int dato;
    Nodo *izq, *der;

    Nodo(int valor, Nodo* i = nullptr, Nodo* d = nullptr)
        : dato(valor), izq(i), der(d) {}
};

bool esCompleto(Nodo* raiz) {
    if (!raiz) return true;

    queue<Nodo*> cola;
    cola.push(raiz);

    bool hueco = false;

    while (!cola.empty()) {
        Nodo* n = cola.front();
        cola.pop();

        if (!n) {
            hueco = true;
        } else {
            if (hueco) return false;

            cola.push(n->izq);
            cola.push(n->der);
        }
    }

    return true;
}

int anchoMaximo(Nodo* raiz) {
    if (!raiz) return 0;

    queue<Nodo*> cola;
    cola.push(raiz);

    int mayor = 0;

    while (!cola.empty()) {
        int cantidad = static_cast<int>(cola.size());
        mayor = max(mayor, cantidad);

        for (int i = 0; i < cantidad; i++) {
            Nodo* n = cola.front();
            cola.pop();

            if (n->izq) cola.push(n->izq);
            if (n->der) cola.push(n->der);
        }
    }

    return mayor;
}

int profundidadMinima(Nodo* raiz) {
    if (!raiz) return -1;

    queue<Nodo*> cola;
    cola.push(raiz);

    int nivel = 0;

    while (!cola.empty()) {
        int cantidad = static_cast<int>(cola.size());

        for (int i = 0; i < cantidad; i++) {
            Nodo* n = cola.front();
            cola.pop();

            if (!n->izq && !n->der)
                return nivel;

            if (n->izq) cola.push(n->izq);
            if (n->der) cola.push(n->der);
        }

        nivel++;
    }

    return -1;
}

void evaluar(Nodo* raiz) {
    cout << "Completo: "
         << boolalpha << esCompleto(raiz) << endl;

    cout << "Ancho maximo: "
         << anchoMaximo(raiz) << endl;

    cout << "Profundidad minima: "
         << profundidadMinima(raiz) << endl;
}

void liberar(Nodo* raiz) {
    queue<Nodo*> cola;

    if (raiz) cola.push(raiz);

    while (!cola.empty()) {
        Nodo* n = cola.front();
        cola.pop();

        if (n->izq) cola.push(n->izq);
        if (n->der) cola.push(n->der);

        delete n;
    }
}

int main() {
    Nodo* a = new Nodo(1,
        new Nodo(2, new Nodo(4), new Nodo(5)),
        new Nodo(3)
    );

    Nodo* b = new Nodo(1,
        new Nodo(2, nullptr, new Nodo(4)),
        new Nodo(3)
    );

    cout << "Arbol A:\n";
    evaluar(a);

    cout << "\nArbol B:\n";
    evaluar(b);

    cout << "\nArbol vacio:\n";
    evaluar(nullptr);

    liberar(a);
    liberar(b);
}