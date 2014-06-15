#ifndef PROFILMANAGER_H
#define PROFILMANAGER_H
#include "Inscription.h"

class ProfilManager{
private:
    Inscriptions** profils;
    unsigned int nb_profils;
    unsigned int nb_Max_Profils;
    Inscriptions** simulations;
    unsigned int nb_simu;
    unsigned int nb_max_Simu;
public:
    ProfilManager();
    void add_Profil(Inscriptions** Profil);
    Inscriptions** getProfil(){
        return this->profils;
    }
    Inscriptions** add_Simu(Inscriptions** simu);
    Inscriptions** get_Simu()
    {
     return this->simulations;
     }
    load_Profil();
    save_Profil();
    load_Simu();
    save_Simu();

};

#endif // PROFILMANAGER_H
