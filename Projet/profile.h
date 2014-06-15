#ifndef PROFILE_H
#define PROFILE_H
#include <QString>
#include <iostream>
#include "Inscription.h"
#include "cursus.h"

class Profile{
private:
    Inscription** inscriptions;
    Cursus cursusActuel;
    Cursus cursusVise;
public:
    Profil();
    Inscription** getInscription()
    {
        return this->inscriptions;
    }
    Cursus getCursusActuel()
    {
        return this->cursusActuel;
    }
    Cursus getCursusVise(){
        return this->cursusVise;
    }


};


#endif // PROFILE_H
