//
// Created by Italo Mendez on 15/11/2026.
//
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct Nodo {
    int dato;
    bool rojo;
    Nodo *izq = nullptr, *der = nullptr, *padre = nullptr;
    Nodo(int valor, bool color = true)
        : dato(valor), rojo(color) {}
};
int altura(Nodo* nodo) {
    if (!nodo) return -1;
    return 1 + max(altura(nodo->izq), altura(nodo->der));
}
void preOrden(Nodo* nodo, bool colores) {
    if (!nodo) {
        cout << "NIL ";
        return;
    }
    cout << nodo->dato;
    if (colores)
        cout << (nodo->rojo ? "(R)" : "(N)");
    cout << " ";
    preOrden(nodo->izq, colores);
    preOrden(nodo->der, colores);
}
void liberar(Nodo* nodo) {
    if (!nodo) return;
    liberar(nodo->izq);
    liberar(nodo->der);
    delete nodo;
}
class RedBlack {
    Nodo* raiz = nullptr;
    void rotarIzquierda(Nodo* x) {
        Nodo* y = x->der;
        x->der = y->izq;
        if (y->izq)
            y->izq->padre = x;
        y->padre = x->padre;
        if (!x->padre)
            raiz = y;
        else if (x == x->padre->izq)
            x->padre->izq = y;
        else
            x->padre->der = y;
        y->izq = x;
        x->padre = y;
    }
    void rotarDerecha(Nodo* x) {
        Nodo* y = x->izq;
        x->izq = y->der;
        if (y->der)
            y->der->padre = x;
        y->padre = x->padre;
        if (!x->padre)
            raiz = y;
        else if (x == x->padre->izq)
            x->padre->izq = y;
        else
            x->padre->der = y;
        y->der = x;
        x->padre = y;
    }
    void corregir(Nodo* z) {
        while (z->padre && z->padre->rojo) {
            Nodo* p = z->padre;
            Nodo* g = p->padre;
            if (p == g->izq) {
                Nodo* tio = g->der;
                if (tio && tio->rojo) {
                    p->rojo = tio->rojo = false;
                    g->rojo = true;
                    z = g;
                } else {
                    if (z == p->der) {
                        z = p;
                        rotarIzquierda(z);
                    }
                    z->padre->rojo = false;
                    z->padre->padre->rojo = true;
                    rotarDerecha(z->padre->padre);
                }
            } else {
                Nodo* tio = g->izq;
                if (tio && tio->rojo) {
                    p->rojo = tio->rojo = false;
                    g->rojo = true;
                    z = g;
                } else {
                    if (z == p->izq) {
                        z = p;
                        rotarDerecha(z);
                    }
                    z->padre->rojo = false;
                    z->padre->padre->rojo = true;
                    rotarIzquierda(z->padre->padre);
                }
            }
        }
        raiz->rojo = false;
    }
    // Retorna la altura negra; -1 significa que hay un error.
    int verificar(Nodo* n, Nodo* padre,
                  long long menor, long long mayor) const {
        // Las hojas nulas son negras.
        if (!n) return 1;
        // Verifica enlaces y orden del BST.
        if (n->padre != padre ||
            n->dato <= menor || n->dato >= mayor)
            return -1;
        // Un nodo rojo no puede tener hijos rojos.
        if (n->rojo &&
            ((n->izq && n->izq->rojo) ||
             (n->der && n->der->rojo)))
            return -1;
        int izquierda = verificar(n->izq, n, menor, n->dato);
        int derecha = verificar(n->der, n, n->dato, mayor);
        // Todos los caminos deben tener igual altura negra.
        if (izquierda == -1 || derecha == -1 ||
            izquierda != derecha)
            return -1;
        return izquierda + (n->rojo ? 0 : 1);
    }
public:
    void insertar(int valor) {
        Nodo* padre = nullptr;
        Nodo* actual = raiz;
        while (actual) {
            padre = actual;
            if (valor == actual->dato) return;
            actual = valor < actual->dato
                ? actual->izq : actual->der;
        }
        Nodo* nuevo = new Nodo(valor);
        nuevo->padre = padre;
        if (!padre)
            raiz = nuevo;
        else if (valor < padre->dato)
            padre->izq = nuevo;
        else
            padre->der = nuevo;
        corregir(nuevo);
    }
    bool esValido() const {
        if (raiz && raiz->rojo) return false;
        return verificar(
            raiz, nullptr, LLONG_MIN, LLONG_MAX
        ) != -1;
    }
    int getAltura() const {
        return altura(raiz);
    }
    void mostrar() const {
        preOrden(raiz, true);
        cout << endl;
    }
    ~RedBlack() {
        liberar(raiz);
    }
};
void insertarBST(Nodo*& raiz, int valor) {
    Nodo** actual = &raiz;
    while (*actual) {
        if (valor == (*actual)->dato) return;
        actual = valor < (*actual)->dato
            ? &(*actual)->izq : &(*actual)->der;
    }
    *actual = new Nodo(valor, false);
}

int main() {
    Nodo* bst = nullptr;
    RedBlack rb;

    bool siempreValido = true;

    for (int i = 1; i <= 20; i++) {
        insertarBST(bst, i);
        rb.insertar(i);

        siempreValido = siempreValido && rb.esValido();
    }

    cout << "Altura BST: " << altura(bst) << endl;
    cout << "Altura Red-Black: " << rb.getAltura() << endl;

    cout << "Valido despues de cada insercion: "
         << boolalpha << siempreValido << endl;

    cout << "Pre-orden BST (NIL = hijo nulo):\n";
    preOrden(bst, false);

    cout << "\nPre-orden Red-Black (R = rojo, N = negro):\n";
    rb.mostrar();

    liberar(bst);
}