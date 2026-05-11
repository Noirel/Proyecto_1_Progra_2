//
// Created by fabri on 08-May-26.
//

#include <iostream>
#include <vector>
#include <random>
#include "GeneradorArchivoDatos.h"
#include "CargadorArchivos.h"
#include "GeneradorLogs.h"
#include "GestorSimulacion.h"
#include "EquipoLaboratorio.h"
#include "Incidencia.h"
using namespace std;

int main() {

    // generador de numeros aleatorios
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> distCriticidad(1, 10);
    uniform_int_distribution<int> distIncidencias(0, 5);  // 0 a 5 incidencias por equipo
    uniform_int_distribution<int> distTiempo(0, 14);
    uniform_int_distribution<int> distDia(1, 30);

    // =============================================
    // 1. CREAR EQUIPOS E INCIDENCIAS EN MEMORIA
    // =============================================
    vector<EquipoLaboratorio*> equiposIniciales;
    vector<Incidencia*> incidenciasIniciales;

    // 300 equipos — criticidad al azar, estado depende de cantidad de incidencias
    for (int i = 1; i <= 300; i++) {
        string id          = "EQ-" + to_string(i);
        int criticidad     = distCriticidad(gen);           // criticidad al azar 1-10
        int cantIncidencias = distIncidencias(gen);         // 0 a 5 incidencias
        double estado      = 100.0 - (cantIncidencias * 10.0); // mas incidencias = peor estado
        int tiempoInact    = distTiempo(gen);

        EquipoLaboratorio* eq = new EquipoLaboratorio(id, criticidad, estado, tiempoInact);

        // crear las incidencias del equipo (puede ser 0)
        for (int j = 0; j < cantIncidencias; j++) {
            int dia         = distDia(gen);
            Incidencia* inc = new Incidencia(id, dia, false);
            incidenciasIniciales.push_back(inc);
            eq->agregarIncidencia(inc);
        }

        equiposIniciales.push_back(eq);
    }

    // =============================================
    // 2. GENERAR ARCHIVO DE DATOS
    // =============================================
    cout << "--- Generando archivo de datos ---" << endl;
    GeneradorArchivoDatos generador("equipos.txt");
    generador.generarArchivo(equiposIniciales, incidenciasIniciales);
    cout << "Archivo equipos.txt generado con "
         << equiposIniciales.size()     << " equipos y "
         << incidenciasIniciales.size() << " incidencias" << endl;

    // liberar equipos iniciales — incidencias las libera el destructor del equipo
    for (EquipoLaboratorio* eq : equiposIniciales)
        delete eq;
    equiposIniciales.clear();
    incidenciasIniciales.clear();  // punteros ya liberados por ~EquipoLaboratorio

    // =============================================
    // 3. CARGAR DESDE EL ARCHIVO
    // =============================================
    cout << "\n--- Cargando desde archivo ---" << endl;
    CargadorArchivos cargador("equipos.txt");
    vector<EquipoLaboratorio*> equiposCargados = cargador.CargarEquipos();
    cargador.CargarIncidencias(equiposCargados);
    cout << "Cargados " << equiposCargados.size() << " equipos" << endl;

    // =============================================
    // 4. EJECUTAR SIMULACION DE 30 DIAS
    // =============================================
    cout << "\n--- Iniciando simulacion ---" << endl;
    GeneradorLogs* logger = new GeneradorLogs("simulacion_log.txt");

    // GestorSimulacion toma ownership de equiposCargados — no hacer delete despues
    GestorSimulacion gestor(equiposCargados, logger);
    gestor.ejecutarSimulacion();

    delete logger;

    return 0;
}