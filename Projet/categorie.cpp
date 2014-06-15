#include "categorie.h"

using namespace std;

QTextStream& operator<<(QTextStream& f, const Categories& c){
    return f<<c.getCode()<<": "<<c.getTitre();
}
