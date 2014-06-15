#ifndef CATEGORIE_H
#define CATEGORIE_H

#include <QString>
#include <QTextStream>
#include <type_traits>
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

#include "exception.h"

class Categories{

private:
    QString code;
    QString titre;
    Categories(const Categories& c);
    Categories& operator=(const Categories& c);
    Categories(const QString& c, const QString& t):
       code(c),titre(t){}
    friend class UV;

public:
    QString const getCode()const { return code; }
    QString const getTitre()const { return titre; }
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
};

inline QTextStream& operator<<(QTextStream& f, const Categories& c);

#endif // CATEGORIE_H
