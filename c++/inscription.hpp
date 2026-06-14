#ifndef INSCRIPTION_HPP
#define INSCRIPTION_HPP

#include "personne.hpp"
#include <list>
#include <string>

class Inscription 
{
private:
    std::list<Personne> inscrits;  
    std::string         nomEvenement;

public:
    // Constructeur
    explicit Inscription(const std::string& evenement = "Événement");

    
    void ajouterDebut(const Personne& p);           
    void ajouterFin(const Personne& p);             
    void insererPosition(const Personne& p, int pos); 

    
    void supprimerDebut();                          
    void supprimerFin();                            
    void desabonner(const std::string& email);      

    //Consultation 
    void afficherListe()    const;
    int  nombreInscrits()   const;
    bool estInscrit(const std::string& email) const;

    // Itérateurs (accès externe)
    std::list<Personne>::iterator       begin();
    std::list<Personne>::iterator       end();
    std::list<Personne>::const_iterator cbegin() const;
    std::list<Personne>::const_iterator cend()   const;
};

#endif 