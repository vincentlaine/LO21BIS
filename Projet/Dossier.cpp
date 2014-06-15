#include "dossier.h"
#include "DossierEditeur.h"
//#include "Equivalence.h"
#include "CursusWindow.h"
#include <QDesktopWidget>

Dossier* Dossier::instanceUnique=0;

Dossier::Dossier(CursusManager& c, UVManager& u, Cursus** tabCur, Inscription** tabI, Equivalence** tabE, bool aes, bool B2, unsigned int nc, unsigned int ni, unsigned int ne): CM(c), UVM(u),activiteExtraScolaire(aes), niveauB2(B2), nbCur(0), nbIns(0), nbEq(0), nbMaxCur(0), nbMaxEq(0), nbMaxIns(0), fileI(""), fileE(""), fileD("") {
    for (unsigned int i=0; i<ni;i++){
        this->addInscription(tabI[i]);
    }
    for (unsigned j=0; j<ne;j++){
        this->addEquivalence(tabE[j]);
    }
    for (unsigned j=0; j<nc;j++){
        this->addCursus(tabCur[j]);
    }
}

void Dossier::addInscription(Inscription* i){
    if(nbIns==nbMaxIns){
        Inscription** newTab=new Inscription*[nbMaxIns+10];
        for(unsigned int i=0; i<nbIns;i++) newTab[i]=inscriptions[i];
        nbMaxIns+=10;
        Inscription** old=inscriptions;
        inscriptions=newTab;
        delete[] old;
    }
    inscriptions[nbIns++]=i;
}

void Dossier::addEquivalence(Equivalence* e){
    if(nbEq==nbMaxEq){
        Equivalence** newTab=new Equivalence*[nbMaxEq+10];
        for(unsigned int i=0; i<nbEq;i++) newTab[i]=equivalences[i];
        nbMaxEq+=10;
        Equivalence** old=equivalences;
        equivalences=newTab;
        delete[] old;
    }
    equivalences[nbEq++]=e;
}

void Dossier::addCursus(Cursus* c){
    if(nbCur==nbMaxCur){
        Cursus** newTab=new Cursus*[nbMaxCur+10]; // Ca plante là
        for(unsigned int i=0; i<nbCur;i++) newTab[i]=cursus[i];
        nbMaxCur+=10;
        Cursus** old=cursus;
        cursus=newTab;
        delete[] old; //PROBLEME
    }
    cursus[nbCur++]=c;
}

void Dossier::supprCur(Cursus* c){
    unsigned int i =0;
    while(cursus[i] != c) i++;
    for(unsigned int j=i; j<nbCur; j++)
        cursus[j]=cursus[j+1];
    nbCur--;
}


/*
void Cursus::addUV(QString u){
    if (nbUV==nbMaxUV){
            QString* newtab=new QString[nbMaxUV+10];
            for(unsigned int i=0; i<nbUV; i++) newtab[i]=tabUV[i];
            nbMaxUV+=10;
            QString* old=tabUV;
            tabUV=newtab;
            delete[] old;
    }
    tabUV[nbUV++]=u;
}
*/

void Dossier::libereInstance(){
    if (instanceUnique!=0) delete instanceUnique;
    instanceUnique = 0;
}

Dossier& Dossier::donneInstance(CursusManager &c, UVManager& u){
    //UVManager& u=UVManager::getInstance();
    //CursusManager& c=CursusManager::getInstance();
    if (instanceUnique==0) instanceUnique= new Dossier(c, u);

    return *instanceUnique;
}

