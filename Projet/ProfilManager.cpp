#include "ProfilManager.h"

using namespace std;

void ProfilManager::save_Profil(const QString& f)
{
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw Exception(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("profils");
     for(unsigned int i=0; i<nbUV; i++){
         stream.writeStartElement("profil");
         stream.writeAttribute("automne", (uvs[i]->ouvertureAutomne())?"true":"false");
         stream.writeAttribute("printemps", (uvs[i]->ouverturePrintemps())?"true":"false");
         stream.writeTextElement("code",uvs[i]->getCode());
         stream.writeTextElement("titre",uvs[i]->getTitre());
         QString cr; cr.setNum(uvs[i]->getNbCredit());
         stream.writeTextElement("credits",cr);
         stream.writeTextElement("categorie",CategorieToString(uvs[i]->getCategorie()));
         stream.writeEndElement();
     }
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();

}

void ProfilManager::load_Profil(const QString& f)
{
    if (file!=f) this->~ProfilManager();
    file=f;

    QFile fin(file);

    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw Exception("Erreur ouverture fichier Profil");
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
        if(token == QXmlStreamReader::StartElement) {

            if(xml.name() == "profils") continue;

            if(xml.name() == "profil") {
                QString code;
                QString titre;
                unsigned int nbCredits;
                Categorie cat;
                bool automne=false;
                bool printemps=false;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that uvs has attribute. */
                if(attributes.hasAttribute("automne")) {
                    QString val =attributes.value("automne").toString();
                    automne=(val == "true" ? true : false);
                }
                if(attributes.hasAttribute("printemps")) {
                    QString val =attributes.value("printemps").toString();
                    printemps=(val == "true" ? true : false);
                }

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named uv.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "uv")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found code.
                        if(xml.name() == "code") {
                            xml.readNext(); code=xml.text().toString();
                        }
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        // We've found credits.
                        if(xml.name() == "credits") {
                            xml.readNext(); nbCredits=xml.text().toString().toUInt();
                        }
                        // We've found categorie
                        if(xml.name() == "categorie") {
                            xml.readNext(); cat=StringToCategorie(xml.text().toString());
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                ajouterUV(code,titre,nbCredits,cat,automne,printemps);

            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw Exception("Erreur lecteur fichier Profil, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
}
