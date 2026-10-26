# Ude@Book — Documentación de implementación (borrador base)

En esta entrega final aclaro que continuo con las desiciones tomadas y documentadas en la primera entrega, pero teniendo en cuenta como se realizan las implementaciones finales.

## 1. Alcance y estado a la fecha (25/10/2026)

Importante aclarar que hasta este momento llegue al desarrollo de las clases que se referencian en el siguiente cuadro.

| Pieza                                                               | Estado                                             | Evidencia                             |
| ------------------------------------------------------------------- | -------------------------------------------------- | ------------------------------------- |
| `Fecha`                                                             | Implementada y probada                             | `test_fecha` imprime "Fecha OK"       |
| `Nodo<T>`                                                           | Implementacion hasta el momento.                   | [prueba test_Nodo pendiente]          |
| `ListaEnlazada<T>` (con cola, copia profunda, iterador, contadores) | Implementacion hasta el momento.                   | [prueba test_listaEnlazada pendiente] |
| `Mensaje`                                                           | Implementada (constructores, validación, getters). | [prueba test_mensaje pendiente]       |
| `Usuario`, `RedSocial`, carga de archivos, funcionalidades I–VII    | No implementadas todavía                           | —                                     |

Aun no tengo la funcionalidad del menu ejecutandose con los 1000 usuarios,

## 2. Qué funciona hoy

### 2.1 Fecha
Class fecha:

La responsabilidad de esta clase es modelar y estructurar fechas (dia, mes, año). Permite realizar operaciones de comparacion, usa sobrecarga de operador  <, que permite comparar directamente dos objetos como fecha1 < fecha2 ejemplo la fecha de nacimiento de un usuario con la de otro o cualquier par de fechas del sistema.

Atributos privados:

-int dia
-int mes
-int anio

Atributos publicos (constantes):

+int ANIO_MIN (constante) = 1900
+int ANIO_MAX(constante) = 2100

Atributos publicos:

+Fecha()
+Fecha(int d, int m, int a)

Metodos estaticos(no dependen de un objeto):

+esValida(int d, int m, int a) bool
+esBisiesto(int a) bool$
+diasDelMes(int m, int a) int

+getDia() int
+getMes() int
+getAnio() int

Constructor por defecto(1/1/1900) y constructor fecha(d,m,a) si la fecha no es valida queda en el valor por defecto.

setFecha(d,m,a) devuelve bool y cambia los tres campos o ninguno.

+setFecha(int d, int m, int a) bool
+operator<(Fecha otra) bool
+aTexto() string
+memoriaUsada() size_t

Aplico encapsulacion poniendo dia mes año en una misma clase, como privados y dejo que solo se cambien atraves de metodos que se validan antes de modificar, por ejemplo en esta clase hay dos grupos que son los que validan y los que usan la validacion para proteger los datos.

Los que validan la regla son los 3 metodos estaticos:
esValido(d, m, a) es el principal: El año esta entre ANIO_MIN y ANIO_MAX, el mes entre 1 y 12
y el dia entre 1 y los dias que tiene ese mes.
diasDelMes(m,a) cuantos dias tiene el mes (28-29-30-31) lo usa esValida.
esBisiesto(a) si el año es bisiesto, para saber si febrero tiene 29 dias, lo usa diasDelMes.

Para dejar claro los getters y setters:
Aqui los getters son lo que no se puede tocar desde fuera como dia, mes y año son const prometen no cambiar el objeto: 
Los getters devuelven el valor de un atributo privado sin permitir modificarlo, y son const. Para modificarlo uso setFecha, un unico setter para los 3 valores.
para tener en cuenta no es que sean 3 setters ejem: seDia, setMes, setAnio hay uno solo es setFecha(d, m, a). ESta es la razon porque la valiz depende de los 3 valores juntos. Si existiera setDia(31), el 31 solo es valido en algunos meses, y la clase no podria saber si esta bien sin conocer el mes y el año. Un setDia suelto podria dejar 31/2/2026. Con un setter se valida la fecha completa: 
Si es valida, cambia los 3 campos y devuelve true, si no es valida, no cambia nada y devuelve false.
getter = leer el dato 
setter = cambia el dato
### 2.2 Nodo<T> y ListaEnlazada<T>

