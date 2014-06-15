#ifndef UV_H
#define UV_H

#include <QString>
#include <QTextStream>
#include <type_traits>
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include "exception.h"

using namespace std;

enum class Categorie {
    CS, TM, TSH, SP,first=CS, last=SP
};

enum class Note { A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC, first=A, last=EC  };

QTextStream& operator<<(QTextStream& f, const Categorie& s);
QTextStream& operator>>(QTextStream& f, Categorie& cat);

Categorie StringToCategorie(const QString& s);
QString CategorieToString(Categorie c);

class UV{

private:
    QString code;
    QString titre;
    unsigned int nbCredit;
    Categorie cat;
    bool automne;
    bool printemps;
    UV(const UV& u);
    UV& operator=(const UV& u);
    UV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p):
       code(c),titre(t),nbCredit(nbc),cat(cat),automne(a),printemps(p){}
    friend class UVManager;

public:
    QString const getCode()const { return code; }
    QString const getTitre()const { return titre; }
    Categorie getCategorie()const { return cat; }
    unsigned int getNbCredit()const { return nbCredit; }
    bool ouvertureAutomne() const { return automne; }
    bool ouverturePrintemps() const { return printemps; }
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
    void setNbCredit(unsigned int n) { nbCredit=n; }
    void setCategorie(Categorie c) { cat=c; }
    void setOuvertureAutomne(bool b) { automne=b; }
    void setOuverturePrintemps(bool b) { printemps=b; }

};

inline QTextStream& operator<<(QTextStream& f, const UV& uv);



#endif // UV_H
