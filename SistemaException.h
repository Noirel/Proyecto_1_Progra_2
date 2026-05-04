//
// Created by N00159834 on 4/5/2026.
//

#ifndef PROYECTO_1_PROGRA_2_SISTEMAEXCEPTION_H
#define PROYECTO_1_PROGRA_2_SISTEMAEXCEPTION_H
#include <exception>
#include <iostream>
using namespace std;

class SistemaException : public std::exception {
protected:
    string message;
public:
    SistemaException(string message) {
        this->message = message;
    }
    SistemaException() {
        this->message = "Error sistema";
    }
    string message() {
        return this->message;
    }

};


#endif //PROYECTO_1_PROGRA_2_SISTEMAEXCEPTION_H
