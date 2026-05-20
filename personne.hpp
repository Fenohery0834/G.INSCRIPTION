#ifndef PERSONNE_HPP
#define PERSONNE_HPP

#include <string>
#include <iostream>

class Personne 
{
private:
    std::string nom;
    std::string prenom;
    int age;
    std::string email;

public:
    
    Personne();
    Personne(const std::string& nom, const std::string& prenom, int age, const std::string& email);

    
    std::string getNom()    const;
    std::string getPrenom() const;
    int         getAge()    const;
    std::string getEmail()  const;

    
    void setNom(const std::string& nom);
    void setPrenom(const std::string& prenom);
    void setAge(int age);
    void setEmail(const std::string& email);

    
    void afficher() const;

    
    bool operator==(const Personne& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Personne& p);
};

#endif 