DossierEditeur::DossierEditeur(UVManager& m, QWidget* parent) : manager(m), QWidget(parent), CM(CursusManager::getInstance()), doss(Dossier::donneInstance(/*CursusManager::getInstance(), UVManager::getInstance()*/)){
    this->setWindowTitle(QString("Consultation du dossier"));
    cursusLabel = new QLabel("Cursus", this);
    equivalencesLabel = new QLabel("Equivalences", this);
    UVLabel = new QLabel("Inscriptions", this);
    recapLabel = new QLabel("Total crédits", this);

    nomNouvCur = new QLineEdit("Cursus à modifier", this);
    activiteES = new QCheckBox("Activité extra-scolaire", this);
    activiteES->setChecked(doss.getActiviteES());
    B2 = new QCheckBox("Niveau B2 validé", this);
    B2->setChecked(doss.getnivB2());
    modifInscr = new QPushButton("Modifier", this);
    nomInscrAModif = new QLineEdit("Inscription à modifier", this);
    modifEqui = new QPushButton("Modifier", this);
    ajoutEqui=new QPushButton("Ajouter", this);

    ajoutInscr = new QPushButton("Ajouter", this);
    nomEquiAModif = new QLineEdit("Nom Etablissement", this);
    ajouterCursus = new QPushButton("Ajouter", this);
    supprimerCursus = new QPushButton("Supprimer", this);
    sauver = new QPushButton("Sauver", this);
    annuler = new QPushButton("Annuler", this);


    couche= new QVBoxLayout;

    cursus = new QComboBox(this);
    unsigned int i=0;
    QMessageBox::information(0, "NB Cursus vu par dossier editeur", QString::number(doss.getNbCur()));
    while(i<doss.getNbCur()){
        cursus->addItem(doss.getCursus()[i]->getNom());
        i++;
    }

    unsigned int totCredCS=0, totCredTM = 0, totCredTSH=0, totCredSP=0;

    coucheH6 = new QHBoxLayout;

    Equivalence** equi = doss.getEquivalences();
    equivalences = new QTableWidget(this);
    equivalences->setColumnCount(6);
    equivalences->setRowCount(1);
    equivalences->setGeometry(QApplication::desktop()->screenGeometry());
    equivalences->setItem(0, 0, new QTableWidgetItem("Etablissement"));
    equivalences->setItem(0, 1, new QTableWidgetItem("Pays"));
    equivalences->setItem(0, 2, new QTableWidgetItem("CS"));
    equivalences->setItem(0, 3, new QTableWidgetItem("TM"));
    equivalences->setItem(0, 4, new QTableWidgetItem("TSH"));
    equivalences->setItem(0, 5, new QTableWidgetItem("SP"));
    i=0;
    while(i<doss.getNbEq()){
        QTableWidgetItem* nomEt = new QTableWidgetItem((QTableWidgetItem)equi[i]->getNomEtablissement());
        QTableWidgetItem* nomPays = new QTableWidgetItem((QTableWidgetItem)equi[i]->getPays());
        QTableWidgetItem* crCS = new QTableWidgetItem(QString::number(equi[i]->getEquiCS()));
        QTableWidgetItem* crTM = new QTableWidgetItem(QString::number(equi[i]->getEquiTM()));
        QTableWidgetItem* crTSH = new QTableWidgetItem(QString::number(equi[i]->getEquiTSH()));
        QTableWidgetItem* crSP = new QTableWidgetItem(QString::number(equi[i]->getEquiSP()));
        equivalences->insertRow(i+1);
        equivalences->setItem(i+1, 0, nomEt);
        equivalences->setItem(i+1, 1, nomPays);
        equivalences->setItem(i+1, 2, crCS);
        equivalences->setItem(i+1, 3, crTM);
        equivalences->setItem(i+1, 4, crTSH);
        equivalences->setItem(i+1, 5, crSP);

        totCredCS+=equi[i]->getEquiCS();
        totCredTM+=equi[i]->getEquiTM();
        totCredTSH+=equi[i]->getEquiTSH();
        totCredSP+=equi[i]->getEquiSP();
        i++;


    }

    coucheH6->addWidget(equivalencesLabel);
    coucheH6->addWidget(equivalences);
    coucheH6->addWidget(nomEquiAModif);
    coucheH6->addWidget(modifEqui);
    coucheH6->addWidget(ajoutEqui);


    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(cursusLabel);
    coucheH1->addWidget(cursus);
    coucheH1->addWidget(nomNouvCur);
    coucheH1->addWidget(ajouterCursus);
    coucheH1->addWidget(supprimerCursus);


    Inscription** ins=doss.getInscriptions();
    tabUV = new QTableWidget(this);
    tabUV->setColumnCount(3);
    tabUV->setRowCount(1);
    tabUV->setItem(0, 0, new QTableWidgetItem("UVs suivies"));
    tabUV->setItem(0, 1, new QTableWidgetItem("Résultat"));
    tabUV->setItem(0, 2, new QTableWidgetItem("Semestre"));
    i=0;

    while(i<doss.getNbIns()){
        QTableWidgetItem* nomUV = new QTableWidgetItem((QTableWidgetItem)ins[i]->getUV().getCode());
        QTableWidgetItem* resUV = new QTableWidgetItem((QTableWidgetItem)NoteToString(ins[i]->getResultat()));
        QString semestre = semestreToString(ins[i]->getSemestre());
        QTableWidgetItem* sem = new QTableWidgetItem((QTableWidgetItem)semestre);
        tabUV->insertRow(i+1);
        tabUV->setItem(i+1, 0, nomUV);
        tabUV->setItem(i+1, 1, resUV);
        tabUV->setItem(i+1, 2, sem);

        if (ins[i]->getUV().getCategorie() == CS && ins[i]->uvResussie())
            totCredCS+=ins[i]->getUV().getNbCredits();
        else if (ins[i]->getUV().getCategorie() == TM && ins[i]->uvResussie())
            totCredTM+=ins[i]->getUV().getNbCredits();
        else if (ins[i]->getUV().getCategorie() == TSH && ins[i]->uvResussie())
            totCredTSH+=ins[i]->getUV().getNbCredits();
        else if (ins[i]->getUV().getCategorie() == SP && ins[i]->uvResussie())
            totCredSP+=ins[i]->getUV().getNbCredits();
        i++;
    }

    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(UVLabel);
    coucheH2->addWidget(tabUV);
    coucheH2->addWidget(nomInscrAModif);
    coucheH2->addWidget(modifInscr);

    coucheH2->addWidget(ajoutInscr);

    recapCred = new QTableWidget(this);
    recapCred->setColumnCount(5);
    recapCred->setRowCount(2);
    recapCred->setGeometry(QApplication::desktop()->screenGeometry());
    recapCred->setItem(0, 0, new QTableWidgetItem("CS"));
    recapCred->setItem(0, 1, new QTableWidgetItem("TM"));
    recapCred->setItem(0, 2, new QTableWidgetItem("TSH"));
    recapCred->setItem(0, 3, new QTableWidgetItem("SP"));
    recapCred->setItem(0, 4, new QTableWidgetItem("Total"));
    recapCred->setItem(1, 0, new QTableWidgetItem(QString::number(totCredCS)));
    recapCred->setItem(1, 1, new QTableWidgetItem(QString::number(totCredTM)));
    recapCred->setItem(1, 2, new QTableWidgetItem(QString::number(totCredTSH)));
    recapCred->setItem(1, 3, new QTableWidgetItem(QString::number(totCredSP)));
    unsigned int grandTotal = totCredCS + totCredSP + totCredTM + totCredTSH;
    recapCred->setItem(1, 4, new QTableWidgetItem(QString::number(grandTotal)));


    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(recapLabel);
    coucheH3->addWidget(recapCred);
    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(activiteES);
    coucheH4->addWidget(B2);
    coucheH5 = new QHBoxLayout;
    coucheH5->addWidget(sauver);
    coucheH5->addWidget(annuler);
    couche->addItem(coucheH1);
    couche->addItem(coucheH2);
    couche->addItem(coucheH6);
    couche->addItem(coucheH3);
    couche->addItem(coucheH4);
    couche->addItem(coucheH5);
    setLayout(couche);

    QObject::connect(sauver,SIGNAL(clicked()), this, SLOT(sauverDossier()));
    QObject::connect(annuler,SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ajouterCursus,SIGNAL(clicked()), this, SLOT(ajoutCursus()));
    QObject::connect(supprimerCursus,SIGNAL(clicked()), this, SLOT(supprimerCur()));
    QObject::connect(modifInscr,SIGNAL(clicked()), this, SLOT(modifierInscription()));
    QObject::connect(modifEqui,SIGNAL(clicked()), this, SLOT(modifierEquivalence()));
    QObject::connect(ajoutInscr, SIGNAL(clicked()), this, SLOT(ajoutInscription()));
    QObject::connect(ajoutEqui, SIGNAL(clicked()), this, SLOT(ajoutEquivalence()));

}


