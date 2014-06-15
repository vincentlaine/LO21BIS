#ifndef UVMANAGER_H
#define UVMANAGER_H

#include"UV.h"
#include <fstream>
#include <sstream>
#include <QString>
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include "semestre.h"

QTextStream& operator<<(QTextStream& f, UV& uv);

template<typename EnumType>
class EnumIterator {
    static_assert(is_enum<EnumType>::value, "EnumType have to be an enum");
    EnumType value;
    EnumIterator(EnumType val):value(val){}
public:
    static EnumIterator getFirst() { return EnumIterator(EnumType::first); }
    bool isDone() const { return value>EnumType::last; }
    EnumType operator*() const { return value; }
    void next() { value=(EnumType)(typename std::underlying_type<EnumType>::type(value)+1); }
};

typedef EnumIterator<Note> NoteIterator;
typedef EnumIterator<Categorie> CategorieIterator;
typedef EnumIterator<Saison> SaisonIterator;

class UVManager {
private:

    UV** uvs;
    unsigned int nbUV;
    unsigned int nbMaxUV;
    QString file;
    void addItem(UV* uv);

    bool modification;
    UV* trouverUV(const QString& c) const;
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);

    UVManager();
    ~UVManager();
    friend struct Handler;
    struct Handler{
        UVManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:

    void load(const QString& f);
    void save(const QString& f);
    static UVManager* getInstance();
    static void libererInstance();
    void ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    void supprimerUV(UV* u);
    const UV* getUV(const QString& code) const;
    UV* getUV(const QString& code);
    class Iterator {
        friend class UVManager;
        UV** currentUV;
        unsigned int nbRemain;
        Iterator(UV** u, unsigned nb):currentUV(u),nbRemain(nb){}
    public:
        Iterator():currentUV(0),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw Exception("error, next on an iterator which is done");
            nbRemain--;
            currentUV++;
        }
        UV& current() const {
            if (isDone())
                throw Exception("error, indirection on an iterator which is done");
            return **currentUV;
        }
    };
    Iterator getIterator() {
        return Iterator(uvs,nbUV);
    }

    class iterator {
        UV** current;
        iterator(UV** u):current(u){}
        friend class UVManager;
    public:
        iterator():current(0){}
        UV& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(uvs); }
    iterator end() { return iterator(uvs+nbUV); }

    class FilterIterator {
        friend class UVManager;
        UV** currentUV;
        unsigned int nbRemain;
        Categorie categorie;
        FilterIterator(UV** u, unsigned nb, Categorie c):currentUV(u),nbRemain(nb),categorie(c){
            while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie){
                nbRemain--; currentUV++;
            }
        }
    public:
        FilterIterator():currentUV(0),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw Exception("error, next on an iterator which is done");
            do {
                nbRemain--; currentUV++;
            }while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie);
        }
        UV& current() const {
            if (isDone())
                throw Exception("error, indirection on an iterator which is done");
            return **currentUV;
        }
    };
    FilterIterator getFilterIterator(Categorie c) {
        return FilterIterator(uvs,nbUV,c);
    }
};

#endif // UVMANAGER_H
