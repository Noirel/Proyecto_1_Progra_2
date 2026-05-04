#include <iostream>
using namespace std;
#include <iostream>
#include "Incidencia.h"
using namespace std;

int main() {
    enum NivelSeveridad {
        No_Tiene = 0,
        Baja = 1,
        Media = 5,
        Alta = 9
    };
    Incidencia incidencia("1234",1, 0);
    cout<<incidencia.getSeveridad();
    incidencia.setSeveridad(No_Tiene);
    cout<<incidencia.getSeveridad();
    return 0;
}