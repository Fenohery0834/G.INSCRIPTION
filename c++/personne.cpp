#include "personne.hpp"
#include <iomanip>


Personne::Personne() : nom(""), prenom(""), age(0), email("") {}


Personne::Personne(const std::string& nom, const std::string& prenom, int age, const std::string& email)
    : nom(nom), prenom(prenom), age(age), email(email) {}


std::string Personne::getNom()    const { return nom; }
std::string Personne::getPrenom() const { return prenom; }
int         Personne::getAge()    const { return age; }
std::string Personne::getEmail()  const { return email; }


void Personne::setNom(const std::string& n)    { nom = n; }
void Personne::setPrenom(const std::string& p) { prenom = p; }
void Personne::setAge(int a)                   { age = a; }
void Personne::setEmail(const std::string& e)  { email = e; }


void Personne::afficher() const {
    std::cout << "│ " << std::left
              << std::setw(13) << prenom << " │ "
              << std::setw(13) << nom    << " │ "
              << std::setw(3)  << age    << " │ "
              << std::setw(23) << email  << " │" << std::endl;
}


bool Personne::operator==(const Personne& other) const {
    return nom    == other.nom
        && prenom == other.prenom
        && email  == other.email;
}


std::ostream& operator<<(std::ostream& os, const Personne& p) {
    os << p.prenom << " " << p.nom
       << " (age: " << p.age << ", email: " << p.email << ")";
    return os;
}