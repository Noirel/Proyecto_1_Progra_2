//
// Created by fabri on 09-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_GENERADORLOGS_H
#define PROYECTO_1_PROGRA_2_GENERADORLOGS_H
#include <iostream>
#include <fstream>
#include <vector>
#include "EquipoLaboratorio.h"
#include "ArchivoException.h"
#include <sstream>
using namespace std;

// par equipo + prioridad para el reporte
struct EquipoConPrioridad {
    EquipoLaboratorio* equipo;
    double prioridad;
};

class GeneradorLogs {
private:
    ofstream archivoSalida;
    vector<string> historial;
    string rutaArchivo;
public:
    GeneradorLogs(const string &rutaArchivo) : rutaArchivo(rutaArchivo) {
        archivoSalida.open(rutaArchivo);
        if (!archivoSalida.is_open()) {
            throw ArchivoException("No se pudo abrir el archivo de salida: " + rutaArchivo);
        }
    }

    ~GeneradorLogs() {
        if (archivoSalida.is_open())
            archivoSalida.close();
    }

    string reporteDiario(int dia,
                         const vector<EquipoConPrioridad> &atendidos,
                         const vector<EquipoConPrioridad> &pendientes,
                         double riesgoGlobal) {
        stringstream ss;
        ss << "========================================\n";
        ss << "Dia: " << dia << "\n";
        ss << "========================================\n";

        ss << "Equipos Atendidos:\n";
        for (auto& ep : atendidos) {
            ss << " [" << ep.equipo->getId() << "]"
               << " - Prioridad: " << ep.prioridad
               << " - Estado: "    << ep.equipo->getEstado() << "%"
               << " - Criticidad: "<< ep.equipo->getCriticidad()
               << " - Incidencias: "<< ep.equipo->getCantIncidencias()
               << "\n";
        }

        ss << "======================================\n";
        ss << "Cantidad de Equipos Pendientes: " << pendientes.size() << "\n";
        for (auto& ep : pendientes) {
            ss << " [" << ep.equipo->getId() << "]"
               << " - Prioridad: " << ep.prioridad
               << "\n";
        }

        ss << "=====================================\n";
        string nivelRiesgo = riesgoGlobal > 7.0 ? "ALTO" : riesgoGlobal > 4.0 ? "MEDIO" : "BAJO";
        ss << "Nivel de Riesgo Global: " << nivelRiesgo << " (" << riesgoGlobal << ")\n";
        ss << "=====================================\n";

        historial.push_back(ss.str());
        archivoSalida << ss.str();
        archivoSalida.flush();
        cout << ss.str();
        return ss.str();
    }

    string reporteAcumulado() {
        stringstream resumen;
        resumen << "=====================================\n";
        resumen << "| | RESUMEN FINAL DE LOS 30 DIAS | |\n";
        resumen << "=====================================\n";
        resumen << "Total de Dias Simulados: 30\n";
        resumen << "Total de Equipos Atendidos: " << historial.size() * 3 << "\n";
        resumen << "Total de Logs Generados: "    << historial.size() << "\n";
        archivoSalida << resumen.str();
        cout << resumen.str();
        return resumen.str();
    }
};


#endif //PROYECTO_1_PROGRA_2_GENERADORLOGS_H