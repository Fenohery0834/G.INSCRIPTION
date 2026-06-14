#include "personne.hpp"

Personne::Personne()
    : nom(""), prenom(""), age(0), email("") {}

Personne::Personne(const QString& nom, const QString& prenom, int age, const QString& email)
    : nom(nom), prenom(prenom), age(age), email(email) {}

QString Personne::getNom()    const { return nom; }
QString Personne::getPrenom() const { return prenom; }
int     Personne::getAge()    const { return age; }
QString Personne::getEmail()  const { return email; }

void Personne::setNom(const QString& n)    { nom = n; }
void Personne::setPrenom(const QString& p) { prenom = p; }
void Personne::setAge(int a)               { age = a; }
void Personne::setEmail(const QString& e)  { email = e; }

bool Personne::operator==(const Personne& other) const
{
    return nom == other.nom && prenom == other.prenom && email == other.email;
}
