#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include "UVManager.h"
#include "dossier.h"
#include "UV.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QMessageBox>

class Inscription {
        const UV* uv;
        Semestre semestre;
        Note resultat;
public:

        Inscription(const UV& u, const Semestre& s, Note res= Note::EC):uv(&u),semestre(s), resultat(res){}
        const UV& getUV() const { return *uv; }
        Semestre getSemestre() const { return semestre; }
        Note getResultat() const { return resultat; }

        void setSemestre(Semestre newsem) {semestre = newsem;}

        void setResultat(Note newres) { resultat=newres; }

        bool uvResussie(){if (resultat== Note::A || resultat== Note::B || resultat== Note::C || resultat== Note::D || resultat== Note::E) return true; return false;}
};

class Dossier;

class InscriptionEditeur : public QWidget{
    Q_OBJECT
    Dossier* unDossier;
    Inscription* inscription;
    QLabel* UVLabel;
    QLineEdit* uv;
    QLabel* semestreLabel;
    QLineEdit* semestre;
    QLabel* resultatLabel;
    QComboBox* resultat;
    QVBoxLayout* couche;
    QHBoxLayout* coucheh;
    QPushButton* sauver;
public :
    InscriptionEditeur(Dossier* d, Inscription *ins=0, QWidget* parent=0);
public slots :
    void modifRes();
};

#endif // INSCRIPTION_H
