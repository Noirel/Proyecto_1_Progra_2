//
// Created by N00159834 on 4/5/2026.
//

#ifndef PROYECTO_1_PROGRA_2_INCIDENCIA_H
#define PROYECTO_1_PROGRA_2_INCIDENCIA_H


class Incidencia {
private:
    string id;
    enum NivelSeveridad {
        No_Tiene = 0,
        Baja = 1,
        Media = 5,
        Alta = 9
    };
    NivelSeveridad severidad;
    int diaReporte;
    bool resuelta;
public:
    Incidencia(const string &id, int dia_reporte, bool resuelta) : id(id), diaReporte(dia_reporte), resuelta(resuelta), severidad(No_Tiene) {
    }

    string getID() const {
        return id;
    }

    void setId(const string &id) {
        this->id = id;
    }

    int getDiaReporte() const {
        return diaReporte;
    }

    void setDiaReporte(int diaReporte) {
        this->diaReporte = diaReporte;
    }

    bool getResuelta() const {
        return resuelta;
    }

    void setResuelta(bool resuelta) {
        this->resuelta = resuelta;
    }

    NivelSeveridad getSeveridad() const {
        return severidad;
    }

    void setSeveridad(int severidad) {
        this->severidad = static_cast<NivelSeveridad>(severidad);
    }

};


#endif //PROYECTO_1_PROGRA_2_INCIDENCIA_H
