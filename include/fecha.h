#ifndef FECHA_H
#define FECHA_H
#include <string>
#include <cstddef>

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    // Limites del año aceptado(constantes de la clase)
    static const int ANIO_MIN = 1900;
    static const int ANIO_MAX = 2100;
    // constructores
    Fecha(); // 1/1/1900 (valor seguro por defecto)
    Fecha(int d, int m, int a); // si la fecha es invalida, queda en el valor por defecto

    // validacion (stactic: no necesita un objeto, se usa tambien al cargar archivos)
    static bool esValida(int d, int m, int a);
    static bool esBisiesto(int a);
    static int diasDelMes(int m, int a);

    // getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // setter: cambia las tres partes juntas o no cambia nada
    bool setFecha(int d, int m, int a);

    // OPerador sobrecargado: permite escribir fecha(f1) < fecha ( f2)
    bool operator<(const Fecha& otra) const;

    //Salida dd/mm/aaaa
    std::string aTexto() const;

    // Instrumentcion del requisito VII
    size_t memoriaUsada() const;


};

#endif
