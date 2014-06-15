#include "CursusManager.h"

QString CategorieCursusToString(CategorieCursus c){
    switch(c){
    case TC: return "TC";
    case Filiere: return "Filiere";
    case Cursus: return "Cursus";
    case HuTech: return "HuTech";
    case Mineur: return "Mineur";
    case autre:return "autre";
    default: throw Exception("erreur, categorie non traitee",__FILE__,__LINE__);
    }
}

CategorieCursus StringToCategorieCursus(const QString& str){
    if (str=="TC") return TC;
    else
    if (str=="Cursus") return Cursus;
    else
    if (str=="Filiere") return Filiere;
    else
    if (str=="HuTech") return HuTech;
    else
    if (str=="Mineur") return Mineur;
    if (str=="autre")return autre;
    else {
        throw Exception(QString("erreur, StringToCategorie, categorie ")+str+" inexistante");
    }
}

const Curs* StringToCursus(const CursusManager& m, const QString& str){
    Curs* cu=m.trouverCursus(str);
    if (cu==0) throw Exception("Cursus non existant");
    return cu;
}

QString CursusToString(Curs cu){
    return cu.getNom();
}

CursusManager::CursusManager():mesCursus(new Curs*[10]),nbCursus(0),nbMaxCursus(10),file(""){}

Curs* CursusManager::trouverCursus(const QString &c) const{
    for(unsigned int i=0; i<nbCursus;i++){
        if (mesCursus[i]->nom==c) return mesCursus[i];
    };
    return 0;

}

CursusManager::~CursusManager(){
    for(unsigned int i=0; i<nbCursus; i++) delete mesCursus[i];
    delete[] mesCursus;
}

void CursusManager::load(const QString& f){
    file=f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw Exception("Erreur ouverture fichier UV");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement){
            // If it's named uvs, we'll go to the next.
            if(xml.name() == "Cursus") continue;
            // If it's named uv, we'll dig the information from there.
            if(xml.name() == "unCursus") {
                QString nom;
                CategorieCursus cat;
                static QString* uvs=new QString[2];
                unsigned int nUV=0; //nb d'UV
                unsigned int nMUV=2;//nb MAX d'UV
                QString codeUV;
                unsigned int nbCS;
                unsigned int nbTM;
                unsigned int nbTSH;
                unsigned int nbSP;
                const Curs* p;
                QString* newtab;
                unsigned int i;

                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "unCursus")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found code.
                        if(xml.name() == "nom") {
                            xml.readNext(); nom=xml.text().toString();
                        }
                        if(xml.name()=="categorie"){
                            xml.readNext(); cat=StringToCategorieCursus(xml.text().toString());
                        }
                        if(xml.name() == "CS") {
                            xml.readNext(); nbCS=xml.text().toString().toUInt();
                        }
                        if(xml.name() == "TM") {
                            xml.readNext(); nbTM=xml.text().toString().toUInt();
                        }
                        if(xml.name() == "TSH") {
                            xml.readNext(); nbTSH=xml.text().toString().toUInt();
                        }
                        if(xml.name() == "SP") {
                            xml.readNext(); nbSP=xml.text().toString().toUInt();
                        }
                        if(xml.name()=="UVs"){
                                xml.readNext();
                                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "UVs")) {
                                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                        if(xml.name()=="uv"){
                                            xml.readNext();codeUV=xml.text().toString();
                                            uvs[nUV++]=codeUV;
                                        }
                                        if (nUV==nMUV){
                                            newtab=new QString[nMUV+10];
                                            for(i=0; i<nUV; i++) newtab[i]=uvs[i];
                                            nMUV+=10;
                                            QString* old=uvs;
                                            uvs=newtab;
                                            delete[] old;
                                        }
                                    }
                                    xml.readNext();
                               }
                        }
                    }
                    xml.readNext();

                }
                this->ajouterCursus(nom, uvs, nUV, cat, nbCS, nbTM, nbTSH, nbSP);
                nUV=0;
                QString* old=uvs;
                uvs=new QString[10];
                delete[] old;
            }//fin unCursus
        }
    }
    if(xml.hasError()) {
        throw Exception("Erreur lecteur fichier UV, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
}

void CursusManager::addItem(Curs* cu){
        if (nbCursus==nbMaxCursus){
                Curs** newtab=new Curs*[nbMaxCursus+10];
                for(unsigned int i=0; i<nbCursus; i++) newtab[i]=mesCursus[i];
                nbMaxCursus+=10;
                Curs** old=mesCursus;
                mesCursus=newtab;
                delete[] old;
        }
        mesCursus[nbCursus++]=cu;
}

void CursusManager::ajouterCursus(const QString n, const QString* t, unsigned int nbU, CategorieCursus c, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP){
    if (trouverCursus(n)) throw Exception(QString("erreur, CursusManager, Cursus")+n+QString("déja existant"));
    Curs* newcursus=new Curs(n,c,CS,TM,TSH,SP);

    for(unsigned int i=0;i<nbU;i++){
        newcursus->addUV(t[i]);
    }
    addItem(newcursus);
    return;
}

Curs* CursusManager::getCursus(const QString& nom){
        Curs* cu=trouverCursus(nom); //si le nom n'est pas trouvé la fonction trouverCursus retourne 0
    if (!cu) throw Exception("erreur, CursusManager, Cursus inexistant",__FILE__,__LINE__);
        return cu;
}

const Curs* CursusManager::getCursus(const QString& nom) const {
    return const_cast<CursusManager*>(this)->getCursus(nom);
}

CursusManager::Handler CursusManager::handler=Handler();

CursusManager* CursusManager::getInstance(){
    if (!handler.instance) handler.instance = new CursusManager; /* instance créée une seule fois lors de la première utilisation*/
    return handler.instance;
}

void CursusManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

void CursusManager::save(){
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw Exception(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
        stream.writeStartElement("Cursus");
            for(unsigned int i=0; i<nbCursus; i++){
                    stream.writeStartElement("unCursus");
                    stream.writeTextElement("nom",mesCursus[i]->getNom());
                    stream.writeTextElement("categorie",CategorieCursusToString(mesCursus[i]->getCategorie()));
                    QString cr;  cr.setNum(mesCursus[i]->getCredCS());
                    stream.writeTextElement("CS",cr);
                    cr.setNum(mesCursus[i]->getCredTM());
                    stream.writeTextElement("TM", cr);
                    cr.setNum(mesCursus[i]->getCredTSH());
                    stream.writeTextElement("TSH", cr);
                    cr.setNum(mesCursus[i]->getCredSP());
                    stream.writeTextElement("SP", cr);
                    stream.writeStartElement("UVs");
                        for(unsigned int j=0; j<mesCursus[i]->getNbUV();j++){
                            const QString* tabTemp=mesCursus[i]->getTabUV();
                            stream.writeTextElement("uv",tabTemp[j]);
                        }
                    stream.writeEndElement();
                stream.writeEndElement();
            }
        stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();
}

void CursusManager::supprimerCursus(const Curs& cu){
    unsigned int i;
    for(i=0; i<nbCursus; i++)
            if (cu.getNom()==mesCursus[i]->getNom()) break;
    if (i==nbCursus) Exception("Erreur, Cursus inexistant ne peut être supprimée");
    for(unsigned int j=i; j<nbCursus; j++)
        mesCursus[j]=mesCursus[j+1];
    nbCursus--;
}
