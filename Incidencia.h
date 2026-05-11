//
// Created by N00159834 on 18/4/2026.
//

#ifndef PROYECTO_1_PROGRA_2_INCIDENCIA_H
#define PROYECTO_1_PROGRA_2_INCIDENCIA_H
#include <iostream>
using namespace std;

class Incidencia {
private:
    string *id;
    int *diaReporte;
    bool resuelta;
public:

    Incidencia(string id, int dia_reporte, bool resuelta) : id(new string(id)), diaReporte(new int(dia_reporte)), resuelta(resuelta) {}

    ~Incidencia() {
        delete id;
        delete diaReporte;
    }

    string getID() const {
        return *id;
    }

    void setId(string &id) {
        this->id = &id;
    }

    int getDiaReporte() const {
        return *diaReporte;
    }

    void setDiaReporte(int &diaReporte) {
        this->diaReporte = &diaReporte;
    }

    bool getResuelta() const {
        return resuelta;
    }

    void setResuelta(bool resuelta) {
        this->resuelta = resuelta;
    }


};


#endif //PROYECTO_1_PROGRA_2_INCIDENCIA_H
