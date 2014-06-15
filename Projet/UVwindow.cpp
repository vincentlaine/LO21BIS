#include "UVwindow.h"

UVEditeur::UVEditeur(UV* uvToEdit, QWidget *parent) :
QWidget(parent),uv(uvToEdit){
    this->setWindowTitle(QString("Edition de l’UV ")+uv->getCode());
    // creation des labels
    codeLabel = new QLabel("code",this);
    titreLabel = new QLabel("titre",this);
    creditsLabel = new QLabel("credits",this);
    categorieLabel = new QLabel("categorie",this);
    ouvertureLabel = new QLabel("ouverture",this);
    // création des composants éditables
    code = new QLineEdit(uv->getCode(),this);
    titre = new QTextEdit(uv->getTitre(),this);
    credits=new QSpinBox(this);
    credits->setRange(1,8);
    credits->setValue(uv->getNbCredit());
    categorie=new QComboBox(this);
    for(CategorieIterator it=CategorieIterator::getFirst(); !it.isDone(); it.next())
    categorie->addItem(CategorieToString(*it));
    categorie->setCurrentIndex(int(uv->getCategorie()));
    automne=new QCheckBox("automne",this);
    automne->setChecked(uv->ouvertureAutomne());
    printemps=new QCheckBox("printemps",this);
    printemps->setChecked(uv->ouverturePrintemps());
    sauver= new QPushButton("Sauver", this);
    annuler= new QPushButton("Annuler", this);
    supprimer= new QPushButton("Supprimer", this);
    // diposition des couches
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(categorieLabel);
    coucheH1->addWidget(categorie);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(credits);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(ouvertureLabel);
    coucheH3->addWidget(automne);
    coucheH3->addWidget(printemps);
    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(supprimer);
    coucheH4->addWidget(annuler);
    coucheH4->addWidget(sauver);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    setLayout(couche);

    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverUV()));
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(supprimerUV()));
    QObject::connect(annuler,SIGNAL(clicked()), this, SLOT(close()));
}

UVEditeur::UVEditeur(QWidget *parent) :
QWidget(parent){
    this->setWindowTitle(QString("Ajout d'une nouvelle UV"));
    // creation des labels
    codeLabel = new QLabel("code",this);
    titreLabel = new QLabel("titre",this);
    creditsLabel = new QLabel("credits",this);
    categorieLabel = new QLabel("categorie",this);
    ouvertureLabel = new QLabel("ouverture",this);
    // création des composants éditables
    code = new QLineEdit("code",this);
    titre = new QTextEdit("titre",this);
    credits=new QSpinBox(this);
    credits->setRange(1,8);
    categorie=new QComboBox(this);
    for(CategorieIterator it=CategorieIterator::getFirst(); !it.isDone(); it.next())
        categorie->addItem(CategorieToString(*it));
    automne=new QCheckBox("automne",this);
    printemps=new QCheckBox("printemps",this);
    ajouter= new QPushButton("Ajouter", this);
    annuler= new QPushButton("Annuler", this);

    // diposition des couches
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(categorieLabel);
    coucheH1->addWidget(categorie);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(credits);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(ouvertureLabel);
    coucheH3->addWidget(automne);
    coucheH3->addWidget(printemps);
    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(annuler);
    coucheH4->addWidget(ajouter);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    setLayout(couche);

    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterUV()));
    QObject::connect(annuler,SIGNAL(clicked()), this, SLOT(close()));
}

void UVEditeur::sauverUV(){
    uv->setCode(code->text());
    uv->setTitre(titre->toPlainText());
    uv->setNbCredit(credits->value());
    uv->setCategorie(Categorie(categorie->currentIndex()));
    uv->setOuverturePrintemps(printemps->isChecked());
    uv->setOuvertureAutomne(automne->isChecked());
    QMessageBox::information(this, "Sauvegarde", "UV sauvegardée...");
}

void UVEditeur::ajouterUV(){
    UVManager::getInstance()->ajouterUV(code->text(), titre->toPlainText(), credits->value(), Categorie(categorie->currentIndex()), printemps->isChecked(), automne->isChecked());
    QMessageBox::information(this, "Sauvegarde", "UV sauvegardée...");
}

void UVEditeur::supprimerUV(){
    UVManager::getInstance()->supprimerUV(uv);
    QMessageBox::information(this, "Sauvegarde", "UV supprimée...");
}
