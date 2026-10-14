
## a. Análisis del problema

- Qué es Ude@Book y en qué consiste la red social a nivel funcional (perfil, amigos, mensajes, álbumes/fotos, sugerencias).
- Ude@Book aspira posicionarse como una compañia lider en el sector de las redes sociales, para ello la idea es conformar una amplia comunidad virtual en el territorio colombiano. El objetivo de este desafio consiste en desarrollar un programa que provea las funcionalidades basicas de la red social, utilizando POO. muy importante tener en cuenta que en esta parte del desafio solo vamos a trabajar en la capa logica, destinada a gestionar eficientemente la informacion de los usuarios, albumes, fotos, grupos, amigos entre otros. Teniendo en cuenta lo mencionado anteriormente  se sabe que la informacion que debe tener  Ude@Book de cada usuario es la siguiente: su nombre de usuario unico, fecha de nacimiento, correo electronico, foto de perfil ojo aqui no es visual solo la ruta de la foto, ciudad, pais y una fecha de inscripcion en la plataforma:
- Cada usuario posee:
- Cero o mas amigos los cuales son otros usuarios registrados en la plataforma con los que se define una mutua relacion de amistad.
- Un conjunto de mensajes que ha enviado, estos ordenados por fecha de envio, los cuales tienen dos estados leido o no leido.
- Un conjunto de solicitudes de amistad, las cuales pueden aceptar o rechazar.
- UN conjunto de sugerencias de amistad, estas muestran a los amigos de sus amigos directos, y se rankean segun la cantidad de amigos en comun.
- Cero o mas albumes, los cuales tienen un nombre, una ruta al almacenamiento y una configuracion de privacidad, pudiendo ser, publicos, privados o solo amigos. Adicionalmente cada album  contiene cero o mas fotos.
- De cada foto se conoce, la fecha de su captura, tamaño, ruta al archivo de almacenamiento y conteo de likes. Cada foto pertenece a un unico album.

EJEMPLO VISUAL DE LO QUE SE DEBE MOSTRAR POR CONSOLA:
- ![Pasted image 20261008171813.png](../../Pasted%20image%2020261008171813.png)

* FUNCIONALIDADES ENSENCIALES DEL MENU VISUALIZADO POR CONSOLA:

I.CARGA/ACTUALIZACION DE DATOS:
 Nota se requieren los  algoritmos necesarios para leer y actualizar los datos desde hacia el almacenamiento permanente.
 Teniendo en cuenta que esta funcionalidad no debe aparecer en el menu presentado a los usuarios. Para esta funcionalidad voy a usar el algoritmo, -tokenizacion por delimitador (lectura), con los siguientes archivos: Usuarios.txt, amigos.txt, solicitudes.txt, mensajes.txt, albumes.txt, fotos.txt. 
 Esto porque debemos tener en cuenta que aqui se nos solicita diseñar el formato de uno o mas archivos destinados a contener la informacion de los usuarios, amigos, solicitudes de amistad, mensajes y otros pero esta funcionalidad no debe aparecer en el menu presentado a los usuarios, aqui no se habla del archivo como tal si no de cuando se ejecuta a la funcion cargarDatos(), guardarDatos() significa que el usuario nunca debe ver una opcion en el menu tipo cargar datos para elegirlo manualmente si no que la carga debe pasar automaticamente al iniciar el programa antes de mostrar el menu por primera vez y el guardado debe pasar auntomaticamente al cerrar el programa o despues de cada operacion que modifique datos sin que el usuario tenga que pedirlo. 
 Su funcion internamente seria usuario.txt aqui el programa va leyendo caracter por caracter hasta encontrar tabulador ('\t') aqui seria como cuando vas leyendo la lista del mercado y te encuentras la coma es como tabulador, aqui el programa se detiene guarda la informacion hasta encontrar de nuevo tabulador ('\t') este proceso se repite hasta leer toda la informacion del usuario como direccion, correo,  etc. NOTA de esta misma forma funciona o se aplica a los 6 archivos del sistema, cambiando unicamente la cantidad y el tipo de campos de cada linea.

II. INGRESO A LA PLATAFORMA Y VISUALIZACION DE MEJORES AMIGOS:
Esta es una funcionalidad sencilla que permite al usuario iniciar sesion con las credenciales personales y mostrar el menu principal, aqui se le deben mostrar 3 fotos de perfil seleccionadas aleatoriamente entre sus amigos, se deben mostrar a la vez y debe estar acompañadas de una opcion que permite actualizarlas por otro grupo de 3 fotos distintas, con la precaucion de que no se visulice la misma foto repetida en un set de 3 o con algun patron de visualizavion fijo. NOTA: La actualizacion de fotos de perfil de amigos solo puede realizarse una unica vez.

Todos los amigos no tienen la misma prioridad, ejem usuarios con 10 o menos amigos en comun tienen una probabilidad de visualizacion simple, los que tienen entre 11 y 20 en comun 2.5 veces mas veces de probabilidad y los que tienen mas de 20 amigos en comun 3.5 veces mas prioridad de aparecer. 
Teniendo en cuenta lo mencionado en este enunciado aqui voy a utilizar estos dos algoritmos.

 -Algoritmo Busqueda lineal: para encontrar al usuario que se esta logueando, ¿como uso este algoritmo y por que?: Aqui el usuario ingresa su nombre, pero el programa necesita validar si el usuario si existe en la base de datos, lo que el programa hace es que recorre la lista de usuarios ya cargada en memoria, en este punto yo imagino la lista como una fila de personas con gafas y en sus gafas llevan el nombre, entonces me voy recorriendo la fila persona por persona deteniendome a mirar su nombre lo verifico si no es continuo con esta misma accion en el caso de que recorra toda la fila y no vea ninguna persona con ese nombre simplemente digo que esa persona no se encuentra en la fila, esto mismo lo aplico en el programa si una persona intenta loguerse la lista recorre buscando el nombre ingresado y si ese nombre no aparece simplemente imprime usuario no encontrado o usurio no registrado. Algoritmo de busqueda lineal.
 
 -Algoritmo Muestreo ponderado por acumulacion de pesos: Este algoritmo lo voy a usar exactamente en ingreso a la plataforma y visualizacion de mejores amigos, en el momento justo despues del login, cuando el programa ya verifico las credenciales y debe mostrar, junto con el menu principal, las 3 fotos del perfil de amigos seleccionados aleatoriamente y tambien lo voy a reutilizar en la funcionalidad cuando el usuario pide, actualizar por otro grupo de tres fotos distintas (recordando que  esta actualizacion solo se puede hacer una vez ).  
 Como funciona este algoritmo, cada amigo tiene un peso segun la cantidad de amigos en comun que tenga con el usuario que inicio sesion. Estos pesos se van acumulando uno tras otro, formando tramos sobre una recta ejemplo como una rifa de papelitos, donde un amigo con mas peso ocupa un tramo mas grande. El programa genera un numero aleatorio entre 0 y la suma total de los pesos, y se busca en que tramo cae ese numero para saber cual amigo fue elegido un amigo con mas amigos en comun tiene mas probabilidad de salir elegido porque tiene un tramo mas grande, lo cual podia hacer que saliera elegido en mas de una de las 3 fotos por eso, cuando un amigo ya fue elegido, se elimina de la lista de candidatos y se recalcula el total de pesos para que no vuelva a salir. Este proceso se repite 3 veces para obtener las 3 fotos distintas.

