#ifndef DOSSIER_H
#define DOSSIER_H


#include <QString>
#include <QTextStream>
#include "cursus.h"
#include "UVManager.h"
#include "UV.h"
#include "Inscription.h"
//#include "Equivalence.h"
#include "CursusManager.h"
#include <QTableWidget>
#include <QListView>
#include <QLineEdit>

using namespace std;

class Inscription;
class Equivalence;


class Dossier{
    QString fileI;
    QString fileE;
    QString fileD;
    CursusManager& CM;
    UVManager& UVM;
    Cursus** cursus;
    Inscription** inscriptions;
    Equivalence** equivalences;
    bool activiteExtraScolaire;
    bool niveauB2;
    unsigned int nbCur;
    unsigned int nbMaxCur;
    unsigned int nbIns;
    unsigned int nbMaxIns;
    unsigned int nbEq;
    unsigned int nbMaxEq;
    static Dossier* instanceUnique;

    Dossier(CursusManager& c, UVManager& u, Cursus** tabCur, Inscription** tabI, Equivalence** tabE, bool aes, bool B2, unsigned int nc, unsigned int ni, unsigned int ne);

    Dossier(CursusManager& c=CursusManager::getInstance(), UVManager& u=UVManager::getInstance()): CM(c), UVM(u), inscriptions(new Inscription*), equivalences(new Equivalence*), activiteExtraScolaire(false), niveauB2(false), nbCur(0), nbIns(0), nbEq(0), nbMaxCur(0), nbMaxIns(0), nbMaxEq(0),fileI(""), fileE(""), fileD("") {}

    Dossier(const Dossier* instance);

    virtual ~Dossier();

    virtual void operator=(const Dossier&){}
public :

    CursusManager& getCursusManager() const {return CM;}

    Cursus** getCursus() const {return cursus;}

    Inscription** getInscriptions() const {return inscriptions;}

    void loadInscription(const QString& f);

    void saveInscription();

    void loadEquivalence(const QString& f);

    void saveEquivalence();

    void loadDossier(const QString &f);

    void saveDossier();

    Equivalence** getEquivalences() const {return equivalences;}

    unsigned int getNbCur() const{return nbCur;}

    unsigned int getNbIns() const{return nbIns;}

    unsigned int getNbEq() const{return nbEq;}

    bool getActiviteES(){return activiteExtraScolaire;}

    bool getnivB2(){return niveauB2;}

    void addCursus(Cursus* c);

    void supprCur(Cursus* c);

    void addInscription(Inscription* i);

    void addEquivalence(Equivalence* e);

    void setAES(bool val){activiteExtraScolaire = val;}

    void setNivB2(bool val){niveauB2 = val;}
    static Dossier& donneInstance(CursusManager& c=CursusManager::getInstance(), UVManager& u=UVManager::getInstance());

    static void libereInstance();


};





#endif // DOSSIER_H