void DossierEditeur::sauverDossier(){
    doss.setAES(activiteES->isChecked());
    doss.setNivB2(B2->isChecked());
    QMessageBox::information(this, "Sauvegarde Dossier", "Dossier sauvegardé");
    close();
}

void DossierEditeur::ajoutCursus(){
    try{
    QString s = nomNouvCur->text();
    doss.addCursus(&CM.getCursus(s));
    QMessageBox::information(this, "Cursus Ajouté", "Cursus correctement ajouté");
    nomNouvCur->clear();
    cursus->addItem(s);
    }
    catch(UTProfilerException e){
        QMessageBox::information(this, "Erreur", "Cursus inexistant");
    }
}

void DossierEditeur::supprimerCur(){
    try{
    QString s = nomNouvCur->text();
    doss.supprCur(&CM.getCursus(s));
    int i=0;
    cursus->setCurrentIndex(i);
    while(s!=cursus->currentText()){
        cursus->setCurrentIndex(i++);
    }
    cursus->removeItem(cursus->currentIndex());
    nomNouvCur->clear();
    QMessageBox::information(this, "Cursus Supprimé", "Cursus correctement supprimé");
    }
    catch(UTProfilerException e){
        QMessageBox::information(this, "Erreur", "Cursus inexistant");
    }
}

