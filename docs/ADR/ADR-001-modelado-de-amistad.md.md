---
tipo: adr
id: ADR-001
status: Aceptado
fecha: 2026-10-06
dominio: "Modelo de dominio"
reemplaza:
superado_por:
---

# ADR-001 — Modelado de la relación de amistad

## Contexto
El enunciado describe la amistad como una relación mutua entre dos
usuarios, sin atributos adicionales (fecha, origen, etc.). El enunciado
además prohíbe el uso de herencia en el diseño.

## Decisión
Cada `Usuario` mantiene una lista enlazada de punteros a otros `Usuario`
(sus amigos), sin una clase `Amistad` separada. Al aceptar una
solicitud, se agrega el puntero correspondiente en ambas listas
(simetría manual).

`SolicitudAmistad` sí se modela como clase aparte, porque tiene estado
propio (pendiente/aceptada/rechazada) y referencia a quién la envió.

## Alternativas consideradas
- Clase `Amistad` con referencia a ambos usuarios: descartada por no
  aportar atributos que el enunciado no pida — complejidad innecesaria.

## Consecuencias
- Operación de "hacerse amigos" requiere actualizar dos listas (una por
  cada usuario), debe hacerse en una sola función para no romper la
  simetría si algo falla a medio camino.