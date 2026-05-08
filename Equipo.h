//
// Created by fabri on 07-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_EQUIPO_H
#define PROYECTO_1_PROGRA_2_EQUIPO_H


#include <iostream>
#include <vector>
using namespace std;
class Incidencia;

class Equipo {
protected:
    string *id;
    int *criticidad;
    double *estado;
    int *tiempoInactivo;
    vector<Incidencia*> incidencias;
    int cantIncidencias;
public:
    Equipo(string id, int criticidad, double estado, int tiempoInactivo)
        : id(new string(id)),
          criticidad(new int(criticidad)),
          estado(new double(estado)),
          tiempoInactivo(new int(tiempoInactivo)) {}

    virtual ~Equipo() {
        delete id;
        delete criticidad;
        delete estado;
        delete tiempoInactivo;
    }

    virtual double calcularPrioridad();
    virtual void aplicarDegradacion()=0;
    virtual void realizarMantenimiento()=0;


    string getId() {
        return *id;
    }

    int getCriticidad() {
        return *criticidad;
    }

    int getIncidencias() {
        return cantIncidencias;
    }
};

#endif //PROYECTO_1_PROGRA_2_EQUIPO_H