void DossierEditeur::modifierInscription(bool j){
    if (j==0){
        unsigned int i=0;
        while(doss.getInscriptions()[i]->getUV().getCode()!=nomInscrAModif->text()) i++;
        InscriptionEditeur* fen2 = new InscriptionEditeur(&this->doss, doss.getInscriptions()[i]);
        fen2->show();
    }
    else {
        InscriptionEditeur* fen2 = new InscriptionEditeur(&this->doss);
        fen2->show();
    }

}

void DossierEditeur::ajoutInscription(){
    modifierInscription(1);
}

void DossierEditeur::modifierEquivalence(bool j){
    if (j==0){
        unsigned int i=0;
        while(doss.getEquivalences()[i]->getNomEtablissement()!=nomEquiAModif->text()) i++;
        EquivalenceEditeur* fen2 = new EquivalenceEditeur(&this->doss, doss.getEquivalences()[i]);
        fen2->show();}
    else {
        EquivalenceEditeur* fen2 = new EquivalenceEditeur(&this->doss);
        fen2->show();
    }
}

void DossierEditeur::ajoutEquivalence(){
    modifierEquivalence(1);
}

void Dossier::loadInscription(const QString& f){
    fileI=f;

    QFile fin(fileI);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UTProfilerException("Erreur ouverture fichier UV");
    }
    QXmlStreamReader xml(&fin);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "Inscription") continue;
            if(xml.name() == "UV") {
                Inscription *i;
                Semestre s;
                QString code;
                Note note;
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "UV")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "nom") {
                            xml.readNext(); code=xml.text().toString();
                        }
                        if(xml.name() == "semestre") {
                            xml.readNext(); s=StringToSemestre(xml.text().toString());
                        }
                        if(xml.name() == "note") {
                            xml.readNext(); note=StringToNote(xml.text().toString());
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                const UV& u=UVM.getUV(code);
                i=new Inscription(u, s, note);
                addInscription(i);

            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier UV, parser xml");
    }
    xml.clear();
}

void Dossier::loadEquivalence(const QString& f){
    fileE=f;

    QFile fin(fileE);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UTProfilerException("Erreur ouverture fichier UV");
    }
    QXmlStreamReader xml(&fin);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "Equivalence") continue;
            if(xml.name() == "equi") {
                QString nom;
                QString pays;
                unsigned int CS;
                unsigned int TM;
                unsigned int TSH;
                unsigned int SP;
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "equi")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "nomEtablissement") {
                            xml.readNext(); nom=xml.text().toString();
                        }
                        if(xml.name() == "pays") {
                            xml.readNext(); pays=xml.text().toString();
                        }
                        if(xml.name() == "CS") {
                            xml.readNext(); CS=xml.text().toString().toUInt();
                        }
                        if(xml.name() == "TM") {
                            xml.readNext(); TM=xml.text().toString().toUInt();
                        }
                        if(xml.name() == "TSH") {
                            xml.readNext(); TSH=xml.text().toString().toUInt();
                        }
                        if(xml.name() == "SP") {
                            xml.readNext(); SP=xml.text().toString().toUInt();
                        }
                    }
                    xml.readNext();
                }

                Equivalence *e=new Equivalence(nom, pays, CS, TM, TSH, SP);
                addEquivalence(e);

            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier UV, parser xml");
    }
    xml.clear();
}

