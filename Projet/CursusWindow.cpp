#include "CursusWindow.h"

CursusEditeur::CursusEditeur(QWidget* parent) : QWidget(parent) {
    this->setWindowTitle(QString("Edition de cursus "));

    nomLabel = new QLabel("Nom cursus", this);
    CSLabel = new QLabel("Crédits CS à valider", this);
    TMLabel = new QLabel("Créidts TM à valider", this);
    TSHLabel = new QLabel("Crédits TSH à valider", this);
    SPLabel = new QLabel("Crédits SP à valider" , this);
    categorieLabel = new QLabel("Catégorie de Cursus", this);
    UVsLabel = new QLabel("Liste des UVs", this);
    UVLabel = new QLabel ("Ajouter UV au cursus", this);
    credCS=new QSpinBox(this);
    credCS->setRange(0,10);
    credTM=new QSpinBox(this);
    credTM->setRange(0,10);
    credTSH=new QSpinBox(this);
    credTSH->setRange(0,10);
    credSP=new QSpinBox(this);
    credSP->setRange(0,10);
    categorie=new QComboBox(this);
    for(CategorieIterator it=CategorieIterator::getFirst(); !it.isDone(); it.next())
    categorie->addItem(CategorieToString(*it));
    UVs=new QComboBox(this);
    newUV=new QLineEdit("",this);
    ok=new QPushButton("OK", this);

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

    coucheH7=new QHBoxLayout;
    coucheH7->addWidget(UVsLabel);
    coucheH7->addWidget(UVs);

    coucheH8=new QHBoxLayout;
    coucheH8->addWidget(UVLabel);
    coucheH8->addWidget(newUV);
    coucheH8->addWidget(ok);

    coucheH6 = new QHBoxLayout;
    coucheH6->addWidget(sauver);
    coucheH6->addWidget(annuler);

    couche= new QVBoxLayout;
    couche->addItem(coucheH1);
    couche->addItem(coucheH2);
    couche->addItem(coucheH3);
    couche->addItem(coucheH4);
    couche->addItem(coucheH5);
    couche->addItem(coucheH7);
    couche->addItem(coucheH8);
    couche->addItem(coucheH6);
    setLayout(couche);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(ajouterCursus()));
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ok, SIGNAL(clicked()),this, SLOT(ajoutUV()));
}

CursusEditeur::CursusEditeur(const Curs* c, QWidget* parent) : cu(c), QWidget(parent) {
    this->setWindowTitle(QString("Edition de cursus "));

    nomLabel = new QLabel("Nom cursus", this);
    CSLabel = new QLabel("Crédits CS à valider", this);
    TMLabel = new QLabel("Créidts TM à valider", this);
    TSHLabel = new QLabel("Crédits TSH à valider", this);
    SPLabel = new QLabel("Crédits SP à valider" , this);
    categorieLabel = new QLabel("Catégorie de Cursus", this);
    UVsLabel = new QLabel("Liste des UVs", this);
    UVLabel = new QLabel ("Ajouter UV au cursus", this);
    credCS=new QSpinBox(this);
    credCS->setRange(0,10);
    credTM=new QSpinBox(this);
    credTM->setRange(0,10);
    credTSH=new QSpinBox(this);
    credTSH->setRange(0,10);
    credSP=new QSpinBox(this);
    credSP->setRange(0,10);
    categorie=new QComboBox(this);
    for(CategorieIterator it=CategorieIterator::getFirst(); !it.isDone(); it.next())
    categorie->addItem(CategorieToString(*it));
    UVs=new QComboBox(this);
    newUV=new QLineEdit("",this);
    ok=new QPushButton("OK", this);

    nomCursus= new QLineEdit(cu->getNom(), this);
    credCS->setValue(cu->getCredCS());
    credTM->setValue(cu->getCredTM());
    credTSH->setValue(cu->getCredTSH());
    credSP->setValue(cu->getCredSP());
    QString cat=CategorieCursusToString(c->getCategorie());
    categorie->setCurrentText(cat);
    for(unsigned int i=0; i<cu->getNbUV();i++){
        const QString* s=cu->getTabUV();
        UVs->addItem(s[i]);
    }

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

    coucheH7=new QHBoxLayout;
    coucheH7->addWidget(UVsLabel);
    coucheH7->addWidget(UVs);

    coucheH8=new QHBoxLayout;
    coucheH8->addWidget(UVLabel);
    coucheH8->addWidget(newUV);
    coucheH8->addWidget(ok);

    coucheH6 = new QHBoxLayout;
    coucheH6->addWidget(sauver);
    coucheH6->addWidget(annuler);

    couche= new QVBoxLayout;
    couche->addItem(coucheH1);
    couche->addItem(coucheH2);
    couche->addItem(coucheH3);
    couche->addItem(coucheH4);
    couche->addItem(coucheH5);
    couche->addItem(coucheH7);
    couche->addItem(coucheH8);
    couche->addItem(coucheH6);
    setLayout(couche);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(sauverCursus()));
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ok, SIGNAL(clicked()),this, SLOT(ajoutUV()));
}

void CursusEditeur::ajoutUV(){
    QString uv=newUV->text();
    QString cursusN=nomCursus->text();
    Curs* cursusA=CursusManager::getInstance()->getCursus(cursusN);
    cursusA->addUV(uv);

    newUV->setText("");
    UVs->addItem(uv);
    return;
}

void CursusEditeur::sauverCursus(){
    QString cursusN=nomCursus->text();
    CategorieCursus cat=CategorieCursus(categorie->currentIndex());
    Curs* cursusA=CursusManager::getInstance()->getCursus(cursusN);
    cursusA->setCategorie(cat);
    cursusA->setCredCS(credCS->value());
    cursusA->setCredTM(credTM->value());
    cursusA->setCredTSH(credTSH->value());
    cursusA->setCredSP(credSP->value());
    QMessageBox::information(this, "Sauvegarde", "Cursus sauvegardé");
    close();
}

void CursusEditeur::ajouterCursus(){
    QString cursusN=nomCursus->text();
    CategorieCursus cat=CategorieCursus(categorie->currentIndex());
    CursusManager::getInstance()->ajouterCursus(cursusN, 0, 0, cat, credCS->value(), credTM->value(), credTSH->value(), credSP->value());
    Curs* cursusA=CursusManager::getInstance()->getCursus(cursusN);
    UVs->setCurrentIndex(0);
    for (int i=0;i<UVs->count();i++){
        cursusA->addUV(UVs->currentText());
        UVs->setCurrentIndex(i+1);
    }
    QMessageBox::information(this, "Sauvegarde", "Cursus ajouté");
    this->close();
}

