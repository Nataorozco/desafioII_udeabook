#ifndef NODO_H
#define NODO_H

template <typename T>
// nodo guarda un elemento y la direccion del siguiente nodo
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo(const T& d) : dato(d), siguiente(nullptr) {}
};

#endif
