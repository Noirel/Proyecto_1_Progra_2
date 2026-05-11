//
// Created by fabri on 07-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_MANTENIMIENTOCORRECTIVO_H
#define PROYECTO_1_PROGRA_2_MANTENIMIENTOCORRECTIVO_H
#include "MantenimientoPreventivo.h"



class MantenimientoCorrectivo : public MantenimientoPreventivo {
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
        //TERMINAR, usa criticidad y tiempoinactivo
    }

    string getTipoMantenimiento() override{
        return "Mantenimiento Correctivo";
    }

};


#endif //PROYECTO_1_PROGRA_2_MANTENIMIENTOCORRECTIVO_H