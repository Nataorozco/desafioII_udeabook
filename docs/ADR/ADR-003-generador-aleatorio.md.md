---
tipo: adr
id: ADR-003
status: Aceptado
fecha: 2026-10-06
dominio: "Aleatoriedad"
reemplaza:
superado_por:
---

# ADR-003 — Uso de rand() en vez de generador propio

## Contexto
En el Desafío I se implementó un LCG propio porque rand() estaba en
zona ambigua frente a la prohibición de ANSI C, y el eje de ese
desafío era manipulación de bits. Este enunciado permite explícitamente
"usar la librería para generar aleatorios".

## Decisión
Usar `rand()`/`srand()` de la librería estándar para la selección
aleatoria ponderada de fotos de perfil y cualquier otra necesidad de
aleatoriedad del proyecto.

## Alternativas consideradas
- Generador propio (LCG): descartado — el eje de evaluación de este
  desafío es POO y eficiencia, no manipulación de bits; implementar un
  generador propio no aporta a ningún criterio de calificación aquí y
  añade complejidad a la sustentación sin beneficio.

## Consecuencias
- Simplifica la explicación del código y reduce superficie de error.
- La semilla debe fijarse con cuidado si se necesita reproducibilidad
  para pruebas (a definir si hace falta para el video de demostración).