III.ADMINISTRAR AMISTADES:
Aqui al usuario se le permite acceder a las opciones:
a) Enviar solicitud de amistad: Dado un nombre de usuario, envia la solicitud de amistad a alguno de los usuarios de la plataforma, siempre que no sean amigos o no tenga pendiente una solicitud de amistad de esa persona.
Aqui en la opcion a) voy a usar el algoritmo busqueda lineal, porque necesito verificar en la lista usuario que el destino existe, se continua verficando que usuario no este en la lista de amigos y luego con este mismo algoritmo verificar en solicitudesRecibidas que no tenga solicitudes de este usuario pendientes. 
Si todo pasa: Insercion simple en la lista enlazada, se agrega la nueva solicitudAmistad a solicitudesRecibidas  del destino.
b) Aceptar solicitudes de amistad recibidas: Permite ver la lista de solicitudes de amistad recibidas y aceptar cualquiera de ellas.
Aqui en la opcion b, voy a usar el algoritmo de insercion simple x2,  porque aqui hay dos listas involucradas la de la persona que envia la solicitud de amistad y la de la persona que recibe la misma, cuando la solicitud de amistad se acepta los dos usuarios pasarian  a ser amigos entonces en ambas listas se haria una insercion, en el que la envia  se inserta el usuario que la acepta y en el que la acepta se inserta el que la envia, esta seria insercion simple x2 y finalmente eliminacion en la lista enlazada quita la solicitud ya atendida, en resumen.
El algoritmo recorrido lineal lista las solicitudes recibidas, insercion simple x2 agrega cada usuario en la lista del otro y eliminacion en la lista enlazada quita la solicitud ya atendida en solicitudes recibidas.

IV. VISITAR PERFIL DE UN AMIGO:
Aqui se pide, dado el nombre de usuario de un amigo, lista sus albumes de fotos con categoria de privacidad "amigos " o "publico". Se puede seleccionar un album cuyas fotos se visualizaran en modo carrucel: pudiendo cambiarse una tras otra de manera circular.
NOTA: Aclaracion aqui lo que se pide como tal no es la visualizacion de la foto, es la ruta  lo que se maneja internamente la ruta el string ruta que ya tiene la clase foto, no una visualizacion real de la imagen, el programa simplemente dice la foto que estas viendo ahora esta en esta ruta con las opciones  de siguiente/previa o te mueves a la ruta de otra foto dentro del mismo album.
Al visualizar cada foto, el usuario tiene 4 opciones: salir del album, siguiente, previa, dar/quitar like a la foto.

En resumen: 
Recorrido lineal sobre los albumes del amigo, filtrando por privacidad ('A' o 'P').
Seleccion de un album navegacion circular por indice sobre sus fotos (siguiente/previa).
Salir corta la navegacion, sin calculo.
Like/quita,  like resuelto con los metodos existentes en foto.

Entonces como el usuario tiene 4 opciones:
SIGUIENTE/PREVIA: Se sabe que un album tiene  -ListaEnlazada<foto*> fotos.
obtenerEn(int indice) me sirve para ir a buscarla.
Me voy con siguiente/previa ¿como la pienso implementar?. Pongo un ejemplo que el usuario tiene 5 fotos pero el sistema internamente empieza a contar desde 0 entonces como tal el 5 no seria una opcion valida, lo que quiere decir que el usuario empieza a mirar las fotos y cuando llega a la opcion 4 se devuelve a 0 osea a la primera foto y si esta en cero y le da la previa simplemente vuelve nuevamente a la opcion 4.

DAR/QUITAR LIKE A LA FOTO:
Esta opcion ya esta en el diagrama de clases en la clase (foto) ya tiene los metodos darLike() y quitarLike().
Aqui voy a usar el algoritmo de recorrido lineal, para pasar por todos los albumes del amigo uno por uno, pero revisando en cada uno el valor de (privacidad) me quedo muestro solo los que son  'A' = amigos  o 'P' = publico, descartando 'V'= privados.

V. VER SUGERENCIAS DE AMISTAD:
Dado un valor K entero (entre 1 y 20), esta funcionalidad debe mostrar K sugerencias de amigos, ordenadas segun la cantidad de amigos que tiene en comun. Debe acompañarse de la opcion enviar solcitud  a alguno de ellos.
Se debe tener en cuenta el concepto de la matriz de adyacencia para representar la relacion de amistad.
Bueno aqui yo pienso que como en el diagrama tengo unsigned char* matrizAdyacencia dentro de RedSocial y aqui ya mi pregunta fue, que voy a representar en esta  matriz?, ejemplo: Si tengo 4 usuarios (Ana, Beto, Carla, Diego) y Ana es amiga de Beto y de Carla, pero no de Diego entonces, como represento esta informacion en una matriz una tabla de filas y columnas? que iria en las filas, que en las columnas, y que valor podria poner en cada celda para indicar si son amigos o no son amigos?.
La respuesta fue que la matriz se puede representar como una tabla de doble entrada donde tanto filas como columnas representan a los usuarios en orden numerico por ejemplo del 0 al 3 se podria poner 1 true 0 false.  (0=Ana, 1=Beto, 2=Carla, 3=Diego), y en cada celda matriz[i]  [j]  poner 1 (o true) si el usuario i y el usuario j son amigos, y 0 (false) si no lo son.
Esta propiedad que matriz[i]  [j] siempre sea igual a matriz [j]  [i]  se llamaria simetrica porque la amistad siempre va en ambos sentidos.

Ejemplo visual de la matriz de adyacencia.

![Pasted image 20261012174843.png](../../Pasted%20image%2020261012174843.png)

