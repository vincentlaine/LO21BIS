#ifndef UVWINDOW_H
#define UVWINDOW_H

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
#include "UVManager.h"
#include "UV.h"

class UVEditeur : public QWidget{
    Q_OBJECT
    UV* uv;
    QLineEdit* code;
    QLabel* codeLabel;
    QTextEdit* titre;
    QLabel* titreLabel;
    QSpinBox* credits;
    QLabel* creditsLabel;
    QComboBox* categorie;
    QLabel* categorieLabel;
    QLabel* ouvertureLabel;
    QCheckBox* automne;
    QCheckBox* printemps;
    QPushButton* ajouter;
    QPushButton* sauver;
    QPushButton* annuler;
    QPushButton* supprimer;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
public:
    UVEditeur(QWidget *parent = 0);
    UVEditeur(UV* uvToEdit, QWidget *parent = 0);
signals:
public slots:
    void sauverUV();
    void ajouterUV();
    void supprimerUV();
    void activerSauver(QString);
private slots:
};

#endif // UVWINDOW_H

