#include "mainwindow.h"
#include "UVwindow.h"
#include "UVManager.h"
#include "CursusManager.h"
#include "CursusWindow.h"
#include "exception.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>

Profiler::Profiler(QWidget *parent):QMainWindow(parent){
    setWindowTitle("UT-Profiler");
    QMenu* mFichier = menuBar()->addMenu("&Fichier");
    QMenu* mCharger=mFichier->addMenu("&Charger");
    QAction * actionChargerUV=mCharger->addAction("Catalogue UVs");
    QAction * actionChargerCursus=mCharger->addAction("Catalogue Cursus");
    mFichier->addSeparator();
    QAction *actionQuitter = mFichier->addAction("&Quitter");
    QMenu* mUV = menuBar()->addMenu("&UV");
    QAction* actionEditerUV=mUV->addAction("&Editer UV");
    QAction* actionAjouterUV=mUV->addAction("&Ajouter UV");
    QMenu* mCursus = menuBar()->addMenu("&Cursus");
    QAction* actionEditerCursus=mCursus->addAction("&Editer Cursus");
    QAction* actionAjouterCursus=mCursus->addAction("&Ajouter Cursus");
    // connections
    connect(actionChargerUV, SIGNAL(triggered()),this,SLOT(openChargerUV()));
    connect(actionChargerCursus, SIGNAL(triggered()),this,SLOT(openChargerCursus()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionEditerUV, SIGNAL(triggered()),this,SLOT(openUV()));
    connect(actionAjouterUV, SIGNAL(triggered()),this,SLOT(ajoutUV()));
    connect(actionEditerCursus, SIGNAL(triggered()),this,SLOT(openCursus()));
    connect(actionAjouterCursus, SIGNAL(triggered()),this,SLOT(ajoutCursus()));
}

void Profiler::openChargerUV(){
    QString chemin = QFileDialog::getOpenFileName();
    UVManager* m=UVManager::getInstance();
    try {
    if (chemin!="")
        m->load(chemin);
        QMessageBox::information(this, "Chargement Catalogue", "Le catalogue d’UVs a été chargé.");
    }catch(
    Exception& e){
        QMessageBox::warning(this, "Chargement Catalogue", "Erreur lors du chargement du fichier (non valide ?)");
    }
}

void Profiler::openChargerCursus(){
    QString chemin = QFileDialog::getOpenFileName();
    CursusManager* c=CursusManager::getInstance();
    try {
    if (chemin!="")
        c->load(chemin);
        QMessageBox::information(this, "Chargement Catalogue", "Le catalogue Cursus a été chargé.");
    }catch(
    Exception& e){
        QMessageBox::warning(this, "Chargement Catalogue", "Erreur lors du chargement du fichier (non valide ?)");
    }
}

void Profiler::openUV(){
    QString code=QInputDialog::getText(this,"Entrez le code de l’UV à éditer","UV");
    if (code!="")
    try {
        UV* uv=UVManager::getInstance()->getUV(code);
        UVEditeur* fenetre=new UVEditeur(uv,this);
        setCentralWidget(fenetre);
    }catch(Exception& e){
        QMessageBox::warning(this, "Edition UV", QString("Erreur : l’UV ")+code+" n’existe pas.");
    }
}

void Profiler::ajoutUV(){
        UVEditeur* fenetre=new UVEditeur(this);
        setCentralWidget(fenetre);
}

void Profiler::openCursus(){
    QString c=QInputDialog::getText(this,"Entrez le cursus à éditer","Filiere");
    if (c!="")
    try {
        Curs* b= CursusManager::getInstance()->getCursus(c);
        CursusEditeur* fenetre=new CursusEditeur(b,this);
        setCentralWidget(fenetre);
    }catch(Exception& e){
        QMessageBox::warning(this, "Edition Cursus", QString("Erreur : la Cursus ")+c+" n’existe pas.");
    }
}

void Profiler::ajoutCursus(){
        CursusEditeur* fenetre = new CursusEditeur(this);
        setCentralWidget(fenetre);
}