Aqui en esta funcionalidad tambien se nos pide calcular cuantos amigos en comun se tiene con cada candidato para poder ordenarlos.
Necesito ir guardando una variable acumuladora, un contador entero, por ejemplo: int contadorComun = 0. Esta variable empezaria en 0 justo antes de empezar a revisar; su trabajo es ir sumando +1 cada vez que se encuentra una coincidencia es decir cada vez que las dos filas tengan un 1 en la misma columna.
Para repetir puedo utilizar un ciclo for que recorra todas las columnas de la matriz, desde el primer usuario hasta el ultimo 0 hasta total usuarios -1 ejemplo de los pasos seria:
Primero me paro en la columna i, que representa a un usuario del sistema, ya sea Carla, Beto, un usuario nuevo, etc.
Segundo paso, miro la celda de Ana en esa columna (matrizAna[i]  ) y la celda de Diego en esa misma columna (matrizDiego[i]).
Tercer paso me pregunto con If ¿ambos valores son 1? si lo son, se aumenta el contador (contadorComun++). Si no lo son, no se hace nada y se pasa a la siguiente columna.
Cuarto paso, al terminar de recorrer toda la fila de un extremo a otro, el valor final queda guardado en contadorComun es el numero total exacto de amigos en comun entre Ana y Diego.
Ese numero total es el que uso para saber en que rango cae (menor o igual a 10, 11-20  o mayor a 20) y poder asignarle su propio peso en la ruleta de mejores amigos o en el ranking de sugerencias.
Aqui uso el algoritmo de insercion ordenada que esta documentado para la lista enlazada, con esta parte se ahorra tener que calcular todo, meterlo en desaorden con un metodo pesado. Se puede aplicar de forma dinamica mientras se va calculando, se itera candidato por candidato, se toma el primer candidato valido que cumple, se calcula su puntuacion usando el cruce de filas en la matriz para contar sus amigos en comun con Ana. El numero total de coincidencias en 1, y se inserta de inmediato de forma ordenada en lugar de guardar el resultado en un vector desordenado llamando a la funcion de insercion ordenada, por ejemplo en ListaEnlazada<sugerencia>, pasandole el candidato y su cantidad de amigos en comun.
En este punto la funcion de insercion ordenada se encargara de buscar el lugar correcto en la lista ordenada de mayor a menor cantidad de amigos en comun, y meterlo ahi mismo. Entonces se controla el limite K por ejemplo, K=5, el algoritmo de insercion puede descartar automaticamente al nuevo candidato si su puntaje es menor al peor de la lista, o bien insertar al nuevo y eliminar al ultimo de la lista para mantener siempre su tope  de k elementos.
De esta manera, cuando se termina de revisar a todos los usuarios del sistema, la lista de sugerencias ya estaria completamente ordenada y lista para mostrarse, sin necesidad de un proceso extra de ordenamiento.
Por otro lado, el objetivo de una sugerencia de amistad es descubrir gente nueva que uno no conoce y que aun no esta agregada. ya soy amigo de esta persona cuando el valor es 1 por ejemplo, matriz[Ana][candidato] ==1 si al revisar la columna del candidato en la fila de Ana se encuentra en 1, significa que ya hay una relacion de amistad directa y el sistema debe detectarlo.

Algoritmos usados en esta parte:
Algoritmo 2 Matriz de adyacencia, para representar la relacion de amistad y poder contar amigos en comun entre Ana o x usuario y cada candidato.
Algoritmo 3 Insercion ordenada, para ir armando la lista de K sugerencias ya ordenada de mayor a menor, sin necesitar un ordenamiento aparte al final.
En la parte de enviar solicitud a alguno de ellos, la ultima parte del enunciado, se reutiliza toda la cadena que ya se menciono en la funcion III.
Busqueda lineal las verificaciones de existencia, no amigo, no solicitud pendiente.
Insercion simple, para agregar la nueva  solicitudAmistad a solicitudesRecibidas del destinatario.

VI. ADMINISTRAR MENSAJES: 
Aqui se nos pide que esta funcionalidad permita:
A). Enviar mensaje: dado el nombre de un amigo, enviale un texto de hasta 512 caracteres.
B). Leer nuevos mensajes: que permita visualizar los mensajes recibidos que no han sido leidos, ordenados por fecha de envio. Se muestran todos los menssajes indicando el emisor de cada uno, luego de lo cual deben marcarse como leidos.
C). Buscar mensajes por rango de fecha: dada una fecha de inicio y una fecha de fin, se deben listar todos los mensajes recibidos en ese rango de (ambas inclusive).
Bueno aqui para dar cumplimiento a la parte:
A) de la funcionalidad, me cuestiono que primero para encontrar el usuario destinatario apartir de su nombre, debo usar el algoritmo de busqueda lineal para encontrar al usuario y una vez encontrado, el nuevo mensaje hay que agregarlo tanto a la lista mensajesEnviados del emisor como a mensajesRecibidos del receptor entonces aqui uso el algoritmo de insercion ordenada.
B) Aqui lo primero que tengo que tener claro es que los mensajes como ya decidi que mensajesRecibidos se mantiene ordenada por fecha gracias al algoritmo de insercion ordenada ya no necesito ordenar nada aqui solo recorrer y filtrar.  Y para recorrer voy a usar el agoritmo de recorrido lineal ya mencionado en la funcion IIIb, porque  se recorre la ListaEnlazada<T> completa de principio a fin, sin detenerce antes de llegar al final, evaluando una condicion en cada elemento, finalmente despues de mostrar cada mensaje no leido que aqui seria tipo bool y como esta en la clase mensaje del diagrama marcaLeido() simplemente pone leido=true. 
C) Ahora para buscar los mensajes con rango de fecha, voy a usar el algoritmo busqueda lineal con corte temprano, que ya de por si estaba pensado para recorrer la lista ordenada por fecha hasta encontrar el inicio del rango, acumular mientras este dentro del rango, y detenerse apenas se pase la fecha final, sin necesidad de recorrer el resto.

ACLARACIONES TECNICAS A TENER EN CUENTA:
En esta version de la plataforma no se requieren funcionalidades para:
-Registrarse en la plataforma o eliminar una cuenta.
-Crear, cargar, editar y eliminar albumes y fotos. ya estan creados y toda su informacion se carga desde el almacenamiento permanente.
-Responder los mensajes leidos de forma directa.
-Cualquier otra no especificada por el cliente en este enunciado.
-En esta version no es necesario validar que cada usuario de un unico like por foto.


