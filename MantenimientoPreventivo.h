//
// Created by fabri on 07-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_MANTENIMIENTOPREVENTIVO_H
#define PROYECTO_1_PROGRA_2_MANTENIMIENTOPREVENTIVO_H
#include "IEstrategiaMantenimiento.h"
#include <iostream>
using namespace std;


class MantenimientoPreventivo : public IEstrategiaMantenimiento {
private:
    double mejoraMinima = 0;
public:
    void ejecutar(EquipoLaboratorio* equipo) override {
        if (equipo == nullptr)
            throw OperacionException("Equipo nulo no se puede realizar mantenimiento");

        for (auto* inc : equipo->getIncidencias()) {
            if (inc->getResuelta() == false) {
                equipo->resolverIncidencias();
                equipo->limpiarIncidenciasResueltas();
                equipo->realizarMantenimiento();
            }
        }
    }
    string getTipoMantenimiento() override{
        return "Mantenimiento Preventivo";
    }

};


#endif //PROYECTO_1_PROGRA_2_MANTENIMIENTOPREVENTIVO_H