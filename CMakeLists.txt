cmake_minimum_required(VERSION 4.1)
project(Proyecto_1_Progra_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto_1_Progra_2 main.cpp
        SistemaException.h
        ArchivoException.h
        FormatoException.h
        OperacionException.h
        Incidencia.h
        Equipo.h
        EquipoLaboratorio.h
        IEstrategiaMantenimiento.h
        EquipoCritico.h
        MantenimientoPreventivo.h
        MantenimientoCorrectivo.h)