VII. MEDICION DEL CONSUMO DE RECURSOS:
Aqui se nos pide que al finalizar la ejecucion de cada una de las funcionalidades requeridas, se deben mostrar en pantalla dos metricas para cuantificar la eficiencia:
A). Cantidad de iteraciones requeridas (directa e indirectamente) para completar esa funcionalidad especifica. si en algun caso se invoca un componente externo debe reportarse su uso.
Aqui es de tener claro que hay que contar tanto las iteraciones del ciclo directo que estan dentro de la funcion por ejemplo: Dentro de enviarSolicitud() como las que ocurren indirectamente dentro de cada llamada a otra funcion por ejemplo buscarUsuario(), porque cuando el programa ejecuta una funcionalidad, el costo total de la operacion incluye todo lo que manda a hacer en cadena. 
Por otro lado, si se invoca un componente externo como rand(), no tendria sentido sumarlo al contador de iteraciones junto con los ciclos for y while propios, porque en el analisis de algoritmos las iteraciones sirven para medir como crece el esfuerzo a medida que aumenta la cantidad de datos. rand() es una funcion de la biblioteca estandar de Ctt que ejecuta una operacion matematica interna de tiempo constante, por lo que se reporta aparte en vez de contarse como una iteracion mas.
B). El total de memoria que esta consumiendo en ese momento exacto de la ejecucion, por causa de todas las estructuras de datos y objetos existentes en el sistema. incluya en este valor las variables locales y parametros por valor involucrados en la funcionalidad.
En esta parte para llevar a cabo lo que se pide la idea es ir desde la raiz (RedSocial) hasta las hojas (foto,mensaje) sumando en cada nivel, se podria conectar por ejemplo cada clase usuario, album, foto,mensaje, solicitudAmistad, LIstaEnalzada<T> tendria su propio metodo memoriaUsada() pero se tiene presente que normalmente esto no lo puede calcular sola REdSocial::memoriaUsada() porque esos datos se estan ejecutando en ese momento, no son atributos de ninguna clase, entonces esto se puede sumar a mano dentro de cada funcion, ya que Ctt no cuenta con mecanismo automatico, que le permita a una clase saber que variables estan viviendo en el stack de una funcion en un momento dado, por esta razon no lo hace RedSocial, las variables locales como contadores, indices (i) o parametros solo existen  temporalmente mientras la funcion se esta ejecutando. Con sizeof(string) hay que resolver un detalle fundamental de Ctt ya que solo devuelve el tamaño de la estructura contenedora, el objeto en si vive en la memoria, que suele ocupar 24 a 32 bytes dependiendo de la arquitectura la solucion para calcular la memoria real que esta consumiendo se debe sumar el contenido fijo mas el espacio dinamico reservado.  Memoria total del string = sizeof(std::string) + str.capacity().

## b. Diagrama de clases UML

**Diagrama de clases completo:** [Ver diagrama Mermaid](../diagrams/05-Diseno-de-clases.md.md)


DIAGRAMA SIMPLIFICADO

![Pasted image 20261010153753.png](../../Pasted%20image%2020261010153753.png)

[Ver el diagrama simplificado en detalle](../diagrams/05-Diseno-de-clases.md.md)

DIAGRAMA UML COMPLETO

![Pasted image 20261010154007.png](../../Pasted%20image%2020261010154007.png)

[Ver el diagrama UML completo en detalle](../diagrams/05-Diseno-de-clases.md.md)

 > **Nota sobre "amigos":** la relación de amistad entre usuarios (muchos a muchos, de `Usuario` consigo mismo) no se dibuja como línea aparte — queda representada por el atributo `-ListaEnlazada<Usuario*> amigos` dentro de la propia clase `Usuario`. 

RESPOSABILIDADES DE CADA CLASE:

1. RedSocial  (Clase principal/ Gestor del sistema)

Responsabilidad: Actua como el contador de toda la aplicacion. Se encarga de administrar el conjunto global de usuarios, manejar la matriz de adyacencia (para calcular grafos de coxiones), persistir la informacion (guardar y cargar datos) y calcular las sugerencias de amistad.

2. Usuario (entidad central)

Responsabilidad: Representar a un miembro registrado en la red social. Almacena toda su informacion personal como: Nombre, correo, ubicacion, foto de perfil y gestiona sus propias colecciones o listas internas, como sus amigos, mensajes enviados/recibidos, albumes y solicitudes de amistad.

3. Fecha (Gestion temporal)

Responsabilidad: Modelar y estructurar fechas (dia, mes, año). Permite realizar operaciones de comparacion, usa algo como esto: mediante la sobrecarga de operador <, que permite comparar directamente dos objetos como, fecha1 < fecha2 ejemplo la fecha de nacimiento de un usuario con la de otro o cualquier par de fechas del sistema.

4. Mensaje (comunicacion)

Responsabilidad: Representar una comunidad individual entre un usuario emisor y un usuario reseptor. Almacena el texto, la fecha de envio, el estado de lectura(bool leido) y ofrece metodos para marcar el mensaje como leido.

5. Album (Organizacion multimedia)

Rsponsabilidad: Agrupar y organizar colecciones de fotografias asociadas a un usuario bajo su nombre, ruta y nivel de privacidad especificos, permitiendo incorporar nuevas imagenes al conjunto.

6. Foto (Elemento multimedia)

