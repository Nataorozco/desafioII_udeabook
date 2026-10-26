---
tipo: adr
id: ADR-005
status: Aceptado
fecha: 2026-10-13
dominio: Estructuras de datos
reemplaza: ADR-002
superado_por:
---

# ADR-005 — Lista simplemente enlazada con cola

## Contexto
El ADR-002 propuesta de  una lista doblemente enlazada para poder avanzar y retroceder en el carrusel de fotos. Al implementarla, el carrusel se resuelve con un índice y el operador módulo, como indica el informe, y el recorrido con el iterador solo necesita avanzar. Además, el diagrama de la primera entrega ya mostraba `Nodo<T>` solo con el puntero `siguiente`. 


## Decisión
`ListaEnlazada<T>` es simplemente enlazada y guarda `cabeza`, `cola` y `cantidad`. 
En esta ultima parte hago mencion de la propuesta mejorada agregando esta parte que no fue planteada en el primer informe, estos son 3 atributos fundamentales cabeza-cola-cantidad, teniendo en cuenta que cabeza apunta al primer nodo, cola apunta al ultimo nodo sin tener que recorrer toda la lista para poder insertar eficientemente. Cantidad guarda cuantos elementos existen por ejemplo si almacena tres mensajes cantidad vale 3.
## Alternativas consideradas
- Doblemente enlazada: cada nodo gasta un puntero más y cada inserción o eliminación actualiza dos enlaces; el carrusel no la necesita.
- Simplemente enlazada sin cola: `insertarFinal` tendría que recorrer toda la lista (O(n)).

## Consecuencias
- `insertarFinal` es O(1) gracias a la cola.
- Eliminar o retroceder puede costar O(n) en el peor caso.
- Hay que mantener `cola` actualizada al insertar y al eliminar; las pruebas de `test_lista` lo verifican.
- Reemplaza parcialmente al ADR-002 (solo en lo relativo a doble enlace); el resto del ADR-002 sigue vigente.

## Relacionado
ADR-002, ADR-007.