Aclaracion de las plantillas definidas  completas en los .h porque el compilador necesita ver todo el codigo para poder generar la version concreta de cada tipo, por ejemplo listaEnlazada<T> no es una clase todavia es un molde, cuando escribo listaEnlazada<fecha>, el compilador toma el molde y  reemplaza T por fecha en ese momento si se crea una clase real.
Bueno como lo explique en la documentacion inicial y para no olvidarlo Nodo<T> es el vagon y ListaEnlazada<T> es el tren, el nodo solo sabe dos cosas, su dato y quien va despues, la lista no guarda datos por si misma, guarda la direccion del primer vagon (cabeza), la del ultimo (cola) y cuantos hay (cantidad). Cada funcion de la lista hace una de estas cuatro acciones sobre los nodos: crearlos (new), recorrerlos (siguiente), reenlazarlos (cambiar un siguiente) o destruirlos (delete).

class Nodo:

+T dato
+Nodo~T~* siguiente
+Nodo(T d)

Este actua como la unidad minima o eslabon individual dentro de la lista enlazada, su unica mision es contener un dato especifico de tipo y guardar al puntero de referencia hacia el siguiente nodo de la cadena.

Class ListaEnlazada:

-Nodo~T~* cabeza
-Nodo~T~* cola
-int cantidad
+ListaEnlazada()
+ListaEnlazada(ListaEnlazada otra)
+operator=(ListaEnlazada otra) ListaEnlazada
+~ListaEnlazada()
+tamano() int
+estaVacia() bool
+insertarFinal(T d)
+insertarOrdenado(T d, unsigned long* it)
+obtenerEn(int i, unsigned long* it) T∗
+eliminarEn(int i, unsigned long* it) bool
+vaciar()
+inicio() Iterador
+memoriaUsada() size_t

Esta se encarga de proveer una estructura de datos dinamica basada en nodos para almacenar colecciones de elementos de cualquier tipo (T). Aqui estas operaciones fundamentales son como insertar al final, insertar de forma ordenada, eliminar elementos obtener elementos por indice.

Class Iterador dentro de la lista: Es una clase pequeña que vive dentro de listaEnlazada<T>. su unico trabajo es recordar en que nodo va el recorrido. actualNodo (privado): el unico dato. Es un puntero al nodo donde esta parado el cursor. Es privado, asi que quien usa el iterador nunca ve los nodos, solo los datos. ConstructorIterador(Nodo<T>* n): deja el cursor parado en el nodo que le pasen haySiguiente(): devuelve true mientras el cursor este sobre el nodo real. Cuando se pasa del ultimo, vale nullptr y devuelve false: es la condicion de parada del ciclo. actual(): devuelve el dato del nodo donde esta el cursor. Devuelve T&(una referencia) para poder modificar el elemento en un sitio, por ejemplo marcar un mensaje como leido. avanzar(): pasa el cursor al siguiente nodo. inicio(): crea un iterador parado en cabeza. Es const porque no modifica la lista. 

### 2.3 Mensaje

Class mensaje:
atributos que tiene mensaje:
Emisor y receptor son punteros.
El receptor apunta al usuario que recibe el mensaje.
El emisor es un puntero al usuario que envio el mensaje.
Texto como string.
Leido como bool, esta leido true en caso contrario false.
fechaEnvio como fecha.

Uso dos constructores uno largo y completo recibe, receptor, fecha, texto y leido. Se usa al cargar el archivo.
El constructor corto recibe lo mismo pero sin leido y lo deja en false. Se usa al enviar un mensaje nuevo.
En mensaje decido permitir recibir cualquier caracter siempre y cuando el cuerpo del mensaje no este vacio. 
-textoEsValido (estatico) responde solo true/false, limpiarTexto (privado) cambia \t = tabulador por un espacio igual que los siguientes en linux y windows \n, \r = final de linea.
-Los limites con constantes: LONGITUD_MIN = 1, LONGITUD_MAX=512.
-Estado seguro si el texto no es valido:  texto vacio, fecha por defecto, punteros nulos, leido = false.
Falta por implementar:
Operador< que insertarOrdenado coloque los mensajes por fecha, comparando sus fechaEnvio con Fecha::operador< 

