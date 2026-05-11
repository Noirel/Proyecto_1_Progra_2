//
// Created by fabri on 10-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_PRIORIZADOREQUIPOS_H
#define PROYECTO_1_PROGRA_2_PRIORIZADOREQUIPOS_H

#include <vector>
#include <iostream>
#include "Equipo.h"

using namespace std;

class PriorizadorEquipos {

    struct EquipoPriorizado {
        EquipoLaboratorio*  equipo;
        double   prioridad;
    };

    vector<EquipoPriorizado> _equiposPriorizados;

public:

    PriorizadorEquipos() : _equiposPriorizados() {}

    ~PriorizadorEquipos() {
        _equiposPriorizados.clear();
    }

    double calcularPrioridad(EquipoLaboratorio* equipo) const {
        if (!equipo) return 0.0;

        int criticidad            = equipo->getCriticidad();
        int incidenciasActivas    = equipo->getCantIncidencias();
        int tiempoInactivo        = equipo->getDiasInactivo();

        double prioridad = (criticidad * 0.5) + (incidenciasActivas * 0.3) + (tiempoInactivo * 0.2);

        return prioridad;
    }

    void combinar(int izquierda, int medio, int derecha) {
        vector<EquipoPriorizado> izq, der;

        for (int i = izquierda; i <= medio; i++)
            izq.push_back(_equiposPriorizados[i]);

        for (int i = medio + 1; i <= derecha; i++)
            der.push_back(_equiposPriorizados[i]);

        int i = 0, j = 0, k = izquierda;

        while (i < izq.size() && j < der.size()) {
            if (izq[i].prioridad >= der[j].prioridad) {
                _equiposPriorizados[k++] = izq[i++];
            } else {
                _equiposPriorizados[k++] = der[j++];
            }
        }

        while (i < izq.size())
            _equiposPriorizados[k++] = izq[i++];

        while (j < der.size())
            _equiposPriorizados[k++] = der[j++];
    }

    void ordenarYCombinar(int izquierda, int derecha) {
        if (izquierda < derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;
            ordenarYCombinar(izquierda, medio);
            ordenarYCombinar(medio + 1, derecha);
            combinar(izquierda, medio, derecha);
        }
    }

    int busquedaBinaria(double prioridad) const {
        int izquierda = 0, derecha = _equiposPriorizados.size() - 1;
        int resultado = 0;

        while (izquierda <= derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;

            if (_equiposPriorizados[medio].prioridad >= prioridad) {
                resultado = medio;
                izquierda = medio + 1;
            } else {
                derecha = medio - 1;
            }
        }

        return resultado;
    }

    void calcularYOrdenar(vector<EquipoLaboratorio*>& equipos) {
        _equiposPriorizados.clear();

        if (equipos.empty()) {
            cout << "[PriorizadorEquipos] Advertencia: lista de equipos vacia" << endl;
            return;
        }

        // Paso 1: Calcular prioridad de cada equipo
        for (EquipoLaboratorio* eq : equipos) {
            if (eq != nullptr) {
                EquipoPriorizado ep;
                ep.equipo    = eq;
                ep.prioridad = calcularPrioridad(eq);
                _equiposPriorizados.push_back(ep);
            }
        }

        // Paso 2: Ordenar usando MergeSort (ordenarYCombinar)
        if (_equiposPriorizados.size() > 1) {
            ordenarYCombinar(0, _equiposPriorizados.size() - 1);
        }
    }

    vector<EquipoLaboratorio*> obtenerTopN(int n) const {
        vector<EquipoLaboratorio*> resultado;

        int limite = (n < (int)_equiposPriorizados.size()) ? n : (int)_equiposPriorizados.size();

        for (int i = 0; i < limite; i++) {
            resultado.push_back(_equiposPriorizados[i].equipo);
        }

        return resultado;
    }

    EquipoLaboratorio* obtenerMayorPrioridad() const {
        if (_equiposPriorizados.empty())
            return nullptr;
        return _equiposPriorizados[0].equipo;
    }

    double obtenerPrioridad(int indice) const {
        if (indice < 0 || indice >= (int)_equiposPriorizados.size())
            return 0.0;
        return _equiposPriorizados[indice].prioridad;
    }

    int cantidad() const {
        return _equiposPriorizados.size();
    }

    void imprimirReporte() const {
        cout << "\n========================================" << endl;
        cout << "  REPORTE DE PRIORIZACION COMPLETO" << endl;
        cout << "========================================" << endl;

        if (_equiposPriorizados.empty()) {
            cout << "[PriorizadorEquipos] No hay equipos priorizados." << endl;
            return;
        }

        cout << "Rango | ID Equipo | Prioridad" << endl;
        cout << "----------------------------------------" << endl;

        for (int i = 0; i < (int)_equiposPriorizados.size(); i++) {
            cout << (i + 1) << " | "
                 << _equiposPriorizados[i].equipo->getId() << " | "
                 << _equiposPriorizados[i].prioridad
                 << endl;
        }

        cout << "========================================" << endl;
    }

    void imprimirTopPriorizados(int n, int dia) const {
        cout << "Dia " << dia << endl;
        cout << "Top prioridad: ";

        int limite = (n < (int)_equiposPriorizados.size()) ? n : (int)_equiposPriorizados.size();

        for (int i = 0; i < limite; i++) {
            if (i > 0) cout << ", ";
            cout << _equiposPriorizados[i].equipo->getId()
                 << " (" << _equiposPriorizados[i].prioridad << ")";
        }

        cout << endl;
    }

};


#endif //PROYECTO_1_PROGRA_2_PRIORIZADOREQUIPOS_H