//
// Created by fabri on 12/4/2026.
//

#ifndef PROYECTO_1_PROGRA_2_SISTEMAEXCEPTION_H
#define PROYECTO_1_PROGRA_2_SISTEMAEXCEPTION_H
#include <exception>
#include <iostream>
using namespace std;

class SistemaException : public std::exception {
protected:
    string msj;
public:
    SistemaException(string msj) {
        this->msj = msj;
    }
    SistemaException() {
        this->msj = "Error sistema";
    }
    string message() {
        return this->msj;
    }

};


#endif //PROYECTO_1_PROGRA_2_SISTEMAEXCEPTION_H
