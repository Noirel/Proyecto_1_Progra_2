//
// Created by N00159834 on 12/4/2026.
//

#ifndef PROYECTO_1_PROGRA_2_OPERACIONEXCEPTION_H
#define PROYECTO_1_PROGRA_2_OPERACIONEXCEPTION_H
#include "SistemaException.h"

class OperacionException : public SistemaException {
    public:
    OperacionException() : SistemaException("Operacion invalida") {};
    OperacionException(string msj) : SistemaException(msj) {};
};


#endif //PROYECTO_1_PROGRA_2_OPERACIONEXCEPTION_H