marcarLeido() cambiar leido a true despues de mostrar un mensaje nuevo, se usa en el momento de leer mensajes nuevos.

memoriaUsada() sumar la memoria de cada mensaje en el reporte, se usa en la medicion de recursos.

class Mensaje:
Privado:
-string texto
-Fecha fechaEnvio
-bool leido
-Usuario* emisor
-Usuario* receptor
-limpiarTexto(string texto) string

publico:
+unsigned int LONGITUD_MIN
+unsigned int LONGITUD_MAX
+Mensaje(string texto, Fecha fechaEnvio, Usuario* emisor, Usuario* receptor, bool
leido)
+Mensaje(string texto, Fecha fechaEnvio, Usuario* emisor, Usuario* receptor)
+textoEsValido(string texto) bool
+getTexto() string
+getFechaEnvio() Fecha
+estaLeido() bool
+getEmisor() Usuario∗
+getReceptor() Usuario∗

Nota: -limpiarTexto(string texto) string:
la decision de mantenerlo privado es porque esto es un paso interno del constructor, donde su trabajo es preparar el texto antes de validarlo y guardarlo.

## 2.4 Conceptos de C++ que se usan en el código


### `this` y `*this`

Los uso para distinguir el parametro del atributo. En el constructor de mensaje el parametro y el atributo se llaman igual (texto, leido, emisor..) para signar al atributo se escribe this->texto = limpio, this->texto es el atributo y texto a secas o soloes el parametro.
this es un puntero al objeto con el que se esta ejecutando el metodo. Dentro de un metodo de mensaje, this apunta al mensaje que se esta construyendo o usando. *this es el objeto mismo.
Para que uso this:
Uso this-> para acceder a un atributo. cuando el parametro y el atributo se llaman igual, 
this->texto es el atributo y texto es el parametro.
this->texto = limpio; // atributo = valor limpio.
This sin asterisco: comparar direcciones. En operador = se pregunta si el objeto que recibe es el mismo que el actual:
if (this != &otra) //  ¿ Mi direccion es distinta de la otra?
Aqui &otra es la direccion de otra, asi que se comparan dos direcciones: this con &otra. por eso va sin asterisco.
*this: Devolver el propio objeto. Al final de operador=:
return * this; //devuelve el objeto actual no su direccion.
El metodo devuelve ListaEnlazada&, una referencia al objeto, y para eso hay que entregar el objeto, no su direccion. Por eso va con asterisco.
Por eso en ListaEnlazada& asi se permite encadenar asignaciones (a= B = c).


### La referencia `&`

La referencia & tiene dos significados diferentes segun donde aparece:
Donde significado/ ejemplo del proyecto
En un tipo (parametro o retorno) Referencia otro nombre para un objeto que ya existe, sin copiarlo const std::string& texto, const FEcha& fechaEnvio, const T& d.
Delante de la variable direccion de memoria (operador direccion de) &otra en this !=&otra.

Por que las uso en los parametros?
porque evita copiar, pasar un std::string o una fecha por valor copiaria todo el objeto en cada llamada, con & se pasa solo el alias.
const impide modificar el original. Con const Fecha& la funcion puede leer la fecha pero no cambiarla.
Una referencia siempre apunta a un objeto valido no puede ser nula, a diferenciaa de un puntero.
Referencia frente a puntero: T& es un alias que no puede ser nulo ni cambiar de objeto, T guarda una direccion que puede ser nullptr y reasignarse. POr eso obtenerEn devuelve T puede devolver nullptr si el indice no existe, algo que la referencia no permite.

### `const` al final de un método
En bool operator<(const Fecha& otra) const o getTexto() const, el const final promete que el metodo no modifica el objeto. Es el que permite llamarlos sobre objetos y sobre const Fecha&.

## 2.5 Cómo se conectan Fecha, Mensaje y ListaEnlazada

### Relaciones entre las clases

Mensaje contiene una fecha (atributo fechaEnvio, por valor): Es composicion. La fecha vive y muere en el mensaje.
Mensaje apunta a Usuario con dos punteros (emisor, receptor): Es asociacion. El mensaje no es dueño de los uauarios y nunca los borra.

