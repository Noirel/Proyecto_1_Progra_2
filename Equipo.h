//
// Created by fabri on 15-Abril-26.
//

#ifndef PROYECTO_1_PROGRA_2_EQUIPO_H
#define PROYECTO_1_PROGRA_2_EQUIPO_H


#include <iostream>
#include <vector>
#include "Incidencia.h"

using namespace std;

class Equipo {
protected:
    string *id;
    int *criticidad;
    double *estado;
    int *tiempoInactivo;
    vector<Incidencia*> incidencias;
    int cantIncidencias;
public:
        Equipo(string id, int criticidad, double estado, int tiempoInactivo) :
            id(new string(id)),
            criticidad(new int(criticidad)),
            estado(new double(estado)),
            tiempoInactivo(new int(tiempoInactivo)),
            cantIncidencias(0) {}
    virtual void aplicarDegradacion()=0;
    virtual void degradarEstado()=0;
    virtual void procesarDia()=0;
    virtual void agregarIncidencia(Incidencia* incidencia)=0;
    virtual void resolverIncidencias()=0;
    virtual void limpiarIncidenciasResueltas()=0;
    virtual void realizarMantenimiento()=0;
};

#endif //PROYECTO_1_PROGRA_2_EQUIPO_H