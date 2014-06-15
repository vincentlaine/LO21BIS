#ifndef FILIERE_H
#define FILIERE_H

enum filieres {MPI, AVI, FQI, MARS, MIT, IDI, CMI, MOPS, PIL, SRI, ICSI, STRIE, FDD, ADEL, STI, SR, AIE, BM, BB, CIB, IAA, AI, CPI, QSE, TE};

class Filiere
{
private :
    filieres nom;
public:
    Filiere(filieres f): nom(f) {}
    filieres getFiliere() const { return nom; }
};

#endif // FILIERE_H
