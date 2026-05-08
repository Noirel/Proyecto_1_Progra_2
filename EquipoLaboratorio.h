//
// Created by fabri on 07-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_EQUIPOLABORATORIO_H
#define PROYECTO_1_PROGRA_2_EQUIPOLABORATORIO_H


#include "Equipo.h"
#include <random>

class EquipoLaboratorio : public Equipo {
private:
    string *laboratorio;
    double *tasaDegradacion;
    mt19937 gen;
    uniform_real_distribution<double> distribucion;
public:

    EquipoLaboratorio(string id, int criticidad, double estado, int tiempoInactivo,
                      string laboratorio, double min = 0.0, double max = 2.0)
        : Equipo(id, criticidad, estado, tiempoInactivo),
          laboratorio(new string(laboratorio)),
          tasaDegradacion(new double(0.0)),
          gen(random_device{}()),
          distribucion(min, max) {}

    virtual ~EquipoLaboratorio() {
        delete laboratorio;
        delete tasaDegradacion;
    }

    void aplicarDegradacion() override {
        *tasaDegradacion += distribucion(gen);
    }

    void realizarMantenimiento() override {
        *criticidad = 0;
        *tiempoInactivo = 0; // Mover a Equipo.h
        // cambiar depéndiendo de como se haga

    }

};


#endif //PROYECTO_1_PROGRA_2_EQUIPOLABORATORIO_H