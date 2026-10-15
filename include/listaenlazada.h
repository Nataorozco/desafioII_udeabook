#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <cstddef>
#include "nodo.h"

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int cantidad;
public:
    ListaEnlazada() : cabeza(nullptr), cantidad(0) {}
    ~ListaEnlazada() { vaciar(); }
    ListaEnlazada(const ListaEnlazada&) = delete;
    ListaEnlazada& operator=(const ListaEnlazada&) = delete;

    int tamano() const { return cantidad; }

    // Inserción simple (al final)
    void insertarFinal(const T& d) {
        Nodo<T>* n = new Nodo<T>(d);
        if (!cabeza) cabeza = n;
        else { Nodo<T>* a = cabeza; while (a->siguiente) a = a->siguiente; a->siguiente = n; }
        cantidad++;
    }

    // Acceso por índice (para la navegación circular de fotos)
    T* obtenerEn(int i) {
        if (i < 0 || i >= cantidad) return nullptr;
        Nodo<T>* a = cabeza;
        for (int k = 0; k < i; k++) a = a->siguiente;
        return &a->dato;
    }

    // TODO: insertarOrdenado (1.3), eliminar (1.8), memoriaUsada (1.6)

    void vaciar() {
        while (cabeza) { Nodo<T>* t = cabeza; cabeza = cabeza->siguiente; delete t; }
        cantidad = 0;
    }
};

#endif
