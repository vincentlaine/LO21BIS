#ifndef SEMESTRE_ETRANGER_H
#define SEMESTRE_ETRANGER_H

#include <QString>
#include<iostream>
#include"semestre.h"

class SemestreEtranger : public Semestre
{
private :
    QString destination;
    unsigned int creditsPrevus;
public:
    SemestreEtranger(Saison s, unsigned int a, string(d), unsigned int(c) ):Semestre(s, a), destination(d), creditsPrevus(c) { if (c<20||c>40) throw SemestreException("credits non valide"); }
    string getDestination() const { return destination; }
    unsigned int getCredits() const { return creditsPrevus; }
};

#endif // SEMESTRE_ETRANGER_H