Responsabilidad: Almacenar los metodos detallados de una fotografia individual(fecha de captura, tamaño, ruta de almacenamiento y contador de "likes), ademas de permitir interactuar con ella mediante los metodos de dar o quitar like

7. SolicitudAmistad (Interaccion social)

Responsabilidad: Controlar el estado y flujo de una peticion de conexion entre el usuario remitente y destinatario, permitiendo ejecutar las acciones de aceptar o rechazar la solicitud.

8. ListasEnlazadas<T> (Estructura de datos generica)(ejem tren)

Responsabilidad: Proveer una estructura de datos dinamica basada en nodos para almacenar colecciones de elementos de cualquier tipo (T). Aqui estas operaciones fundamentales como insertar al final, insertar de forma ordenada, eliminar elementos y obtener elementos por indice.

9. Nodo<T>(Eslabon de la estructura)(ejem vagon del tren)

Responsabilidad: Actuar como la unidad minima o eslabon individual dentro de la lista enlazada. su unica mision es contener un dato especifico de tipo <T> y guardar al puntero de referencia hacia el siguiente nodo de la cadena

EXPLICACION PORQUE NO HAY HERENCIA Y COMO SE RESOLVIERON LAS RELACIONES SOLO CON COMPOSICION/ASOCIACION.

1. No hay herencia por la restriccion que no se debe usar herencia en este diagrama.

2. No se usa herencia que es cuando una clase hereda a otra, como decir el administrador es un usuario, este diagrama se enfoca en realaciones estructurales de uso, las caules se dividen en tres categorias.

*Composicion:  (Rombo relleno ◆) es una relacion  de propiedad estricta y ciclo de vida compartido.
-Se usa cuando una clase es dueña absoluta de la otra y la otra parte no puede existir sin contenedor, si el contenedor se destruye, los elementos dentro mueren con el.
Ejem:
RedSocial ◆---  usuarios. RedSocial es dueña de los usuarios.
Album ◆---  foto, el album contiene las fotos.
ListaEnlazada ◆--- Nodo La lista es dueña de los nodos (el tren es dueño de los vagones).

*Asociacion dirigida: (flecha continua → ) es una relacion de conocimiento, interaccion o colaboracion.
-Se usa cuando una clase se conecta, interactua o conoce a otra pero sin poseerla ni ser dueña de su existencia, no hay una dependencia de vida estricta.
Ejem:
Usuario → mensaje. El usuario interactua con los mensajes, los manda o los lee, pero el mensaje es un objeto independiente que viaja de un emisor a un receptor.
Usuario → solicitud de amistad. El usuario gestiona solicitudes, pero la solicitud es una entidad de enlace temporal.
Usuario  → album. El usuario apunta a los albumes.

*Dependencia: (flecha punteada ╌╌>) con la etiqueta usa: Es una relacion de uso temporal o herramienta. 
-se usa cuando una clase simplemente necesita a otra de forma temporal.
Ejem: pasandola como parametro en una funcion o para construir algo, pero no almacena una copia permanente de ella como parte de su estructura principal.
RedSocial  ╌╌> ListaEnlazada (etiquetada como usa). La  RedSocial utiliza las ListasEnlazadas para organizar a sus usuarios.
Usuario  ╌╌> ListaEnlazada (Etiquetado como usa). El usuario utiliza listas enlazadas para guardar sus amigos o mensajes.

RESUMEN:
Rombo relleno (◆ composicion). Es dueño absoluto y lo contiene fisicamente ejemplo sencillo un tren si el tren no existe los vagones tampoco.

Flecha continua ( → ) se comunican, interactuan o se relacionan entre directamente ejemplo sencillo alguien revisando sus mensajes.

Flecha punteada (╌╌> Dependencia)con la palabra usa los servicios o metodos de otra clase temporalmente.

¿Por que no es herencia?
Porque si dijeramos que es herencia significaria que un album es un tipo de usuario lo cual no es verdad porque un album no es una persona. O que foto es un tipo de album tampoco seria correcto porque una foto no es un contenedor de fotos, es una unidad individual.


¿Por que si es composicion?

La composicion representada por un rombo relleno ◆ tiene un o es parte de:
Ejem: Entre un album y foto, un album tiene un conjunto de fotos y una foto le pertenece a album.
Si se borra el album completo de la base de datoso de la memoria, esas fotos individuales pierden su contenedor principal y tambien son eliminadas, las fotos no existen sueltas por la red social sin pertenecer a ningun lado, su ciclo de vida depende enteramente del album que las contiene.

Entre la RedSocial y el usuario, los usuarios le pertenecen al sistema de esa red social, si la red social cierra o se destruye, los usuarios registrados en ella dejan de pertenecer a ese sistema.

En conclusion:
La herencia se usa para compartir codigo entre las jerarquias similares (un administrador es un usuario) en cambio la composicion se usa cuando se arman objetos complejos juntando piezas que le pertenecen (un album tiene fotos y un usuario tiene albumes).

La razon por la que la composicion y la asociacion funcionan igual de bien o incluso mejor que la herencia se debe al principio fundamental en la programacion orientada a objetos conocida como composicion sobre herencia.

Funciona muy bien por estas razones: 
*Flexibilidad y evita jrearquias rigidas.
La herencia crea una cadena de parentesco muy rigida. Si yo intentara usarla para todo, terminaria forzando relaciones extrañas solo para que las clases compartan codigo ejem, intentando hacer que un album herede caracteristicas de un usuario.

La composicion y la asociacion actuan como piezas  construidas bajo el concepto de modularidad, permiten que objetos totalmente independientes se conecten porque se necesitan, (Album contiene foto, usuario posee album) sin atar sus naturalezas de forma forzada.

RESPONSABILIDAD UNICA:
Al no depender de una clase padre, cada entidad del diagrama mantiene una responsabilidad clara y aislada. NOTA: Aqui la clase padre no es el enfoque la menciono para poner el ejemplo.(no aplica).
El album solo se encarga de agrupar fotos.
El usuario solo gestiona su perfil y sus listas.
La listaEnlazada solo maneja nodos y punteros.

La conclusion final es que utilizar relaciones en lugar de herencia logra un diseño limpio, facil de entender.


## C. Algoritmos


* ALGORITMO MUESTREO PONDERADO POR ACUMULACION DE PESOS(1)

 LOGIN - MEJORES AMIGOS
 
Este algoritmo lo voy a usar exactamente en ingreso a la plataforma y visualizacion de mejores amigos, en el momento justo despues del login, cuando el programa ya verifico las credenciales y debe mostrar, junto con el menu principal, las 3 fotos del perfil de amigos seleccionados aleatoriamente y tambien lo voy a reutilizar en la funcionalidad cuando el usuario pide, actualizar por otro grupo de tres fotos distintas (recordando que  esta actualizacion solo se puede hacer una vez ).  
 Como funciona este algoritmo, cada amigo tiene un peso segun la cantidad de amigos en comun que tenga con el usuario que inicio sesion. Estos pesos se van acumulando uno tras otro, formando tramos sobre una recta ejemplo como una rifa de papelitos, donde un amigo con mas peso ocupa un tramo mas grande. El programa genera un numero aleatorio entre 0 y la suma total de los pesos, y se busca en que tramo cae ese numero para saber cual amigo fue elegido un amigo con mas amigos en comun tiene mas probabilidad de salir elegido porque tiene un tramo mas grande, lo cual podia hacer que saliera elegido en mas de una de las 3 fotos por eso, cuando un amigo ya fue elegido, se elimina de la lista de candidatos y se recalcula el total de pesos para que no vuelva a salir. Este proceso se repite 3 veces para obtener las 3 fotos distintas.

El enunciado pide que la probabilidad de seleccion no sea uniforme un usuario con mas amigos en comun debe tener mas chance de aparecer, esto se resuelve con un muetreo ponderado por acumulacion de pesos:
1 A cada amigo candidato se le asigna un peso segun el nivel o categoria de amigos en comun: 
<=10   1.0 , 11-20  2.5,  >20  3.5.
2 Se construye una suma acumulada del valor de la prioridad o (pesos) (pesoAcumulado[i] = pesoAcumulado[i-1] + peso[i]).
3 Se  genera un numero aletorio entre 0 y la suma total de pesos (rand())
4 Se recorre el arreglo acumulado hasta encontrar el primer valor que supere el numero generado ese es el candidato elegido.
5 Se repite 3 veces evitando repetir el mismo amigo si ya fue elegido, salvo que no haya suficientes amigos.

Restriccion: la opcion de actualizar el set de 3 fotos por otro grupo distinto solo puede usarse una unica vez por sesion de login  no es una actualizacion ilimitada. esto implica un contador de control por ejemplo bool fotosYaActualizadas en RedSocial o en la sesion del usuario que se resetea en cada nuevo login.

*ALGORITMO MATRIZ DE ADYACENCIA (sugerencias de amigos)(2)

Se usa: Para calcular hasta K sugerencias de amistad (K entre 1 y 20), rankeadas por numero de amigos en comun entre dos usuarios en tiempo constante por consulta: Comparar las filas correspondientes a ambos usuarios y contar coincidencias.
Uso unsigned char* (no bool) para la matriz, empaquetada a nivel de bit para optimizar memoria
(misma tecnica del Desafio I, 1 bit por relacion de amistad en vez de un byte completo). Esto porque quiero reforzar el criterio de eficiencia en la seleccion de estructuras que vale el 25% de la nota.
Para el usuario 'U', se recorre su fila en la matriz, se descartan los que ya son amigos o es el mismo, y para cada candidato se cuentan las coincidencias con la fila de 'U' amigos en comun usando operadores btwise AND si la matriz se empaqueta por bits.
Se ordenan los candidatos por cantidad de amigos en comun de mayor a menor y se devuelven los primeros K.
Por que no lista de amigos por usuario sin matriz? porque calucular amigos en comun comparando dos listas enlazadas requiere recorrer ambas por cada par de usuario candidato mas costoso cuando hay muchos usuarios. La matriz convierte la comparacion en una operacion directa fila contra fila.

*ALGORITMO INSERCION ORDENADA (3)

Donde se usa: despues de calcular amigos en comun, algoritmo(2) antes de devolver el top-k (ordenamiento de candidatos por amigos en comun).

El algoritmo de insercion se usa al insertar cada candidato en una lista ya ordenada por cantidad de amigos en comun, en vez de ordenar todo al final, es consistente con el metodo insertarOrdenado() que ya fue puesto en ListaEnlazada<T> en el diagrama de clases aqui se reutiliza la misma estructura/metodo en vez de escribir un sort(algoritmo que reordena los elementos de un arreglo) aparte. porque K es mas pequeño de maximo 20 y los candidatos no son miles la insercion ordenada es defendible y evita implementar un algoritmo de ordenamiento generico aparte solo para esto.

*ALGORITMO BUSQUEDA LINEAL CON CORTE TEMPRANO (sobre lista ya ordenada)(4)

Busqueda de mensajes por rango de fechas.
Este se usa al buscar mensajes de usuario dentro de un rango de al menos 6 semanas. 
Si los mensajes de un usuario se mantienen en una lista enlazada ordenada por fecha de envio insertando siempre con insertarOrdenado(), reutilizando a fecha::esMenorQue(), la busqueda por rango se reduce a.
-Recorrer la lista desde el inicio hasta encontrar el primer mensaje cuya fecha >= fecha inicial del rango.
-Continuar recorriendo y acumulando mensajes mientras la fecha sea  < =  fecha final del rango.
-Detenerce apenas se pase la fecha final.
Por que no busqueda binaria? porque una lista enlazada no tiene acceso indexado, asi que la busqueda binaria clasica no aplica direactamente sin convertirla primero en arreglo.

*ALGORITMO BUSQUEDA LINEAL(5)

BUSQUEDA DE USUARIO POR NOMBRE

-Busqueda lineal: para encontrar al usuario que se esta logueando, como uso este algoritmo y por que?: Aqui el usuario ingresa su nombre, pero el programa necesita validar si el usuario si existe en la base de datos, lo que el programa hace es que recorre la lista de usuarios ya cargada en memoria, en este punto yo imagino la lista como una fila de personas con gafas y en sus gafas llevan el nombre, entonces me voy recorriendo la fila persona por persona deteniendome a mirar su nombre lo verifico si no es continuo con esta misma accion en el caso de que recorra toda la fila y no vea ninguna persona con ese nombre simplemente digo que esa persona no se encuentra en la fila esto mismo lo aplico en el programa si una persona intenta loguerse la lista recorre buscando el nombre ingresado y si ese nombre no aparece simplemente imprime usuario no encontrado o usurio no registrado. -Algoritmo de busqueda lineal. Donde se usa: buscarUsuario(string nombre) en RedSocial.

Algoritmo: recorrido lineal sobre la lista enlazada de usuarios, comparando cada nombreUsuario con el buscado. Con string la comparacion se simplifica a usar el operador == directamente (string lo sobrecarga internamente), en vez de tener que escribir una comparacion manual caracter por caracter como hubiera sido necesario con char*. El algoritmo de recorrido en si (lineal sin estructura de busqueda indexada) no cambia solo el paso de comparacion dentro de cada iteracion.

REUTILIZACION DE DOS PIEZAS YA DEFINIDAS Y APLICADAS EN ESTE ARCHIVO: (algoritmos4 y 7)

Aqui se hace referencia a la diferencia entre busqueda lineal algoritmo(5), en busqueda lineal algoritmo(5) se recorre toda la fila, de principio a fin, sin exepcion, hasta encontrar a la persona o hasta llegar al final sin encontrarla, no hay ninguna condicion para detenerse antes. En busqueda lineal con corte temprano mencionado en el algoritmo 4 es el mismo recorrido uno por uno, pero la lista esta ordenada por fecha, entonces en cuanto se encuentra un mensaje cuya fecha ya se paso del rango que busca, puede parar ahi mismo no tiene sentido seguir revisando  los que vienen despues porque ya se sabe que tampoco van a estar en el rango.

-Busqueda de mensajes por rango de fechas (ahi se usa una variante: busqueda lineal con corte temprano (algoritmo 4)).
-Carga y actualizacion de datos (para resolver las referencias cruzadas por nombre (algoritmo7))

*ALGORITMO INSTRUMENTACION POR CONTADOR + (calculo manual con ziseof) (6)

CONTEO DE ITERACIONES Y MEMORIA POR OPERACION:
Donde se usa: En el requisito obligatorio en el enunciado de la seccion VII
al finalizar la ejecucion de cada funcionalidad, mostrar en pantalla 2 metricas.
Medicion del consumo  de recursos: 
A). La cantidad de iteraciones requeridas directa e indirectamente, para completar esa funcionalidad especifica. Si en algun caso se invoca un componente externo, debe reportarse su uso.
B). El total de memoria que se esta consumiendo en ese momento exacto de la ejecucion, por causa de todas las estruturas de datos y objetos existentes en el sistema. incluya en este valor las variables locales y parametros por valor involucrados en la funcionalidad.
No es un algoritmo de computo si no de instrumentacion:
1. Iteraciones directas e indirectas:  Cada funcion que haga un recorrido ciclo for/while lleva un contador int iteraciones = 0; incrementando en cada vuelta. Indirectas significa que si la funcionalidad llama a otra funcion que tambien itera ejem. Enviar solicitud() llama a buscarUsuario(), que tiene su propio ciclo de busqueda lineal, esas iteraciones tambien se suman al total reportado no solo las del ciclo principal de la funcionalidad.
2. Componentes externos: Si se invoca algo externo a este codigo ejem. rand(), su uso debe reportarse aparte auque no sea un ciclo propio que podamos contar en iteraciones.
3. Memoria (alcance total del sistema, no solo involucrado). el reporte de memoria no es solo de las estructuras que usa esa funcionalidad es la memoria de todo lo que existe en el sistema en ese instante todos los usuarios cargados, con todas sus listas de amigos/mensajes/albumes/fotos/solicitudes, mas la matriz de adyacencia, sumando a las variables locales y parametros por valor de la funcionalidad actual. Esto se resuelve con un metodo memoriaUsada() en RedSocial que recorre y suma la memoria de todas las estructuras, reutilizando el memoriaUsada() propio de cada una de las clases que RedSocial contiene por composicion/asociacion, usuario, album, foto, mensaje, solicitudAmistad, ListaEnlazada<T>.

