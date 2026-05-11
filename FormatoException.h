//
// Created by N00159834 on 12/4/2026.
//

#ifndef PROYECTO_1_PROGRA_2_FORMATOEXCEPTION_H
#define PROYECTO_1_PROGRA_2_FORMATOEXCEPTION_H
#include "SistemaException.h"

class FormatoException : public SistemaException {
public:
    FormatoException() : SistemaException("Formato invalido") {};
};


#endif //PROYECTO_1_PROGRA_2_FORMATOEXCEPTION_H
