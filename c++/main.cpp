#include <iostream>
#include <limits>
#include "personne.hpp"
#include "inscription.hpp"

using namespace std;

// Fonction utilitaire pour vider le tampon d'entrée
void viderBuffer() 
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Fonction pour saisir les informations d'une personne
Personne saisirPersonne() 
{
    string nom, prenom, email;
    int age;

    cout << "Nom : "; cin >> nom;
    cout << "Prénom : "; cin >> prenom;
    cout << "Âge : "; 
    while (!(cin >> age) || age < 1 || age > 120) 
    {
        cout << "[!] Âge invalide (1-120). Réessayez : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Email : "; cin >> email;
    
    return Personne(nom, prenom, age, email);
}

int main() 
{
    Inscription event("Gestionnaire d'Inscriptions");
    int choix = -1;

    while (choix != 0) 
    {
        cout << "\n MENU De GESTION \n";
        cout << "1. Afficher la liste\n";
        cout << "2. Ajouter au début\n";
        cout << "3. Ajouter à la fin\n";
        cout << "4. Insérer à une position spécifique\n";
        cout << "5. Supprimer par email (désabonner)\n";
        cout << "6. Supprimer le premier\n";
        cout << "7. Supprimer le dernier\n";
        cout << "0. Quitter\n";
        cout << "Votre choix : ";
        
        if (!(cin >> choix)) 
        {
            cout << "[!] Erreur de saisie. Veuillez entrer un nombre.\n";
            cin.clear();
            viderBuffer();
            continue;
        }
        viderBuffer(); // vide le '\n' résiduel après lecture du choix

        switch (choix) 
        {
            case 1:
                event.afficherListe();
                break;

            case 2:
                cout << "\nSaisie de la personne :\n";
                event.ajouterDebut(saisirPersonne());
                break;

            case 3:
                cout << "\nSaisie de la personne :\n";
                event.ajouterFin(saisirPersonne());
                break;

            case 4: 
            {
                int pos;
                cout << "\nSaisie de la personne :\n";
                Personne p = saisirPersonne();
                cout << "Position d'insertion (0 = début) : ";
                cin >> pos;
                try 
                {
                    event.insererPosition(p, pos);
                } catch (const exception& e) {
                    cout << "Erreur : " << e.what() << endl;
                }
                break;
            }

            case 5: 
            {
                string email;
                cout << "Entrez l'email de la personne à supprimer : ";
                cin >> email;
                event.desabonner(email);
                break;
            }

            case 6:
                event.supprimerDebut();
                break;

            case 7:
                event.supprimerFin();
                break;

            case 0:
                cout << "Fermeture du programme...\n";
                break;

            default:
                cout << "Choix invalide !\n";
        }
    }

    return 0;
}