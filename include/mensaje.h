#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>
#include "fecha.h"

class Usuario; //solo se guardan punteros Nota la usare mas adelante

class Mensaje {
private:
    //cambia tabulador/t/ salto de linea en linux \n salto de linea en windows \r\n por un espacio
    static std::string limpiarTexto(const std::string& texto);

    std::string texto;
    Fecha fechaEnvio;
    bool leido;
    Usuario* emisor; // no es dueño: nunca se hace delete
    Usuario* receptor;// no es dueño: nunca se hace delete



public:// TODO: getters/setters, métodos, memoriaUsada()
    Mensaje();
    // limites del texto (constantes con nombre)
    static const unsigned int LONGITUD_MIN = 1;
    static const unsigned int LONGITUD_MAX =512;

    //constructor completo para cargar desde archivo) lo llamo completo porque el mismo
    //hace el trabajo de limpiar, validar y asignar.
    Mensaje(const std::string& texto, const Fecha& fechaEnvio,
            Usuario* emisor, Usuario* receptor, bool leido);

    //constructor corto (mensaje nuevo: leido= false) este lo llamo corto, por que
    // en vez de hacer el trabajo llama al completo en su lista de inicializacion.
    Mensaje(const std::string& texto, const Fecha& fechaEnvio,
            Usuario* emisor, Usuario* receptor);

    // solo responde true/false, no modifica nada
    static bool textoEsValido(const std::string& texto);

    // Getters
    const std::string& getTexto() const;
    const Fecha& getFechaEnvio() const;
    bool estaLeido() const;
    Usuario* getEmisor()const;
    Usuario* getReceptor()const;

};

#endif
