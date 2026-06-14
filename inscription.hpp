#ifndef INSCRIPTION_HPP
#define INSCRIPTION_HPP

#include "personne.hpp"
#include <QWidget>
#include <QList>
#include <QString>

namespace Ui { class Inscription; }

class Inscription : public QWidget
{
    Q_OBJECT

public:
    explicit Inscription(QWidget *parent = nullptr);
    ~Inscription();

    // Opérations sur la liste
    void ajouterDebut(const Personne& p);
    void ajouterFin(const Personne& p);
    void insererPosition(const Personne& p, int pos);
    void supprimerDebut();
    void supprimerFin();
    bool desabonner(const QString& email);

    int  nombreInscrits() const;
    bool estInscrit(const QString& email) const;
    const QList<Personne>& liste() const;

private slots:
    void on_btnAjouterDebut_clicked();
    void on_btnAjouterFin_clicked();
    void on_btnInsererPos_clicked();
    void on_btnSupprimerDebut_clicked();
    void on_btnSupprimerFin_clicked();
    void on_btnDesabonner_clicked();
    void on_btnEffacer_clicked();
    void on_searchEdit_textChanged(const QString& text);
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::Inscription   *ui;
    QList<Personne>    inscrits;
    QString            nomEvenement;

    void    rafraichirTable(const QString& filtre = "");
    void    rafraichirStats();
    void    afficherMessage(const QString& msg, bool erreur = false);
    bool    validerFormulaire(QString& nom, QString& prenom, int& age, QString& email);
    void    clearForm();
};

#endif // INSCRIPTION_HPP
