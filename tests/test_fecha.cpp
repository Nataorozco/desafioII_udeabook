#include <iostream>
#include "fecha.h"
using namespace std;
static int fallos = 0;
#define CHECK(c) do{ if(!(c)){ cout<<"FALLA: "#c<<endl; fallos++; } }while(0)
int main() {
    CHECK(Fecha::esValida(29,2,2024));   CHECK(!Fecha::esValida(29,2,2023));
    CHECK(!Fecha::esValida(29,2,1900));  CHECK(Fecha::esValida(29,2,2000));
    CHECK(!Fecha::esValida(31,4,2025));  CHECK(!Fecha::esValida(1,13,2025));
    CHECK(!Fecha::esValida(0,1,2025));
    CHECK(Fecha::esValida(1,1,2100)); CHECK(!Fecha::esValida(1,1,2101)); CHECK(!Fecha::esValida(1,1,1899));
    Fecha a(10,3,2025), b(5,4,2025), c(10,3,2025), mala(31,2,2025);
    CHECK(a < b); CHECK(!(b < a)); CHECK(!(a < c)); CHECK(!(c < a));
    CHECK(Fecha(31,12,2024) < Fecha(1,1,2025));
    CHECK(mala.aTexto() == "01/01/1900");
    CHECK(a.aTexto() == "10/03/2025");
    // rango inclusivo [ini, fin] usando solo operator<
    Fecha ini(1,3,2025), fin(10,3,2025);
    CHECK(!(a < ini) && !(fin < a));
    CHECK(sizeof(Fecha) == a.memoriaUsada());
    cout << (fallos ? "HAY FALLOS" : "Fecha OK") << endl;
    return fallos;
}
