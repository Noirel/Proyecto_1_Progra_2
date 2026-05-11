//
// Created by fabri on 7-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_GENERADORARCHIVODATOS_H
#define PROYECTO_1_PROGRA_2_GENERADORARCHIVODATOS_H


#include <fstream>
#include <vector>
#include <string>
#include "EquipoLaboratorio.h"
#include "Incidencia.h"
#include "ArchivoException.h"
using namespace std;

class GeneradorArchivoDatos {
private:
    string rutaArchivo;

public:
    GeneradorArchivoDatos(const string& ruta) : rutaArchivo(ruta) {}

    void generarArchivo(const vector<EquipoLaboratorio*>& equipos,
                        const vector<Incidencia*>& incidencias) {
        ofstream archivo(rutaArchivo);
        if (!archivo.is_open())
            throw ArchivoException("No se pudo crear: " + rutaArchivo);

        for (auto* eq : equipos) {
            archivo << eq->getId()
            << ";criticidad=" << eq->getCriticidad()
            << ";estado="     << eq->getEstado()
            << ";tiempoInactivo=" << eq->getDiasInactivo()
            << ";cantidadIncidencias=" << eq->getCantIncidencias()
            << "\n";
        }

        for (auto* inc : incidencias) {
            archivo << "INC"
            << ";" << inc->getID()
            << ";dia=" << inc->getDiaReporte()
            << ";resuelta=" << inc->getResuelta()
            << "\n";
        }

        archivo.close();
    }
};


#endif //PROYECTO_1_PROGRA_2_GENERADORARCHIVODATOS_H