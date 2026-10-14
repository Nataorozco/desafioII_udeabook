---
tipo: adr
id: ADR-002
status: Aceptado
fecha: 2026-10-06
dominio: "Estructuras de datos"
reemplaza:
superado_por:
---

# ADR-002 — Lista enlazada genérica con template

## Contexto
El enunciado prohíbe STL y structs, exige memoria dinámica propia y el
uso de templates. Se necesita una estructura reutilizable para amigos,
mensajes, álbumes, fotos y usuarios.

## Decisión
Lista doblemente enlazada genérica (`template <typename T>`), no
circular por defecto, guardando punteros (`T*`) en cada nodo en vez de
copias por valor. El carrusel de fotos conecta manualmente el primer y
último nodo solo en ese contexto específico, sin alterar la clase base.

## Alternativas consideradas
- Lista simplemente enlazada: descartada porque el carrusel necesita
  moverse en ambas direcciones.
- Guardar objetos por valor: descartada por el requisito explícito del
  enunciado de evitar copias innecesarias sobre datos estructurados.
- Lista circular por defecto: descartada porque solo el carrusel de
  fotos necesita esa propiedad; forzarla en todas las listas complica
  el resto de los recorridos sin necesidad.

## Consecuencias
- Requiere destructor que libere cada nodo (evitar fugas de memoria) y
  constructor de copia con copia profunda (exigido por el enunciado).
- Buena candidata para sobrecargar operadores (`[]`, `<<`), cumpliendo
  ese requisito del diagrama de clases.