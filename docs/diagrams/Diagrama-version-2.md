
## tipo: diagrama version: 2 fecha: 2026-10-17

# Diagrama de clases — versión 2 (organizado en tres vistas)

Esta versión **continúa** la de la primera entrega (`05-Diseno-de-clases`), que no se modifica. Cambian las clases ya implementadas: `Fecha`, `Nodo<T>`, `ListaEnlazada<T>` y `Mensaje`. `Usuario`, `Album`, `Foto`, `SolicitudAmistad` y `RedSocial` siguen como en el diseño preliminar, aún sin implementar.

1. **Vista general:** todas las clases y cómo se relacionan.
2. **Dominio:** `RedSocial`, `Usuario`, `Mensaje`, `Album`, `Foto`, `SolicitudAmistad` y `Fecha`, con sus atributos y métodos.
3. **Estructuras de datos:** `ListaEnlazada<T>`, `Nodo<T>` e `Iterador<T>`.

`Usuario`, `Album` y `RedSocial` usan `ListaEnlazada<T>`: se ve en el tipo de sus atributos (por ejemplo `ListaEnlazada<Mensaje*> mensajesEnviados`).

## Vista general

```mermaid
classDiagram
    direction TB
    class RedSocial
    class Usuario
    class SolicitudAmistad
    class Mensaje
    class Album
    class Foto
    class Fecha
    class ListaEnlazada~T~
    class Nodo~T~
    class Iterador~T~
    RedSocial "1" *-- "0..*" Usuario : contiene
    Usuario "1" --> "0..*" SolicitudAmistad : recibe
    Usuario "1" --> "0..*" Mensaje : envia y recibe
    Usuario "1" *-- "0..*" Album : posee
    Album "1" *-- "0..*" Foto : contiene
    Mensaje --> Usuario : emisor y receptor
    Mensaje *-- Fecha
    Usuario *-- Fecha
    Foto *-- Fecha
    RedSocial ..> ListaEnlazada~T~ : usa
    ListaEnlazada~T~ "1" *-- "0..*" Nodo~T~ : compuesta de
    ListaEnlazada~T~ ..> Iterador~T~ : crea
    Iterador~T~ --> Nodo~T~ : apunta
```

## Dominio

```mermaid
classDiagram
    direction TB
    class RedSocial {
        -ListaEnlazada~Usuario*~ usuarios
        -unsigned char* matrizAdyacencia
        -int totalUsuarios
        +cargarDatos(string ruta)
        +guardarDatos(string ruta)
        +buscarUsuario(string nombre) Usuario*
        +calcularSugerencias(Usuario u, int k) ListaEnlazada
    }
    class Usuario {
        -string nombreUsuario
        -Fecha fechaNacimiento
        -string correo
        -string rutaFotoPerfil
        -string ciudad
        -string pais
        -Fecha fechaInscripcion
        -ListaEnlazada~Usuario*~ amigos
        -ListaEnlazada~Mensaje*~ mensajesEnviados
        -ListaEnlazada~Mensaje*~ mensajesRecibidos
        -ListaEnlazada~SolicitudAmistad*~ solicitudesRecibidas
        -ListaEnlazada~Album*~ albumes
        +Usuario(nombre, fecha, correo, foto, ciudad, pais)
        +Usuario(Usuario otro)
        +enviarSolicitud(Usuario destino)
        +aceptarSolicitud(SolicitudAmistad s)
        +amigosEnComun(Usuario otro) int
    }
    class SolicitudAmistad {
        -Usuario* remitente
        -Usuario* destinatario
        -char estado
        +aceptar()
        +rechazar()
    }
    class Mensaje {
        -string texto
        -Fecha fechaEnvio
        -bool leido
        -Usuario* emisor
        -Usuario* receptor
        +unsigned int LONGITUD_MIN$
        +unsigned int LONGITUD_MAX$
        +Mensaje(string texto, Fecha fechaEnvio, Usuario* emisor, Usuario* receptor, bool leido)
        +Mensaje(string texto, Fecha fechaEnvio, Usuario* emisor, Usuario* receptor)
        +textoEsValido(string texto) bool$
        -limpiarTexto(string texto) string$
        +getTexto() string
        +getFechaEnvio() Fecha
        +estaLeido() bool
        +getEmisor() Usuario∗
        +getReceptor() Usuario∗
    }
    class Album {
        -string nombre
        -string ruta
        -char privacidad
        -ListaEnlazada~Foto*~ fotos
        +agregarFoto(Foto f)
    }
    class Foto {
        -Fecha fechaCaptura
        -int tamanio
        -string ruta
        -int likes
        +darLike()
        +quitarLike()
    }
    class Fecha {
        -int dia
        -int mes
        -int anio
        +int ANIO_MIN$
        +int ANIO_MAX$
        +Fecha()
        +Fecha(int d, int m, int a)
        +esValida(int d, int m, int a) bool$
        +esBisiesto(int a) bool$
        +diasDelMes(int m, int a) int$
        +getDia() int
        +getMes() int
        +getAnio() int
        +setFecha(int d, int m, int a) bool
        +operator<(Fecha otra) bool
        +aTexto() string
        +memoriaUsada() size_t
    }
    RedSocial "1" *-- "0..*" Usuario : contiene
    Usuario "1" --> "0..*" SolicitudAmistad : recibe
    Usuario "1" --> "0..*" Mensaje : envia y recibe
    Usuario "1" *-- "0..*" Album : posee
    Album "1" *-- "0..*" Foto : contiene
    Mensaje "0..*" --> "1" Usuario : emisor / receptor
    Mensaje *-- Fecha : fechaEnvio
    Usuario *-- Fecha : nacimiento e inscripcion
    Foto *-- Fecha : fechaCaptura
```

## Estructuras de datos

```mermaid
classDiagram
    direction TB
    class ListaEnlazada~T~ {
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
    }
    class Iterador~T~ {
        -Nodo~T~* actualNodo
        +Iterador(Nodo~T~* n)
        +haySiguiente() bool
        +actual() T
        +avanzar()
    }
    class Nodo~T~ {
        +T dato
        +Nodo~T~* siguiente
        +Nodo(T d)
    }
    ListaEnlazada~T~ "1" *-- "0..*" Nodo~T~ : compuesta de
    ListaEnlazada~T~ ..> Iterador~T~ : crea con inicio()
    Iterador~T~ --> Nodo~T~ : apunta al nodo actual
```