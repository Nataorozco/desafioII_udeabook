---
tipo: adr
id: ADR-007
status: Aceptado
fecha: 2026-10-20
dominio: Estructuras de datos
reemplaza:
superado_por:
---

# ADR-007 — Iterador de la lista

## Contexto
Recorrer la lista con `obtenerEn(i)` dentro de un `for` obliga a empezar desde la cabeza en cada vuelta. 
Class Iterador dentro de la lista: Es una clase pequeña que vive dentro de listaEnlazada<T>. su unico trabajo es recordar en que nodo va el recorrido. actualNodo (privado): el unico dato. Es un puntero al nodo donde esta parado el cursor. Es privado, asi que quien usa el iterador nunca ve los nodos, solo los datos. ConstructorIterador(Nodo<T>* n): deja el cursor parado en el nodo que le pasen haySiguiente(): devuelve true mientras el cursor este sobre el nodo real. Cuando se pasa del ultimo, vale nullptr y devuelve false: es la condicion de parada del ciclo. actual(): devuelve el dato del nodo donde esta el cursor. Devuelve T&(una referencia) para poder modificar el elemento en un sitio, por ejemplo marcar un mensaje como leido. avanzar(): pasa el cursor al siguiente nodo. inicio(): crea un iterador parado en cabeza. Es const porque no modifica la lista. 

## Decisión
Clase `Iterador` anidada en `ListaEnlazada<T>`, con `haySiguiente()`, `actual()` y `avanzar()`, y `inicio()` en la lista. Guarda solo el nodo actual (privado), así quien la usa nunca ve los nodos.

## Alternativas consideradas
- Recorrer con `obtenerEn(i)`: más simple, pero cuadrático.

## Consecuencias
- Con 1000 elementos son 1000 pasos con iterador frente a 499.500 con `obtenerEn`.
- Los recorridos completos (usuarios, mensajes, álbumes) pasan de O(n²) a O(n).
- Sostiene el criterio de eficiencia del enunciado.

## Relacionado
ADR-005.
