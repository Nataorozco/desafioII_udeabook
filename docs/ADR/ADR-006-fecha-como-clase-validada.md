---
tipo: adr
id: ADR-006
status: Aceptado
fecha: 2026-10-17
dominio: Modelo de dominio
reemplaza:
superado_por:
---

# ADR-006 — Fecha como clase validada

## Contexto
Una fecha guardada como texto acepta cualquier valor, incluso imposible por eso la razon de usarla como clase y no como string.
La responsabilidad de esta clase es modelar y estructurar fechas (dia, mes, año). Permite realizar operaciones de comparacion, usa sobrecarga de operador  <, que permite comparar directamente dos objetos como fecha1 < fecha2 ejemplo la fecha de nacimiento de un usuario con la de otro o cualquier par de fechas del sistema.

## Decisión
Clase `Fecha` con `dia`, `mes` y `anio` enteros privados. Las constantes `ANIO_MIN = 1900` y `ANIO_MAX = 2100` y los métodos estáticos `esValida`, `esBisiesto` y `diasDelMes` validan. El constructor y `setFecha` rechazan fechas inválidas: el constructor deja 1/1/1900 y `setFecha` devuelve `bool` y cambia los tres campos o ninguno. Se compara con `operator<` (año, luego mes, luego día).

## Alternativas consideradas
- Guardar la fecha como texto "dd/mm/aaaa": acepta cualquier valor y comparar exige interpretarlo.
- Valor por defecto con un año más reciente: se mantuvo 1/1/1900 por simplicidad al explicarlo.

## Consecuencias
- Toda `Fecha` del sistema es válida y comparar fechas es comparar números.
- La prueba detectó un error en `operator<` al comparar meses, ya corregido.

## Relacionado
ADR-005, ADR-008.
