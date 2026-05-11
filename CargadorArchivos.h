//
// Created by fabri on 09-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_CARGADORARCHIVOS_H
#define PROYECTO_1_PROGRA_2_CARGADORARCHIVOS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "EquipoLaboratorio.h"
#include "Incidencia.h"
#include "ArchivoException.h"
#include "OperacionException.h"
using namespace std;


class CargadorArchivos {
private:
    string rutaArchivo;
public:
    CargadorArchivos(const string &ruta) : rutaArchivo(ruta) {}

    vector<EquipoLaboratorio*> CargarEquipos() {
        ifstream archivo(rutaArchivo);
        if (!archivo.is_open())
            throw ArchivoException("No se pudo abrir el archivo: " + rutaArchivo);
        vector<EquipoLaboratorio*> equipos;
        string linea;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            if (linea.find("EQ") != 0) continue;

        stringstream ss(linea);
        string id, campoCriticidad, campoEstado, campoCant, campoTiempo;

            getline(ss, id, ';');
            getline(ss, campoCriticidad, ';');
            getline(ss, campoEstado, ';');
            getline(ss, campoTiempo, ';');
            getline(ss, campoCant, ';');

            int    criticidad = stoi(campoCriticidad.substr(campoCriticidad.find('=') + 1));
            double estado = stod(campoEstado.substr(campoEstado.find('=') + 1));
            int    cantIncid = stoi(campoCant.substr(campoCant.find('=') + 1));
            int tiempoInactivo = stoi(campoTiempo.substr(campoTiempo.find('=') + 1));

        EquipoLaboratorio* eq = nullptr;
            eq = new EquipoLaboratorio(id, criticidad, estado, tiempoInactivo); // Cambiar EquipoLaboratorio Constructor
            eq->setCantIncidencias(cantIncid);

        equipos.push_back(eq);
        }
        return equipos;
    }
    void CargarIncidencias(const vector<EquipoLaboratorio*> &equipos) {
        ifstream archivo(rutaArchivo);
        if (!archivo.is_open())
            throw ArchivoException("No se pudo abrir el archivo: " + rutaArchivo);

        vector<Incidencia*> incidencias;
        string linea;

        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            if (linea.find("INC") != 0) continue;

            stringstream ss(linea);
            string cabecera, idEquipo, campoDia, campoResuelta;

            getline(ss, cabecera, ';');
            getline(ss, idEquipo, ';');
            getline(ss, campoDia, ';');
            getline(ss, campoResuelta, ';');

            int  dia = stoi(campoDia.substr(campoDia.find('=') + 1));
            bool resuelta = stoi(campoResuelta.substr(campoResuelta.find('=') + 1));

            EquipoLaboratorio* equipoDestino = nullptr;
            for (auto* eq : equipos) {
                if (eq->getId() == idEquipo) {
                    equipoDestino = eq;
                    break;
                }
            }
            if (equipoDestino == nullptr)
                throw OperacionException("Equipo: "+ idEquipo + " no encontrado para asignar incidencia");

            Incidencia* inc = new Incidencia(idEquipo, dia, resuelta);
            equipoDestino->agregarIncidencia(inc);

            }
    }

};


#endif //PROYECTO_1_PROGRA_2_CARGADORARCHIVOS_H