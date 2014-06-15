#ifndef CursusWINDOW_H
#define CursusWINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "CursusManager.h"

class CursusEditeur :  public QWidget {
    Q_OBJECT
    CursusManager* cM;
    const Curs* cu;
    QLineEdit* nomCursus;
    QLabel* nomLabel;
    QSpinBox* credCS;
    QLabel* CSLabel;
    QSpinBox* credTM;
    QLabel* TMLabel;
    QSpinBox* credTSH;
    QLabel* TSHLabel;
    QSpinBox* credSP;
    QLabel* SPLabel;
    QComboBox* categorie;
    QLabel* categorieLabel;

    QPushButton* sauver;
    QPushButton* annuler;
    QPushButton* ajouter;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;
    QHBoxLayout* coucheH7;
    QHBoxLayout* coucheH8;
    friend class Curs;

public :
    CursusEditeur(QWidget *parent = 0);
    CursusEditeur(Curs* ,QWidget* parent=0);

public slots :
   void ajouterCursus();
   void sauverCursus();
};

#endif // CursusWINDOW_H
