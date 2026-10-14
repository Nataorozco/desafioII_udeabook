---
tipo: ADR
id: ADR-004
status: aceptada
fecha: 2026-10-07
dominio: "Ude@Book — tipos de datos"
reemplaza: null
superado_por: null
---

# ADR-004: Tipo de dato para atributos de texto (`char*` vs. `std::string`)

## Contexto

El enunciado del Desafío II prohíbe explícitamente el uso de STL y de `struct`, y exige que las estructuras de datos dinámicas, como las listas enlazadas, se implementen desde cero.

Sin embargo, no menciona explícitamente si `std::string` está permitido para los atributos de texto (nombre de usuario, correo, rutas de archivo, texto de mensajes, entre otros). Esto contrasta con el Desafío I, cuyo enunciado sí prohibía explícitamente cualquier sintaxis ajena a ANSI C.

Ante esta ambigüedad, se analizó la diferencia entre la STL (Standard Template Library) y otras partes de la biblioteca estándar de C++. La STL se asocia tradicionalmente con contenedores, iteradores, algoritmos y objetos función. `std::string`, definido en `<string>` como `std::basic_string<char>`, pertenece a la biblioteca estándar de C++, pero no es uno de los contenedores clásicos de la STL.

Esta interpretación se consultó con el profesor, quien aceptó el uso de `std::string`.

## Decisión

Se utilizará `std::string` para los atributos de texto de las clases del dominio:

- **Usuario:** `nombreUsuario`, `correo`, `rutaFotoPerfil`, `ciudad` y `pais`.
- **Mensaje:** `texto`.
- **Album:** `nombre` y `ruta`.
- **Foto:** `ruta`.
- **RedSocial:** parámetros de texto de los métodos `cargarDatos`, `guardarDatos` y `buscarUsuario`, como las rutas de archivo y los nombres de usuario.

Se mantienen los tipos que no representan texto:

- `unsigned char*` para la matriz de adyacencia.
- `char` para los códigos de un carácter, como `privacidad` en `Album` y `estado` en `SolicitudAmistad`.

## Alternativas consideradas

### 1. `char*` dinámico con manejo manual

Esta fue la opción inicial por precaución ante la ambigüedad del enunciado.

Se descarta como decisión final porque, una vez confirmado con el profesor que `std::string` está permitido, mantener `char*` añadiría complejidad sin que el enunciado lo exija expresamente.

El manejo manual requeriría gestionar la memoria con `new` y `delete`, copiar cadenas correctamente y controlar los riesgos de fugas de memoria y dobles liberaciones.

### 2. `std::string` — alternativa elegida

Simplifica el manejo de texto y reduce la necesidad de administrar manualmente la memoria de cada cadena.

Además, proporciona operaciones de comparación y asignación, y permite que el constructor de copia, el operador de asignación y el destructor generados por el compilador gestionen correctamente el atributo de texto.

Esto se cumple siempre que la clase no tenga otros recursos que requieran una gestión manual especial.

### 3. Implementar una clase de cadena propia (`MiString`)

Se descarta porque supondría trabajo adicional que no aporta una ventaja clara para los objetivos del desafío.

El requisito de implementar estructuras de datos dinámicas desde cero ya se aborda mediante `ListaEnlazada<T>` y `Nodo<T>`, que permiten demostrar el manejo de memoria dinámica y la implementación de estructuras propias.

Crear otra clase para gestionar cadenas competiría con el tiempo disponible para desarrollar y probar las funcionalidades obligatorias.

## Consecuencias

- Los constructores de `Usuario`, `Mensaje`, `Album` y `Foto` podrán asignar directamente sus atributos de texto sin utilizar `new`,  ni gestionar individualmente la memoria de cada cadena.
- Las clases que solo contienen `std::string` y tipos simples pueden aprovechar las operaciones especiales generadas por el compilador, siempre que no existan otros recursos que requieran gestión personalizada.
- `Usuario` todavía necesitará una estrategia de copia correcta para sus listas enlazadas internas. El uso de `std::string` no resuelve automáticamente los problemas de copia profunda de estructuras dinámicas propias.
- La gestión manual de memoria dinámica se concentrará principalmente en `Nodo<T>`, `ListaEnlazada<T>` y otras estructuras que realmente lo requieran. Por tanto, el uso de `std::string` no elimina la necesidad de demostrar manejo de memoria dinámica en el proyecto.
- La medición de memoria debe distinguir entre el tamaño del objeto `std::string` y la memoria dinámica utilizada por su contenido. `sizeof(std::string)` no incluye necesariamente la memoria reservada para almacenar caracteres.
- Para estimar la memoria asociada a una cadena, se puede considerar `sizeof(std::string)` más la capacidad dinámica que corresponda, evitando contabilizar dos veces el almacenamiento interno. La capacidad puede incluir espacio reservado que todavía no contiene caracteres utilizados.
- Las fórmulas definitivas de medición deberán ajustarse a la implementación utilizada y documentarse en la sección de eficiencia y consumo de recursos del informe.

## Estado

Decisión aceptada tras consultar con el profesor la interpretación de la restricción sobre STL.
