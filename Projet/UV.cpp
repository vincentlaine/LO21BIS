#include "UV.h"
#include"exception.h"

using namespace std;

QTextStream& operator<<(QTextStream& f, const UV& uv){
    return f<<uv.getCode()<<", "<<uv.getCategorie()<<", "<<uv.getNbCredit()<<" credits, "<<uv.getTitre();
}

QTextStream& operator>>(QTextStream& f, Categorie& cat){
    QString str;
    f>>str;
    if (str=="CS") cat=Categorie::CS;
    else
    if (str=="TM") cat=Categorie::TM;
    else
    if (str=="SP") cat=Categorie::SP;
    else
    if (str=="TSH") cat=Categorie::TSH;
    else {
        throw Exception("erreur, lecture categorie");
    }
    return f;
}

QTextStream& operator<<(QTextStream& f, const Categorie& cat){
    switch(cat){
    case Categorie::CS: f<<"CS"; break;
    case Categorie::TM: f<<"TM"; break;
    case Categorie::SP: f<<"SP"; break;
    case Categorie::TSH: f<<"TSH"; break;
    default: throw Exception("erreur, categorie non traitee");
    }
    return f;
}

Categorie StringToCategorie(const QString& str){
    if (str=="CS") return Categorie::CS;
    else
    if (str=="TM") return Categorie::TM;
    else
    if (str=="SP") return Categorie::SP;
    else
    if (str=="TSH") return Categorie::TSH;
    else {
        throw Exception(QString("erreur, StringToCategorie, categorie ")+str+" inexistante");
    }
}

QString CategorieToString(Categorie c){
    switch(c){
    case Categorie::CS: return "CS";
    case Categorie::TM: return "TM";
    case Categorie::SP: return "SP";
    case Categorie::TSH: return "TSH";
    default: throw Exception("erreur, categorie non traitee",__FILE__,__LINE__);
    }
}

/*
Note StringToNote(const QString& s)
{
    if (s=="A") return Note::A;
    else
    if (s=="B") return Categorie::TM;
    else
    if (s=="C") return Categorie::SP;
    else
    if (s=="D") return Categorie::TSH;
    else
    if (s=="D") return Categorie::TSH;
    else {
        throw Exception(QString("erreur, StringToCategorie, categorie ")+str+" inexistante");
    }
}
QString NoteToString(Note N);*/
