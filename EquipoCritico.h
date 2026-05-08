//
// Created by fabri on 07-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_EQUIPOCRITICO_H
#define PROYECTO_1_PROGRA_2_EQUIPOCRITICO_H

#include "Equipo.h"

class EquipoCritico : public Equipo {
    private:
    string *critico;
    double *factorRiesgo;
    bool *requiereEspecialista;
    mt19937 gen;
    uniform_real_distribution<double> distribucion;

public:

    EquipoLaboratorio(double factorRiesgo, bool requiereEspecialista, double min = 0.0, double max = 2.0)
        : Equipo(id, criticidad, estado, tiempoInactivo),
          laboratorio(new string(critico)),
          tasaDegradacion(new double(0.0)),
          gen(random_device{}()),
          distribucion(min, max) {}

    virtual ~EquipoCritico() {
        delete critico;
        delete factorRiesgo;
        delete requiereEspecialista;
    }

};


#endif //PROYECTO_1_PROGRA_2_EQUIPOCRITICO_H