NOTA IMPORTANTE: Con string: sizeof(string) No devuelve el tamaño real del texto que contiene devuelve el tamaño del objeto contenedor un valor fijo, que es solo el puntero interno, el tamaño y la capacidad. Para textos largos que string guarda en el heap, no dentro del propio objeto, ese sizeof no refleja la memoria real usada. Para un reporte de consumo preciso, hay que sumar sizeof(string) mas .capacity() de cada string de lo contrario el reporte de memoria subestima el uso real cada vez que un atributo de texto sea largo.

*ALGORITMO TOKENIZACION POR DELIMITACION (LECTURA) (7)

CARGA Y ACTUALIZACION DE DATOS (almacenamiento permanente)

-Tokenizacion por delimitacion (lectura) + (insercion ordenada/final + busqueda lineal + recorrido lineal): La funcion de este algoritmo esta concretamente ligada con los archivos, usuarios.txt, amigos.txt, solicitudes.txt, mensajes.txt, albumes.txt, fotos.txt. Donde se usa: En la funcionalidad obligatoria del primer enunciado leer y actualizar usuarios, amigos, solicitudes, mensajes, albumes y fotos desde hacia los archivos de texto antes mencionados. No aparece en el menu visible al usuario, la funcion de este algoritmo es que va leyendo caracter por caracter hasta encontrar un tabulador ('\t') en ese momento el programa se detiene, esto es  similar en la vida real como cuando estamos leyendo una lista ejemplo de mercado y leemos una palabra, encontramos una coma y paramos, esa es la funcion de tabulador entonces encuentra un tabulador y se detiene guarda la informacion y continua con la siguiente leyendo hasta encontrar de nuevo tabulador ('\t') este proceso se repite hasta leer toda la informacion del usuario como direccion, correo, ciudad etc. NOTA de esta misma forma funciona o se aplica a los 6 archivos del sistema mencionados al inicio, cambiando unicamente la cantidad y el tipo de campos de cada linea.

