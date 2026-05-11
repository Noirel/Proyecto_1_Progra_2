//
// Created by N00159834 on 10/5/2026.
//

#ifndef PROYECTO_1_PROGRA_2_GESTORSIMULACION_H
#define PROYECTO_1_PROGRA_2_GESTORSIMULACION_H
#include <iostream>
#include <vector>
#include "GeneradorLogs.h"
#include "IEstrategiaMantenimiento.h"
#include "MantenimientoPreventivo.h"
#include "MantenimientoCorrectivo.h"
#include "PriorizadorEquipos.h"
#include "EquipoLaboratorio.h"
using namespace std;
 
class GestorSimulacion {
private:
    int diaActual;
    vector<EquipoLaboratorio*> equipos;
    PriorizadorEquipos priorizador;
    IEstrategiaMantenimiento* estrategia;
    GeneradorLogs* generadorLogs;
    double riesgoGlobal;
 
    double calcularRiesgoGlobal() {
        if (equipos.empty()) return 0.0;
        double total = 0.0;
        for (EquipoLaboratorio* eq : equipos)
            total += priorizador.calcularPrioridad(eq);
        return total / equipos.size();
    }
 
    void ajustarEstrategia() {
        delete estrategia;
        if (riesgoGlobal > 7.0)
            estrategia = new MantenimientoCorrectivo();
        else
            estrategia = new MantenimientoPreventivo();
    }
 
    void ejecutarDia() {
        cout << "\n========================================" << endl;
        cout << "DIA " << diaActual << endl;
        cout << "========================================" << endl;
 
        // 1. todos los equipos procesan el dia (degradacion)
        for (EquipoLaboratorio* eq : equipos)
            eq->procesarDia();
 
        // 2. calcular prioridades y ordenar
        priorizador.calcularYOrdenar(equipos);
 
        // 3. mostrar top 3 priorizados
        priorizador.imprimirTopPriorizados(3, diaActual);
 
        // 4. seleccionar los 3 de mayor prioridad con su prioridad
        vector<EquipoLaboratorio*> top3 = priorizador.obtenerTopN(3);
 
        // 5. aplicar mantenimiento
        if (estrategia == nullptr)
            throw OperacionException("No hay estrategia asignada al gestor");
 
        for (EquipoLaboratorio* eq : top3)
            estrategia->ejecutar(eq);
 
        // 6. calcular riesgo global
        riesgoGlobal = calcularRiesgoGlobal();
 
        // 7. construir vectores con prioridad para el reporte
        vector<EquipoConPrioridad> atendidosConPrioridad;
        for (EquipoLaboratorio* eq : top3) {
            EquipoConPrioridad ep;
            ep.equipo    = eq;
            ep.prioridad = priorizador.calcularPrioridad(eq);
            atendidosConPrioridad.push_back(ep);
        }
 
        vector<EquipoConPrioridad> pendientesConPrioridad;
        for (EquipoLaboratorio* eq : equipos) {
            bool fueAtendido = false;
            for (EquipoLaboratorio* atendido : top3) {
                if (eq->getId() == atendido->getId()) {
                    fueAtendido = true;
                    break;
                }
            }
            if (!fueAtendido) {
                EquipoConPrioridad ep;
                ep.equipo    = eq;
                ep.prioridad = priorizador.calcularPrioridad(eq);
                pendientesConPrioridad.push_back(ep);
            }
        }
 
        // 8. generar reporte del dia
        generadorLogs->reporteDiario(diaActual, atendidosConPrioridad, pendientesConPrioridad, riesgoGlobal);
 
        // 9. ajustar estrategia para el siguiente dia
        ajustarEstrategia();
 
        diaActual++;
    }
 
public:
    GestorSimulacion(vector<EquipoLaboratorio*>& equipos, GeneradorLogs* generadorLogs)
        : diaActual(1),
          equipos(equipos),
          priorizador(),
          estrategia(new MantenimientoPreventivo()),
          generadorLogs(generadorLogs),
          riesgoGlobal(0.0) {}
 
    ~GestorSimulacion() {
        delete estrategia;
        for (EquipoLaboratorio* eq : equipos)
            delete eq;
        equipos.clear();
    }
 
    void setEstrategia(IEstrategiaMantenimiento* nuevaEstrategia) {
        delete estrategia;
        estrategia = nuevaEstrategia;
    }
 
    void ejecutarSimulacion() {
        cout << "\n========================================" << endl;
        cout << "  INICIO DE SIMULACION - 30 DIAS" << endl;
        cout << "========================================" << endl;
 
        for (int i = 0; i < 30; i++)
            ejecutarDia();
 
        generadorLogs->reporteAcumulado();
 
        cout << "\n========================================" << endl;
        cout << "  SIMULACION FINALIZADA" << endl;
        cout << "========================================" << endl;
    }
};

#endif