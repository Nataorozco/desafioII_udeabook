```mermaid
classDiagram
    class Fecha {
        -int dia
        -int mes
        -int anio
        +Fecha(int, int, int)
        +esMenorQue(Fecha) bool
        +esIgualA(Fecha) bool
        +imprimir()
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

    class Mensaje {
        -string texto
        -Fecha fechaEnvio
        -bool leido
        -Usuario* emisor
        -Usuario* receptor
        +marcarLeido()
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

    class SolicitudAmistad {
        -Usuario* remitente
        -Usuario* destinatario
        -char estado
        +aceptar()
        +rechazar()
    }

    class Nodo~T~ {
        -T dato
        -Nodo~T~* siguiente
    }

    class ListaEnlazada~T~ {
        -Nodo~T~* cabeza
        -Nodo~T~* cola
        -int tamanio
        +insertarFinal(T dato)
        +insertarOrdenado(T dato)
        +eliminar(T dato)
        +ListaEnlazada(ListaEnlazada otra)
        +obtenerEn(int indice) T
    }

    class RedSocial {
        -ListaEnlazada~Usuario*~ usuarios
        -unsigned char* matrizAdyacencia
        -int totalUsuarios
        +cargarDatos(string ruta)
        +guardarDatos(string ruta)
        +buscarUsuario(string nombre) Usuario*
        +calcularSugerencias(Usuario u, int k) ListaEnlazada
    }

    RedSocial "1" *-- "0..*" Usuario : contiene
    Usuario "1" *-- "0..*" Album : posee
    Album "1" *-- "0..*" Foto : contiene
    Usuario "1" --> "0..*" Mensaje : envia
    Usuario "1" --> "0..*" Mensaje : recibe
    Usuario "1" --> "0..*" SolicitudAmistad : recibe
    Usuario "1" *-- "1" Fecha : fechaNacimiento

    ListaEnlazada~T~ "1" *-- "0..*" Nodo~T~ : compuesta de
    Usuario ..> ListaEnlazada~T~ : usa
    RedSocial ..> ListaEnlazada~T~ : usa
```

> **Nota: "amigos":** la relación de amistad entre usuarios (muchos a muchos, de `Usuario` consigo mismo) no se dibuja como línea aparte queda representada por el atributo `ListaEnlazada<Usuario*> amigos` dentro de la propia clase `Usuario`. 


# Diagrama de clases — versión resumen



```mermaid
classDiagram
    class Fecha
    class Usuario
    class Mensaje
    class Album
    class Foto
    class SolicitudAmistad
    class Nodo~T~
    class ListaEnlazada~T~
    class RedSocial

    RedSocial "1" *-- "0..*" Usuario : contiene
    Usuario "1" *-- "0..*" Album : posee
    Album "1" *-- "0..*" Foto : contiene
    Usuario "1" --> "0..*" Mensaje : envia
    Usuario "1" --> "0..*" Mensaje : recibe
    Usuario "1" --> "0..*" SolicitudAmistad : recibe
    Usuario "1" *-- "1" Fecha : fechaNacimiento

    ListaEnlazada~T~ "1" *-- "0..*" Nodo~T~ : compuesta de
    Usuario ..> ListaEnlazada~T~ : usa
    RedSocial ..> ListaEnlazada~T~ : usa
```