REUTILIZACION DE CUATRO PIEZAS YA DEFINIDAS Y  APLICADAS EN ESTE ARCHIVO: (algoritmos 4 y5).

 -Tokenizacion por delimitador(lectura): cada linea se separa en sus campos con, getline(archivo, campo,  '\t' ) repetido una vez por campo esto porque el numero de campos por tipo de registro es fijo y conocido.
 
-Reconstruccion en memoria via insertarFinal()/ insertarOrdenado: cada linea se convierte en un objeto y se agrega a su listaEnlazada<T> con los mismos metodos ya definidos en el diseño mensajes.txt usa insertarOrdenado() por fecha, para que la lista quede lista de una vez para la busqueda por rango -mencionada en el algoritmo 4.

-Resolucion de referencias cruzadas via buscarUsuario(): los archivos no guardan punteros, guardan nombreUsuario como texto cada referencia se resuelve reutilizando la busqueda lineal 
mencionada en el algoritmo 5, para obtener el usuario* real antes de contruir el objeto.

-Recorrido lineal para escritura: guardarDatos() recorre cada listaEnlazada<T>  con el patron de recorrido estandar y escribe cada objeto con una linea de campos separados por tabulador ('\t').

*ALGORITMO ELIMINACION EN LA LISTA ENLAZADA (8)

Donde se usa: en la funcionalidad B) aceptar solicitudes de amistad recibidas, al aceptar una solicitud de amistad, se elimina de solicitudesRecibidas para que deje de aparecer como pendiente, ya que la amistad ya quedo registrada en las listas amigos de ambos usuarios.

Este algoritmo recorre ListaEnlazada<solicitudAmistad*> buscando el nodo cuyo dato coincide con la solicitud que se esta aceptando, al encontrarlo, se reconecta el puntero del nodo anterior directamente al nodo siguiente (saltando el nodo eliminado), y se libera la memoria del nodo quitado. Es el metodo eliminar(T dato) que esta definido en listaEnlazada<T> en el diagrama de clases.

*ALGORITMO RECORRIDO LINEAL(Recorrido completo con filtro)(9)

Donde se usa: Se usa la primera vez en III.b en listar solicitudes de amistad pendientes de un usario, reutilizado en IV filtrar albumes de un amigo por 'A'/'P' y en VI.b para listar los mensajes recibidos no leidos, ordenados por fecha.

En este algoritmo se recorre la ListaEnlazada<T> completa de principio a fin, sin detenerse antes de llegar al final, evaluando una condicion en cada elemento (estado == 'P',  privacidad != 'V', leido == false, etc) y acumulando/mostrando todos los que la cumplen a diferencia de busqueda lineal, que busca un solo elemento especifico y se detiene en cuanto lo encuentra.
Por que no busqueda lineal (5) ni busqueda con corte temprano(4), en estos tres casos puede haber varios elementos que cumplan la condicion, repartidos en cualquier posicion de la lista no agrupados ni en un rango continuo, asi que no hay ningun punto seguro para detenerse antes de terminar de recorrer toda la lista.

 ## d. Tipos de datos y justificación

Dato: Nombre de usuario, correo, ciudad, pais, ruta de foto, texto de mensaje. Tipo elegido(string)
Por que? al ser confirmado por el profesor el uso, lo usare ya que simplifica el manejo de memoria sin New/delete manuales estas seran cedidas a ListasEnlazadas<T>/ Nodo<T>.

Dato: Dia, mes, año (fecha): Tipo elegido (int). por que? rango pequeño, no necesita short ni tipos mas grandes, int seria el estandar para estos campos.

Dato: Tamaño de foto (foto::tamanio): Tipo (int). Por que? suficiente para representar tamaños de archivo sin necesitar long.

