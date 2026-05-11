//
// Created by N00159834 on 12/4/2026.
//

#ifndef PROYECTO_1_PROGRA_2_ARCHIVOEXCEPTION_H
#define PROYECTO_1_PROGRA_2_ARCHIVOEXCEPTION_H
#include "SistemaException.h"

class ArchivoException : public SistemaException {
public:
    ArchivoException() : SistemaException("Archivo Invalido"){}
    ArchivoException(string msj) : SistemaException(msj){}

};

#endif //PROYECTO_1_PROGRA_2_ARCHIVOEXCEPTION_H
