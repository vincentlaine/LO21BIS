#include "Cursus.h"

void Curs::addUV(QString u){
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
