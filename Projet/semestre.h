#ifndef SEMESTRE_H
#define SEMESTRE_H

#include <QString>
#include <QTextStream>
#include<iostream>
#include"exception.h"

enum class Saison { Automne, Printemps, first=Automne, last=Printemps };

class Semestre {
    Saison saison;
    unsigned int annee;
public:
    Semestre(Saison s, unsigned int a):saison(s),annee(a){ if (annee<1972||annee>2099) throw Exception("annee non valide"); }
    Saison getSaison() const { return saison; }
    unsigned int getAnnee() const { return annee; }
};

//inline QTextStream& operator<<(QTextStream& f, const Semestre& s) { return f<<s.getSaison()<<s.getAnnee()%100; }


#endif // SEMESTRE_H