ListaEnlazada<T> es generica no sabe que guarda. Cada Nodo<T> guarda un T y el puntero al siguiente. puede ser ListaEnlazada fecha , ListaEnlazada mensaje o LIstaEnlazada<Usuario*>.



###Idea para medir memoria

ListaEnlazada<T>::memoriaUsada() suma por cada nodo, sizeof(Nodo<T>)-sizeof(T) mas dato.memoriaUsada(). Si "T" es mensaje, el metodo suma el tamaño del objeto, la memoria dinamica del texto (sizeof(std::string)) mas capacity() y llama a fecha::memoriaUsada(). Cada calse mide lo suyo y delega en lo que contiene.

### Por qué los punteros a `Usuario` no se cuentan dos veces

Mensaje guarda solo la direccion de los usuarios. La memoria de cada Usuario la cuenta RedSocial, que es quien lo contiene, si mensaje la sumara se duplicaria.
Por ejemplo supongo que tengo un Usuario llamado Camila, y Camila solo existe una vez en memoria, pero muchos mensajes apuntan a ella. Si cada mensaje se sumara la memoria de Camila, la contaria una vez por cada mensaje, y el total seria mayor mayor que lo que realmente ocupa el programa. 
NOTA: en la medicion de memoria, cada objeto se cuenta una vez, por quien lo posee. Mensaje suma sus punteros pero no los usuarios a los que apuntan, porque esos pertenecen a RedSocial; si no, un mismo usuario se contaria tantas veces como mensaje haya enviado.


### Qué pasa al copiar un `Mensaje` dentro de un nodo

Nodo<T> guarda el "T" por valor, asi que al insertar se copia el mensaje, se copian el texto y la fecha (copias completas) y los dos punteros(solo la direccion). Los Usuarios no se duplican, porque los punteros apuntan al mismo "Usuario".


## 3. Decisiones tomadas durante la implementación (continúan desde el ADR-004)

[[ADR-004-tipo-dato-texto|ADR-004 — Tipo de dato para texto]]
[[ADR-005-lista-simplemente-enlazada|ADR-005 — Lista simplemente enlazada con cola]]
[[ADR-006-fecha-como-clase-validada|ADR-006 — Fecha como clase validada]]
[[ADR-007-iterador-de-la-lista|ADR-007 — Iterador de la lista]]
[[ADR-008-reglas-del-texto-de-mensaje|ADR-008 — Reglas del texto de Mensaje]]


## 5. Diagrama de clases: qué cambia

-Fecha: operador<, setFecha, aTexto, getters, memoriaUsada, metodos estaticos de validacion.
-ListaEnlazada<T>:  Iterador anidado, eliminarEn, obtenerEn que devuelve T*, contador de iteraciones, copia profunda, operador= memoriaUsada.
-Mensaje: dos constructores, textoeEsValido, limpiarTexto, getters, constantes.

## 7. Problemas encontrados durante la implementación

1. Mayusculas en las clases y archivos (Fecha.h y fecha.h  son distintos en linux).
2. Un .h quedo en el src/ y el CMakeLists.txt tenia una ruta duplicada.
3. Error en operador< al comparar meses: detectado en la prueba.
4. perdi una version de nodo.h y listaEnlazada.h que no estaba en un commit, decido hacer commit por pieza.
5. Qt creator no me mostraba varios.h porque los tenia en el target equivocado del CMakeLists.txt
6. El contructor cortp de mensaje daba "out-of-line definition does not match any declaration" porque faltaba su declaracion identica en el .h.

## 8. Pendiente

1.  test_mensaje y el resto de Mensaje (operador<, marcarLeido, memoriaUsada).
2. Usuario minima, RedSocial minima, carga de archivo (quitar \r), busqueda de mensaje por rango con corte temprano.
3. Reporte de iteraciones y memoria; datos de prueba con 1000 o mas usuarios.
4. Diagrama de clases y ADR nuevos conforme se implemente cada pieza.



## 9. Enlace video

https://youtu.be/CG9DZf-NHwA