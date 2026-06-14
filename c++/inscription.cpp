#include "inscription.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iomanip>


Inscription::Inscription(const std::string& evenement) : nomEvenement(evenement) {}



void Inscription::ajouterDebut(const Personne& p) 
{
    inscrits.push_front(p);
    std::cout << "[+] " << p.getPrenom() << " " << p.getNom()
              << " inscrit(e) en tête de liste.\n";
}

void Inscription::ajouterFin(const Personne& p) 
{
    inscrits.push_back(p);
    std::cout << "[+] " << p.getPrenom() << " " << p.getNom()
              << " inscrit(e) en fin de liste.\n";
}

void Inscription::insererPosition(const Personne& p, int pos) 
{
    if (pos < 0) throw std::out_of_range("Position négative invalide.");

    
    auto it = inscrits.begin();
    int  i  = 0;
    while (it != inscrits.end() && i < pos) 
    {
        ++it;
        ++i;
    }
    inscrits.insert(it, p);
    std::cout << "[+] " << p.getPrenom() << " " << p.getNom()
              << " inséré(e) à la position " << pos << ".\n";
}



void Inscription::supprimerDebut() 
{
    if (inscrits.empty()) 
    {
        std::cout << "[!] Liste vide, impossible de supprimer en tête.\n";
        return;
    }
    std::cout << "[-] " << inscrits.front().getPrenom() << " "
              << inscrits.front().getNom() << " retiré(e) de la tête.\n";
    inscrits.pop_front();
}

void Inscription::supprimerFin() 
{
    if (inscrits.empty()) 
    {
        std::cout << "[!] Liste vide, impossible de supprimer en queue.\n";
        return;
    }
    std::cout << "[-] " << inscrits.back().getPrenom() << " "
              << inscrits.back().getNom() << " retiré(e) de la queue.\n";
    inscrits.pop_back();
}

void Inscription::desabonner(const std::string& email) 
{
    // Recherche via itérateur et suppression avec erase
    auto it = std::find_if(inscrits.begin(), inscrits.end(),
                           [&email](const Personne& p) {
                               return p.getEmail() == email;
                           });

    if (it != inscrits.end()) 
    {
        std::cout << "[-] " << it->getPrenom() << " " << it->getNom()
                  << " désabonné(e) (email : " << email << ").\n";
        inscrits.erase(it);
    } 
    else 
    {
        std::cout << "[!] Aucun inscrit avec l'email : " << email << "\n";
    }
}



void Inscription::afficherListe() const 
{
    const auto bord = [](const std::string& gauche,
                         const std::string& intersection,
                         const std::string& droite,
                         const std::vector<int>& largeurs) 
    {
        const std::string trait = u8"─";
        std::string ligne = gauche;
        for (std::size_t i = 0; i < largeurs.size(); ++i) 
        {
            for (int j = 0; j < largeurs[i]; ++j) 
            {
                ligne += trait;
            }
            ligne += (i + 1 < largeurs.size() ? intersection : droite);
        }
        return ligne;
    };

    const std::vector<int> colonnes = {15, 15, 5, 25};

    std::cout << "\n  Liste des inscrits – " << nomEvenement << "\n";
    std::cout << "  Nombre d'inscrits : " << inscrits.size() << "\n";
    std::cout << bord(u8"┌", u8"┬", u8"┐", colonnes) << "\n";
    std::cout << "│ " << std::left
              << std::setw(13) << "Prénom" << " │ "
              << std::setw(13) << "Nom"    << " │ "
              << std::setw(3)  << "Âge"    << " │ "
              << std::setw(23) << "Email"  << " │\n";
    std::cout << bord(u8"├", u8"┼", u8"┤", colonnes) << "\n";

    for (auto cit = inscrits.cbegin(); cit != inscrits.cend(); ++cit) 
    {
        cit->afficher();
    }

    std::cout << bord(u8"└", u8"┴", u8"┘", colonnes) << "\n\n";
}

int Inscription::nombreInscrits() const 
{
    return static_cast<int>(inscrits.size());
}

bool Inscription::estInscrit(const std::string& email) const 
{
    return std::any_of(inscrits.cbegin(), inscrits.cend(),
                       [&email](const Personne& p) 
                       {
                           return p.getEmail() == email;
                       });
}



//std::list<Personne>::iterator       Inscription::begin()        { return inscrits.begin(); }
std::list<Personne>::iterator       Inscription::begin()        { return inscrits.begin(); }
std::list<Personne>::iterator       Inscription::end()          { return inscrits.end(); }
std::list<Personne>::const_iterator Inscription::cbegin() const { return inscrits.cbegin(); }
std::list<Personne>::const_iterator Inscription::cend()   const { return inscrits.cend(); }