void Dossier::loadDossier(const QString& f){
    fileD=f;

    QFile fin(fileD);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UTProfilerException("Erreur ouverture fichier UV");
    }
    QXmlStreamReader xml(&fin);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "Dossier") continue;
            if(xml.name() == "unDossier") {
                Dossier& d=Dossier::donneInstance();
                QString nomCursus;
                bool aes;
                bool b2;
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("aes")) {
                    QString val =attributes.value("aes").toString();
                    aes=(val == "true" ? true : false);
                }
                if(attributes.hasAttribute("b2")) {
                    QString val =attributes.value("b2").toString();
                    b2=(val == "true" ? true : false);
                }

                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name()=="unDossier")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name()=="Cursus"){
                            xml.readNext();
                            while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Cursus")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if(xml.name()=="nomCursus"){
                                        xml.readNext(); nomCursus=xml.text().toString();
                                        d.addCursus(&(CM.getCursus(nomCursus)));
                                    }
                                }
                                xml.readNext();
                            }
                        }
                    }
                    xml.readNext();
                }
                d.setAES(aes);
                d.setNivB2(b2);
            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier UV, parser xml");
    }
    xml.clear();
}

void Dossier::saveInscription(){
    QFile newfile(fileI);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("Inscription");
     for(unsigned int i=0; i<nbIns; i++){
         stream.writeStartElement("UV");
         stream.writeTextElement("nom",inscriptions[i]->getUV().getCode());
         stream.writeTextElement("semestre",semestreToString(inscriptions[i]->getSemestre()));
         stream.writeTextElement("note",NoteToString(inscriptions[i]->getResultat()));
         stream.writeEndElement();
     }
     stream.writeEndElement();

     stream.writeEndDocument();
     newfile.close();
     if(stream.hasError()) {
         throw UTProfilerException("Erreur lecteur fichier UV, parser xml");
     }
}

void Dossier::saveEquivalence(){
    QFile newfile(fileE);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("Equivalence");
     for(unsigned int i=0; i<nbEq; i++){
         stream.writeStartElement("equi");
         stream.writeTextElement("nomEtablissement",equivalences[i]->getNomEtablissement());
         stream.writeTextElement("pays",equivalences[i]->getPays());
         QString cr; cr.setNum(equivalences[i]->getEquiCS());
         stream.writeTextElement("CS",cr);
         cr.setNum(equivalences[i]->getEquiTM());
         stream.writeTextElement("TM",cr);
         cr.setNum(equivalences[i]->getEquiTSH());
         stream.writeTextElement("TSH",cr);
         cr.setNum(equivalences[i]->getEquiSP());
         stream.writeTextElement("SP",cr);
         stream.writeEndElement();
     }
     stream.writeEndElement();

     stream.writeEndDocument();
     newfile.close();
     if(stream.hasError()) {
         throw UTProfilerException("Erreur lecteur fichier UV, parser xml");
     }
}

Dossier::~Dossier() {
   delete[] inscriptions;
   delete[] equivalences;
}

void Dossier::saveDossier(){
    QFile newfile(fileD);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("Dossier");
     stream.writeStartElement("unDossier");
     stream.writeAttribute("aes", (getActiviteES())?"true":"false");
     stream.writeAttribute("b2", (getnivB2())?"true":"false");
     stream.writeStartElement("Cursus");
     for (unsigned int i=0; i<nbCur;i++){
         stream.writeTextElement("nomCursus", getCursus()[i]->getNom());
     }

     stream.writeEndElement();
     stream.writeEndElement();
     stream.writeEndElement();

     stream.writeEndDocument();
     newfile.close();
     if(stream.hasError()) {
         throw UTProfilerException("Erreur lecteur fichier UV, parser xml");
     }
}
