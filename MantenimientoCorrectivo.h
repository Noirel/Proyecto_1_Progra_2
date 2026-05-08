//
// Created by fabri on 07-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_MANTENIMIENTOCORRECTIVO_H
#define PROYECTO_1_PROGRA_2_MANTENIMIENTOCORRECTIVO_H
#include "IEstrategiaMantenimiento.h"
#include "Equipo.h"


class MantenimientoCorrectivo : public IEstrategiaMantenimiento {
private:
    bool resuelveIncidencias = true;
    int incidenciasCrticiasResueltas;
public:
    void ejectutarCorrectivo(Equipo* equipo) override {
        if (equipo = nullptr)
        throw OperacionException();


        for (auto* inc : equipo->getIncidencias()) {
            if (!inc->estaResuelta()) {
                inc->resolver();
                incidenciasCrticiasResueltas++;
            }
        }
        //TERMINAR
    }

    string getTipoMantenimiento() override{
        return "Mantenimiento Correctivo";
    }

};


#endif //PROYECTO_1_PROGRA_2_MANTENIMIENTOCORRECTIVO_H