#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <cstddef>
#include "nodo.h"

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int cantidad;
public:
    ListaEnlazada() : cabeza(nullptr), cola(nullptr), cantidad(0) {}

    // constructor de copia, crea nodos, no comparte los del original
    //aqui se crea una lista nueva creando elementos de otra

    ListaEnlazada(const ListaEnlazada& otra): cabeza(nullptr), cola(nullptr), cantidad(0) {
        for (Nodo<T>* a = otra.cabeza; a != nullptr; a = a->siguiente) //mueve al siguiente nodo
            insertarFinal(a->dato); //insertar final crea un nodo nuevo para guardar una copia de este dato
    }
    // Asignacion: Liberar lo propio y copia en profundidad
    ListaEnlazada& operator=(const ListaEnlazada& otra) {
        if (this != &otra) {
            vaciar();
            for (Nodo<T>* a = otra.cabeza; a != nullptr; a = a->siguiente)
                insertarFinal(a->dato);
        }
        return *this;
    }

    // DEstructor devuelve  al sistema la memoria de todos los nodos
    ~ListaEnlazada() { vaciar(); }

    //consulta el tamaño y comprueba si esta vacia
    int tamano() const {return cantidad; }
    bool estaVacia() const {return cantidad ==0;}

    // Inserción simple (al final gracias a cola)
    void insertarFinal(const T& d) {
        Nodo<T>* n = new Nodo<T>(d);
        if (cola == nullptr) { cabeza = n; cola = n;}
        else { cola->siguiente = n; cola = n;}
        cantidad++;
    }

    // insercion ordenada algoritmo (3) deja la lista de menor a mayor segun el operador <
    //si hay iguales, el nuevo queda despues de ellos.
    void insertarOrdenado(const T& d, unsigned long* it = nullptr) {
        Nodo<T>* n = new Nodo<T>(d); // este primer nodo se covierte en el primero y el ultimo
        if (cabeza == nullptr) {
            cabeza = n; cola = n;
        }else if (d < cabeza->dato){
            n->siguiente = cabeza;
            cabeza = n;
        }else {
            Nodo<T>* a = cabeza; //puntero auxiliar a que permite recorrer la lista sin perder
            //la referencia de lacabeza
            while (a->siguiente != nullptr && !(d < a->siguiente->dato)){
                a = a->siguiente;
                if (it) (*it)++;
            }
            n->siguiente = a->siguiente;
            a->siguiente = n;
            if (n->siguiente == nullptr) cola = n;
        }
        cantidad++;
    }

    // Acceso por posicion (0= primero). DEvuelve la direccion del elemento
    // asi se puede modificar por ejemplo marcar un mensaje como leido o nullptr
    T* obtenerEn(int i, unsigned long* it = nullptr) {
        if (i < 0 || i >= cantidad) return nullptr;
        Nodo<T>* a = cabeza;
        for (int k = 0; k < i; k++) {
            a = a->siguiente;
            if(it) (*it)++;
        }
        return &a->dato;
    }

    //Eliminacion por posicion devuelve false si la posicion no existe
    bool eliminarEn(int i, unsigned long* it = nullptr) {
        if (i < 0 || i >= cantidad) return false;
        Nodo<T>* borrar;
        if (i == 0) {
            borrar = cabeza;
            cabeza = cabeza->siguiente;
            if (cabeza == nullptr) cola = nullptr;
        }else {
            Nodo<T>* previo = cabeza;
            for (int k = 0; k < i -1; k++) {
                previo = previo->siguiente;
                if (it) (*it)++;
            }
            borrar = previo->siguiente;
            previo->siguiente = borrar->siguiente;
            if (borrar == cola) cola = previo;
        }
        delete borrar;
        cantidad ++;
        return true;
    }

    void vaciar() {
        while (cabeza != nullptr) {
            Nodo<T>* t = cabeza;
            cabeza = cabeza->siguiente;
            delete t;
        }
        cola = nullptr;
        cantidad = 0;
    }

    //memoria de la lista, el objeto lista+ por cada nodo
    size_t memoriaUsada() const {
        size_t total = sizeof(ListaEnlazada<T>);
        for (Nodo<T>* a = cabeza; a != nullptr; a = a->siguiente)
            total += (sizeof(Nodo<T>) - sizeof(T)) + a->dato.memoriaUsada();
        return total;
    }
};

#endif
