#include "fecha.h"

Fecha::Fecha() : dia(1), mes(1), anio(ANIO_MIN) {}

Fecha::Fecha(int d, int m, int a) : dia(1), mes(1), anio(ANIO_MIN) {
    setFecha(d, m, a);
}

bool Fecha::esBisiesto(int a) {
    return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
}


int Fecha::diasDelMes(int m, int a) {
    if (m == 2) return esBisiesto(a) ? 29 : 28;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

bool Fecha::esValida(int d, int m, int a) {
    if (a < ANIO_MIN || a > ANIO_MAX) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > diasDelMes(m, a)) return false;
    return true;
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

bool Fecha::setFecha(int d, int m, int a) {
    if (!esValida(d, m, a)) return false;
    dia = d; mes = m; anio = a;
    return true;
}

// esta Fecha es menor que otra = ocurrio antes se compara de lo mas significativo (año)a
// lo mas significativo (dia)

bool Fecha::operator<(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;

}

std::string Fecha::aTexto() const {
    std::string d = (dia < 10 ? "0": "") + std::to_string(dia);
    std::string m = (mes < 10 ? "0": "") + std::to_string(mes);
    return d + "/" + m + "/" + std::to_string(anio);

}

size_t Fecha::memoriaUsada() const {
    return sizeof(Fecha);
}
