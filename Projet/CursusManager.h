#ifndef CURSUSMANAGER_H
#define CURSUSMANAGER_H

#include "Cursus.h"
#include "UVManager.h"

typedef EnumIterator<Curs> CursusIterator;

QString CategorieCursusToString(CategorieCursus c);

class CursusManager{
    Curs** mesCursus;
    unsigned int nbCursus;
    unsigned int nbMaxCursus;

    void addItem(Curs* newcursus);
    CursusManager(const CursusManager& cm);
    CursusManager& operator=(const CursusManager& cm);
    CursusManager();
    ~CursusManager();

    friend struct Handler;
    struct Handler{
        CursusManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:
    QString file;
    Curs* trouverCursus(const QString& c) const;
    void load(const QString& f);
    void save();
    static CursusManager* getInstance();
    static void libererInstance();
    void ajouterCursus(const QString n, const QString* t, unsigned int nbU, CategorieCursus c, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP);
    void ajouterCursus(Curs *cur);
    const Curs* getCursus(const QString& nom) const;
    Curs** getMesCursus() const {return mesCursus;}
    unsigned int getNbCursus() const {return nbCursus;}
    Curs* getCursus(const QString& nom);
    void supprimerCursus(const Curs& cu);

    class Iterator {
        friend class CursusManager;
        Curs** currentCursus;
        unsigned int nbRemain;
        Iterator(Curs** c, unsigned nb):currentCursus(c),nbRemain(nb){}
       public:
            Iterator():nbRemain(0),currentCursus(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                        throw Exception("error, next on an iterator which is done");
                nbRemain--;
                currentCursus++;
            }
            Curs& current() const {
                if (isDone())
                    throw Exception("error, indirection on an iterator which is done");
                return **currentCursus;
            }
    };
    Iterator getIterator() {
        return Iterator(mesCursus,nbCursus);
   }
};

#endif // CURSUSMANAGER_H