Dato:Privacidad de album, estado de solicitud de amistad: Tipo (char)(un solo caracter como codigo: 'P'/'V'/'A' para publico/privado/amigos; 'P'/'A'/'R' para pendiente/aceptada/rechazada/). Por que? Evita usar enum class no es clase pero evita mantener consistencia con "sin STL", un char es la forma mas economica de codificar un estado fijo de pocas opciones.

Dato: Matriz de adyasencia de amistades: Tipo (unsingned char*) igual que en el desafioI, permite empaquetar 1 bit por relacion si se decide optimizar memoria el tipo correcto para manipulacion bit a bit.

Dato: Contador de iteraciones: Tipo(int). Por que? es estandar para contadores de ciclo.

Dato: Memoria consumida(sizeof acumulado): Tipo (size_t) no int. Por que? sizeof devuelve size_t de forma nativa en Ctt usar int para acumularlo seria forzar una conversion innecesaria en teoria podria no representar valores muy grandes en estructuras masivas.

Dato: Peso en el muestreo ponderado (1.0, 2.5, 3.5): Tipo (double). Por que? porque los pesos tienen decimales explicitos en el enunciado(2.5x, 3.5x) float perderia precision muy rapido y int no serviria.

Dato: Punteros entre nodos de la lista enlazada(cabeza,cola,siguiente):Tipo (Nodo<T>*). POr que? puntero simple porque cada nodo apuntaal siguiente, sin necesidad de reasignar el nodo mismo desde afuera.

Dato: Parametro de listaEnlazada cuando se necesita modificar la lista completa ejem al hacer push_front que cambia la cabeza desde una funcion externa, si llegara a necesitar. Tipo: (Nodo<T>**) o referencia por metodo de la propia clase. POr que? porque en este diseño, como insertarFinal/insertarOrdenado son metodos de la propia clase no funciones externas, no necesitamos doublepuntero aqui la clase modifica su propio atributo, cabeza directamente. El double puntero solo seria necesario si una funcion externa a la clase necesitara reasignar el nodo cabeza, como pasaba con el tablero en el desafioI.

NOTA IMPORTANTE:
En el desafio I, doble puntero unsigned char** era necesario porque las funciones de redimension eran funciones libres no metodos de una clase que necesitanban reasignar una variable que vivia en el main(). En este desafio como si tenemos clases, ListaEnlazada<T> puede modificar su propia cabeza/cola directamente desde sus propios metodos por eso casi no necesitamos doble puntero aqui.
 Desicion confirmada:  char* vs std::string
 Voy a usar std::string tecnicamente std::string no hace parte de la STL en sentido estricto (STL = a contenedores + iteraddores + algoritmos + fuction objets) es una clase aparte de la biblioteca estandar Ctt.


## e. Decisiones de diseño relevantes (referencia a ADR)

ADR-001 -Modelado de la relacion de amistad. Decido no crear una clase "Amistad" independiente, porque la amistad es una relacion mutua entre dos usuarios y el enunciado no le asigna atributos propios. Aqui cada objeto usuario mantiene  una lista de punteros a sus amigos que al aceptarla solicitud actualiza la lista de ambos usuarios para conservar la simetria de la relacion. Pero en cambio si creo la clase solicitudAmistad porque representa una operacion con estado propio, pendiente, aceptada o rechazada permite identificar al remitente y al destinatario. — [Abrir ADR-001](../ADR/ADR-001-modelado-de-amistad.md.md)

ADR-002 -Lista enlazada generica. Decido implementar ListaEnlazada<T> mediante templates y una clase Nodo<T>, con el fin de reutilizar una estructura dinamica propia para administrar usuarios, amigos,mensajes, albumes y fotografias sin recurrir a los contenedores de la  STL. Elijo una lista doblemente enlazada no circular como estructura general, ya que permite avanzar y retroceder entre sus elementos. Para el carrucel de fotografias, utilizare un indice que permita recorrer las fotos de forma circular mediante el operador modulo, sin necesidad de convertir fisicamente la lista circular. Los nodos alamacenaran los datos definidos por el tipo T que podra ser un puntero cuando corresponda, para evitar copias innecesarias de los objetos. — [Abrir ADR-002](../ADR/ADR-002-lista-enlazada-generica.md.md)

ADR-003 -Generador de numeros aleatorios. Decido utilizar rand() y srand() de la bibioteca estandar de Ctt para las operaciones que requieren aleatoriedad, especialmente la seleccion ponderada de fotografias de perfil al iniciar sesion. A diferencia del desafio 1, en este proyecto el enunciado permite utilizar una biblioteca para generar numeros aleatorios y el objetivo principal esta en la programcion orientada a objetos y la eficiencia de las estructuras de datos. — [Abrir ADR-003](../ADR/ADR-003-generador-aleatorio.md.md)

ADR-004 -Tipo de dato para los atributos de texto. Decido utilizar std::string para los atributos textuales de las clases de dominio, como nombres de usuario, correos, rutas y mensajes, despues de consultar con el profesor, quien confirmo que si esta permitido el uso. Esta alternativa simplifica las asignaciones y comparaciones de cadenas, y evita la gestion manualmente de memoria de cada texto char*, new y delete. La implementacion propia de estructuras dianamicas, seguira siendo responsabilidad de ListaEnalazada<T> y nodo<T>, tambien  para tener en cuenta que sizeof(std::string) no representa por si solo toda la memoria utilizada por el texto. — [Abrir ADR-004](../ADR/ADR-004-tipo-dato-texto.md.md)
## f. Problemas enfrentados hasta ahora

1. Restriccion de la STL, ligera confucion de que no se debia usar (string), el enunciado era ambiguo sobre si era permitido o no, aclarado por el profesor Augusto que si es permitido.
2. Datos distintos en el documento que se habia descargado inicialmente y el que se encontraba en la plataforma, rangos de peso >20 frente a >21 y la restriccion de actualizar las 3 fotos una sola vez no coincidian. Se resolvio tomando el texto original de la plataforma como fuente.
3. REpeticion de amigos en el muestreo ponderado: un amigo con mucho peso podia salir en varias de las 3 fotos. Se resolvio retirando al elegido de los candidatos y recalculando el total antes de cada sorteo.
4. Sugerencias de amistad: Se tiene que descartar al propio usuario (diagonal de la matriz) y a quienes ya son amigos. La insercion ordenada con tope K evito ordenar todo al final.
5. Medicion de los recursos:el alcance de la memoria es todo el sistema, no solo la funcionalidad. sizeof(string) no refleja el texto real, asi que debo usar sizeof + capacity(),y las variables locales se suman a mano en cada funcion.
6. Algoritmos: cuando pense que ya habia definido todos los algoritmos que necesitaba note que me faltaba 2 mas los cuales nombre, recorrido lineal e insercion simple.
7. Herencia o composicion: Ya que se aclara que no se usa herencia entonces las relaciones se resuelven con composicion y asociacion



