#include "CursusWindow.h"

CursusEditeur::CursusEditeur(QWidget* parent) : QWidget(parent) {
    this->setWindowTitle(QString("Edition de cursus "));

    nomLabel = new QLabel("Nom cursus", this);
    CSLabel = new QLabel("Crédits CS à valider", this);
    TMLabel = new QLabel("Créidts TM à valider", this);
    TSHLabel = new QLabel("Crédits TSH à valider", this);
    SPLabel = new QLabel("Crédits SP à valider" , this);
    categorieLabel = new QLabel("Catégorie de Cursus", this);
    credCS=new QSpinBox(this);
    credCS->setRange(0,100);
    credTM=new QSpinBox(this);
    credTM->setRange(0,100);
    credTSH=new QSpinBox(this);
    credTSH->setRange(0,100);
    credSP=new QSpinBox(this);
    credSP->setRange(0,100);
    categorie=new QComboBox(this);
    for(CursusIterator it=CursusIterator::getFirst(); !it.isDone(); it.next())
        categorie->addItem(CategorieCursusToString(*it));

    nomCursus= new QLineEdit("", this);
    credCS->setValue(0);
    credTM->setValue(0);
    credTSH->setValue(0);
    credSP->setValue(0);

    sauver = new QPushButton("Sauver", this);
    annuler = new QPushButton("Annuler", this);
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(nomLabel);
    coucheH1->addWidget(nomCursus);
    coucheH1->addWidget(categorieLabel);
    coucheH1->addWidget(categorie);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(CSLabel);
    coucheH2->addWidget(credCS);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(TMLabel);
    coucheH3->addWidget(credTM);
    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(TSHLabel);
    coucheH4->addWidget(credTSH);
    coucheH5 = new QHBoxLayout;
    coucheH5->addWidget(SPLabel);
    coucheH5->addWidget(credSP);

    coucheH6 = new QHBoxLayout;
    coucheH6->addWidget(sauver);
    coucheH6->addWidget(annuler);

    couche= new QVBoxLayout;
    couche->addItem(coucheH1);
    couche->addItem(coucheH2);
    couche->addItem(coucheH3);
    couche->addItem(coucheH4);
    couche->addItem(coucheH5);
    couche->addItem(coucheH6);
    setLayout(couche);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(ajouterCursus()));
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
}

CursusEditeur::CursusEditeur(Curs* c, QWidget* parent) : cu(c), QWidget(parent) {
    this->setWindowTitle(QString("Edition de cursus "));

    nomLabel = new QLabel("Nom cursus", this);
    CSLabel = new QLabel("Crédits CS à valider", this);
    TMLabel = new QLabel("Créidts TM à valider", this);
    TSHLabel = new QLabel("Crédits TSH à valider", this);
    SPLabel = new QLabel("Crédits SP à valider" , this);
    categorieLabel = new QLabel("Catégorie de Cursus", this);
    credCS=new QSpinBox(this);
    credCS->setRange(0,100);
    credTM=new QSpinBox(this);
    credTM->setRange(0,100);
    credTSH=new QSpinBox(this);
    credTSH->setRange(0,100);
    credSP=new QSpinBox(this);
    credSP->setRange(0,100);

    nomCursus= new QLineEdit(cu->getNom(), this);
    credCS->setValue(cu->getCredCS());
    credTM->setValue(cu->getCredTM());
    credTSH->setValue(cu->getCredTSH());
    credSP->setValue(cu->getCredSP());
    categorie=new QComboBox(this);
    for(CursusIterator it=CursusIterator::getFirst(); !it.isDone(); it.next())
        categorie->addItem(CategorieCursusToString(*it));

    sauver = new QPushButton("Sauver", this);
    annuler = new QPushButton("Annuler", this);
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(nomLabel);
    coucheH1->addWidget(nomCursus);
    coucheH1->addWidget(categorieLabel);
    coucheH1->addWidget(categorie);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(CSLabel);
    coucheH2->addWidget(credCS);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(TMLabel);
    coucheH3->addWidget(credTM);
    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(TSHLabel);
    coucheH4->addWidget(credTSH);
    coucheH5 = new QHBoxLayout;
    coucheH5->addWidget(SPLabel);
    coucheH5->addWidget(credSP);

    coucheH6 = new QHBoxLayout;
    coucheH6->addWidget(sauver);
    coucheH6->addWidget(annuler);

    couche= new QVBoxLayout;
    couche->addItem(coucheH1);
    couche->addItem(coucheH2);
    couche->addItem(coucheH3);
    couche->addItem(coucheH4);
    couche->addItem(coucheH5);
    couche->addItem(coucheH6);
    setLayout(couche);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(sauverCursus()));
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
}

void CursusEditeur::sauverCursus(){
    cu->setNom(nomCursus->text());
    cu->setCredCS(credCS->value());
    cu->setCredTM(credTM->value());
    cu->setCredTSH(credTSH->value());
    cu->setCredSP(credSP->value());
    QMessageBox::information(this, "Sauvegarde", "Cursus sauvegardé");
    close();
}

void CursusEditeur::ajouterCursus(){
    CursusManager::getInstance()->ajouterCursus(nomCursus->text(), CategorieCursus(categorie->currentIndex()), credCS->value(), credTM->value(), credTSH->value(), credSP->value());
    QMessageBox::information(this, "Sauvegarde", "Cursus ajouté");
    this->close();
}

