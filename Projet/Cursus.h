#ifndef CURSUS_H
#define CURSUS_H

#include <QString>

enum CategorieCursus {
    TC,Cursus,Filiere,HuTech, Mineur, autre, first=TC, last=autre
};

class Curs{
private:
    QString* tabUV;
    unsigned int nbUV;
    unsigned int nbMaxUV;
    QString nom;
    CategorieCursus categorie;
    unsigned int credCS;
    unsigned int credTM;
    unsigned int credTSH;
    unsigned int credSP;

    Curs(const Curs &c);
    Curs& operator=(const Curs& c);
    Curs(QString n, CategorieCursus cat, unsigned int nbCS, unsigned int nbTM, unsigned int nbTSH, unsigned int nbSP) : nom(n), categorie(cat), credCS(nbCS), credTM(nbTM), credTSH(nbTSH), credSP(nbSP),nbUV(0), nbMaxUV(4), tabUV(new QString[4]){}

    friend class CursusManager;
public :
    QString getNom() const {return nom;}
    CategorieCursus getCategorie() const {return categorie;}
    const QString* getTabUV()const{return tabUV;}
    unsigned int getNbUV()const{return nbUV;}
    unsigned int getCredCS()const {return credCS;}
    unsigned int getCredTM()const {return credTM;}
    unsigned int getCredTSH() const {return credTSH;}
    unsigned int getCredSP() const {return credSP;}
    void setCredCS(unsigned int n){credCS=n;}
    void setCredTM(unsigned int n){credTM=n;}
    void setCredTSH(unsigned int n){credTSH=n;}
    void setCredSP(unsigned int n){credSP=n;}
    void setCategorie(CategorieCursus c){categorie=c;}
    void addUV(QString u);
};

#endif // Cursus_H
