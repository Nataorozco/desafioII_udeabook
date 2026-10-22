#include "mensaje.h"

const std::string& Mensaje::getTexto() const {return texto; }
const Fecha& Mensaje::getFechaEnvio() const {return fechaEnvio; }
bool Mensaje::estaLeido() const {return leido; }
Usuario* Mensaje::getEmisor() const {return emisor; }
Usuario* Mensaje::getReceptor() const {return receptor; }

//aqui llamado de constructor completo sobrecargado
Mensaje::Mensaje(const std::string& texto, const Fecha& fechaEnvio,
Usuario* emisor, Usuario* receptor, bool leido)
    : texto(""), fechaEnvio(), leido(false), emisor(nullptr), receptor(nullptr)
{
    // 1) limpiar 2)validar (en este orden)
    std::string limpio = limpiarTexto(texto);
    if(textoEsValido(limpio)) {
        this->texto = limpio;
        this->fechaEnvio = fechaEnvio;
        this->leido = leido;
        this->emisor = emisor;
        this->receptor = receptor;
    }
    // si no es seguro queda el estado seguro de arriba
}

//mensaje corto, aqui llamado de constructor sobrecargado
Mensaje::Mensaje(const std::string& texto, const Fecha& fechaEnvio,
Usuario* emisor, Usuario* receptor)
    : Mensaje(texto, fechaEnvio, emisor, receptor, false)
{

}

std::string Mensaje::limpiarTexto(const std::string& texto)
{
    std::string resultado = texto;
    for (unsigned int i = 0; i < resultado.size(); i++) {
        char c = resultado[i];
        if (c == '\t' || c == '\n' || c == '\r') {
            resultado[i] = ' ';
        }
    }
    return resultado;
}

bool Mensaje::textoEsValido(const std::string& texto)
{
    if (texto.size() < LONGITUD_MIN || texto.size() > LONGITUD_MAX) {
        return false;
    }
    // Debe haber al menos un caracter que no sea en blanco
    for (unsigned int i = 0; i < texto.size(); i++) {
        char c = texto[i];
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            return true;
        }
    }
    return false;
}
