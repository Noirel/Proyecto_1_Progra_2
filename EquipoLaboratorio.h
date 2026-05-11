//
// Created by fabri on 16-Abril-26.
//

#ifndef PROYECTO_1_PROGRA_2_EQUIPOLABORATORIO_H
#define PROYECTO_1_PROGRA_2_EQUIPOLABORATORIO_H


#include "Equipo.h"
#include <random>

class EquipoLaboratorio : public Equipo {
private:
    double *tasaDegradacion;
    mt19937 gen;
    uniform_real_distribution<double> distribucion;
    double min = 0.0;
    double max = 2.0;
public:

    EquipoLaboratorio(string id, int criticidad, double estado, int tiempoInactivo,
                      double min = 0.0, double max = 2.0): Equipo(id, criticidad, estado, tiempoInactivo),
          tasaDegradacion(new double(0.0)),
          gen(random_device{}()),
          distribucion(min, max) {}

    virtual ~EquipoLaboratorio() {
        delete tasaDegradacion;
        delete id;
        delete criticidad;
        delete estado;
        delete tiempoInactivo;
        for (auto* inc : incidencias)
            delete inc;
        incidencias.clear();
    }

    void setCantIncidencias(int cantIncidencias){
        this->cantIncidencias = cantIncidencias;
    }

    string getId() {
        return *id;
    }

    int getCriticidad() {
        return *criticidad;
    }

    vector<Incidencia*> getIncidencias() {
        return incidencias;
    }

    int getCantIncidencias() {
        return cantIncidencias;
    }

    double getEstado() {
        return *estado;
    }

    int getDiasInactivo() {
        return *tiempoInactivo;
    }

    void aplicarDegradacion() override {
        *tasaDegradacion += distribucion(gen);
    }

    void degradarEstado() override {
        double degradacionBase = *tasaDegradacion;
        double degradacionPorCriticidad = (*criticidad * 0.1);
        double degradacionPorInactividad = (*tiempoInactivo * 0.05);
        double degradacionPorIncidencias = (getCantIncidencias() * 0.15);

        double degradacionTotal = degradacionBase + degradacionPorCriticidad +
                                 degradacionPorInactividad + degradacionPorIncidencias;

        *estado -= degradacionTotal;


        if (*estado < 0.0) {
            *estado = 0.0;
        }

        *tiempoInactivo = *tiempoInactivo + 1;

        *tasaDegradacion = 0.0;
    }

    void procesarDia() override {
        aplicarDegradacion();
        degradarEstado();
    }

    void agregarIncidencia(Incidencia* incidencia) override {
        if (incidencia != nullptr) {
            incidencias.push_back(incidencia);
            cantIncidencias++;
        }
    }

    void resolverIncidencias() override {
        for (int i = 0; i < (int)incidencias.size(); i++) {
            if (incidencias[i] != nullptr) {
                incidencias[i]->setResuelta(true);
            }
        }
    }

    void limpiarIncidenciasResueltas() override{
        vector<Incidencia*> incidenciasActivas;

        for (int i = 0; i < (int)incidencias.size(); i++) {
            if (incidencias[i] != nullptr) {
                if (!incidencias[i]->getResuelta()) {
                    incidenciasActivas.push_back(incidencias[i]);
                }
            }
        }

        incidencias = incidenciasActivas;
        cantIncidencias = incidencias.size();
    }

    void realizarMantenimiento() override{

        *estado = 100.0;           // Estado perfecto
        *tiempoInactivo = 0;

        resolverIncidencias();
        limpiarIncidenciasResueltas();
        cantIncidencias = 0;
    }
};


#endif //PROYECTO_1_PROGRA_2_EQUIPOLABORATORIO_H