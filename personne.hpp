#ifndef PERSONNE_HPP
#define PERSONNE_HPP

#include <QString>

class Personne
{
public:
    Personne();
    Personne(const QString& nom, const QString& prenom, int age, const QString& email);

    QString getNom()    const;
    QString getPrenom() const;
    int     getAge()    const;
    QString getEmail()  const;

    void setNom(const QString& n);
    void setPrenom(const QString& p);
    void setAge(int a);
    void setEmail(const QString& e);

    bool operator==(const Personne& other) const;

private:
    QString nom;
    QString prenom;
    int     age;
    QString email;
};

#endif // PERSONNE_HPP
