#ifndef EQUIVALENCE_H
#define EQUIVALENCE_H

#include <QString>
#include <QTextStream>
#include "cursus.h"
#include "UVManager.h"
#include "dossier.h"


class Equivalence{
    QString nomEtablissement;
    QString pays;
    unsigned int equiCS;
    unsigned int equiTM;
    unsigned int equiTSH;
    unsigned int equiSP;
public :

    Equivalence(Equivalence* e);
    Equivalence(QString nom, QString p, unsigned int Cs, unsigned int Tm, unsigned int Tsh, unsigned int Sp=0):nomEtablissement(nom), pays(p), equiCS(Cs), equiTM(Tm), equiTSH(Tsh), equiSP(Sp){}
    QString getNomEtablissement()const{return nomEtablissement;}

    QString getPays()const{return pays;}

    unsigned int getEquiCS()const{return equiCS;}

    unsigned int getEquiTM()const{return equiTM;}

    unsigned int getEquiTSH()const{return equiTSH;}

    unsigned int getEquiSP()const{return equiSP;}

    void setNomEtablissement(QString n){nomEtablissement=n;}

    void setPays(QString p){pays=p;}
    void setEquiCS(unsigned int C){equiCS=C;}
    void setEquiTM(unsigned int T){equiTM=T;}
    void setEquiTSH(unsigned int Tsh){equiTSH=Tsh;}
    void setEquiSP(unsigned int S){equiSP=S;}

};

class Dossier;

class EquivalenceEditeur : public QWidget{
    Q_OBJECT
    Dossier* unDossier;/** instance unique de Dossier*/
    Equivalence* equivalence;/** équivalence à éditer*/
    QLabel* nomEtLabel;
    QLineEdit* nomEt;/** zone de texte contenant le nom de l'établissement*/
    QLabel* paysLabel;
    QLineEdit* pays;/** zone de texte contenant le nom du pays*/
    QLabel* csLabel;
    QSpinBox* cs;/** nombre de crédits CS obtenus*/
    QLabel* tmLabel;
    QSpinBox* tm;/** nombre de crédits TM obtenus*/
    QLabel* tshLabel;
    QSpinBox* tsh;/** nombre de crédits TSH obtnenus*/
    QLabel* spLabel;
    QSpinBox* sp;/** nombre de crédits SP obtenus*/
    QVBoxLayout* couche;
    QHBoxLayout* coucheh;
    QPushButton* sauver;/** bouton permettant de sauver l'équivalence*/
    QPushButton* ajouter;/** bouton permettant d'ajouter une nouvelle équivalence*/
public :
    EquivalenceEditeur(Dossier* d,Equivalence *eq=0, QWidget* parent=0);
public slots :

    void modifEqui();
};


#endif // EQUIVALENCE_H
