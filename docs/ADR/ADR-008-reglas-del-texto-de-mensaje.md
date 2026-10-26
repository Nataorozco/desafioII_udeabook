---
tipo: adr
id: ADR-008
status: Aceptado
fecha: 2026-10-20
dominio: Modelo de dominio
reemplaza:
superado_por:
---

# ADR-008 — Reglas del texto de Mensaje

## Contexto
El archivo de datos guarda un registro por línea con los campos separados por tabulador. Un mensaje con `\t`, `\n` o `\r` en el texto rompería el formato.

## Decisión
`Mensaje` acepta cualquier carácter mientras el texto no esté vacío ni sea solo blancos y no pase de 512 caracteres (`LONGITUD_MIN` y `LONGITUD_MAX`). Antes de validar, el constructor reemplaza `\t`, `\n` y `\r` por un espacio. `textoEsValido` es estático y solo responde `true` o `false`. Si el texto no es válido, el mensaje queda en estado seguro (texto vacío, fecha por defecto, punteros nulos, `leido = false`).

## Alternativas consideradas
- Rechazar mensajes con esos caracteres: se pierde contenido legítimo.
- Validar antes de limpiar: un texto como "\t\t" pasaría y quedaría como solo espacios.

## Consecuencias
- El texto guardado nunca contiene separadores del archivo.
- Al cargar el archivo conviene quitar el `\r` final de cada línea leída.
- Dos constructores sobrecargados: el completo (con `leido`) para cargar y el corto (delegado) para mensajes nuevos.

## Relacionado
ADR-004, ADR-006.
