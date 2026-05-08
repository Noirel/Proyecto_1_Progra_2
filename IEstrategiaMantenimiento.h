//
// Created by fabri on 07-May-26.
//

#ifndef PROYECTO_1_PROGRA_2_IESTRATEGIAMANTENIMIENTO_H
#define PROYECTO_1_PROGRA_2_IESTRATEGIAMANTENIMIENTO_H
#include <iostream>
#include "OperacionException.h"
using namespace std;

class IEstrategiaMantenimiento {
public:
    virtual void ejecutar(Equipo* equipo) = 0;
    virtual string getTipoMantenimiento() = 0;
    virtual ~IEstrategiaMantenimiento() = default;
};


#endif //PROYECTO_1_PROGRA_2_IESTRATEGIAMANTENIMIENTO_H