#include "inscription.hpp"
#include "ui_inscription.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QTimer>
#include <stdexcept>

Inscription::Inscription(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Inscription)
    , nomEvenement("Gestionnaire d'Inscriptions")
{
    ui->setupUi(this);

    // Configuration du tableau
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"#", "Prénom", "Nom", "Âge", "Email"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(0, 45);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);

    // Données de démonstration
    inscrits.append(Personne("Razafy",        "Aina",  26, "aina.razafy@gmail.com"));
    inscrits.append(Personne("Andriamaharo",  "Hery",  32, "heryrak@gmail.Com"));
    inscrits.append(Personne("Rakoto",        "Fara",  24, "fara.rakoto@gmail.com"));

    rafraichirTable();
    rafraichirStats();
}

Inscription::~Inscription()
{
    delete ui;
}

void Inscription::ajouterDebut(const Personne& p)
{
    inscrits.prepend(p);
}

void Inscription::ajouterFin(const Personne& p)
{
    inscrits.append(p);
}

void Inscription::insererPosition(const Personne& p, int pos)
{
    if (pos < 0) throw std::out_of_range("Position négative invalide.");
    if (pos >= inscrits.size()) inscrits.append(p);
    else inscrits.insert(pos, p);
}

void Inscription::supprimerDebut()
{
    if (!inscrits.isEmpty()) inscrits.removeFirst();
}

void Inscription::supprimerFin()
{
    if (!inscrits.isEmpty()) inscrits.removeLast();
}

bool Inscription::desabonner(const QString& email)
{
    for (int i = 0; i < inscrits.size(); ++i)
    {
        if (inscrits[i].getEmail() == email)
        {
            inscrits.removeAt(i);
            return true;
        }
    }
    return false;
}

int Inscription::nombreInscrits() const { return inscrits.size(); }

bool Inscription::estInscrit(const QString& email) const
{
    for (const Personne& p : inscrits)
        if (p.getEmail() == email) return true;
    return false;
}

const QList<Personne>& Inscription::liste() const { return inscrits; }


void Inscription::on_btnAjouterDebut_clicked()
{
    QString nom, prenom, email; int age;
    if (!validerFormulaire(nom, prenom, age, email)) return;
    ajouterDebut(Personne(nom, prenom, age, email));
    rafraichirTable(ui->searchEdit->text());
    rafraichirStats();
    afficherMessage(QString("%1 %2 ajouté(e) en tête.").arg(prenom, nom));
    clearForm();
}

void Inscription::on_btnAjouterFin_clicked()
{
    QString nom, prenom, email; int age;
    if (!validerFormulaire(nom, prenom, age, email)) return;
    ajouterFin(Personne(nom, prenom, age, email));
    rafraichirTable(ui->searchEdit->text());
    rafraichirStats();
    afficherMessage(QString("%1 %2 ajouté(e) en fin.").arg(prenom, nom));
    clearForm();
}

void Inscription::on_btnInsererPos_clicked()
{
    QString nom, prenom, email;
    int age;
    if (!validerFormulaire(nom, prenom, age, email)) return;
    int pos = ui->spinPosition->value();
    try
    {
        insererPosition(Personne(nom, prenom, age, email), pos);
    } catch (const std::out_of_range& e) {
        afficherMessage(QString("Erreur : %1").arg(e.what()), true);
        return;
    }
    rafraichirTable(ui->searchEdit->text());
    rafraichirStats();
    afficherMessage(QString("%1 %2 inséré(e) à la position %3.").arg(prenom, nom).arg(pos));
    clearForm();
}

void Inscription::on_btnSupprimerDebut_clicked()
{
    if (inscrits.isEmpty()) { afficherMessage("La liste est vide.", true); return; }
    QString info = inscrits.first().getPrenom() + " " + inscrits.first().getNom();
    supprimerDebut();
    rafraichirTable(ui->searchEdit->text());
    rafraichirStats();
    afficherMessage(info + " retiré(e) de la tête.");
}

void Inscription::on_btnSupprimerFin_clicked()
{
    if (inscrits.isEmpty()) { afficherMessage("La liste est vide.", true); return; }
    QString info = inscrits.last().getPrenom() + " " + inscrits.last().getNom();
    supprimerFin();
    rafraichirTable(ui->searchEdit->text());
    rafraichirStats();
    afficherMessage(info + " retiré(e) de la fin.");
}

void Inscription::on_btnDesabonner_clicked()
{
    QString email;
    QList<QTableWidgetItem*> sel = ui->tableWidget->selectedItems();
    if (!sel.isEmpty())
        email = ui->tableWidget->item(ui->tableWidget->currentRow(), 4)->text();
    else
        email = ui->editEmail->text().trimmed();

    if (email.isEmpty()) { afficherMessage("Sélectionnez une ligne ou saisissez un email.", true); return; }

    QMessageBox box(this);
    box.setWindowTitle("Confirmation");
    box.setText(QString("Désabonner l'inscrit avec l'email :\n%1 ?").arg(email));
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);
    if (box.exec() != QMessageBox::Yes) return;

    if (desabonner(email))
    {
        rafraichirTable(ui->searchEdit->text());
        rafraichirStats();
        afficherMessage(QString("Inscrit(e) (%1) désabonné(e).").arg(email));
    }
    else
    {
        afficherMessage(QString("Aucun inscrit avec l'email : %1").arg(email), true);
    }
}

void Inscription::on_btnEffacer_clicked() { clearForm(); }

void Inscription::on_searchEdit_textChanged(const QString& text)
{
    rafraichirTable(text);
}

void Inscription::on_tableWidget_itemSelectionChanged()
{
    QList<QTableWidgetItem*> sel = ui->tableWidget->selectedItems();
    if (sel.isEmpty()) return;
    int row = ui->tableWidget->currentRow();
    ui->editEmail->setText(ui->tableWidget->item(row, 4)->text());
}


bool Inscription::validerFormulaire(QString& nom, QString& prenom, int& age, QString& email)
{
    nom    = ui->editNom->text().trimmed();
    prenom = ui->editPrenom->text().trimmed();
    age    = ui->spinAge->value();
    email  = ui->editEmail->text().trimmed();

    if (nom.isEmpty() || prenom.isEmpty())
    {
        afficherMessage("Le nom et le prénom sont obligatoires.", true); return false;
    }
    if (!email.contains('@') || !email.contains('.'))
    {
        afficherMessage("Adresse email invalide.", true); return false;
    }
    if (estInscrit(email))
    {
        afficherMessage("Cet email est déjà inscrit.", true); return false;
    }
    return true;
}

void Inscription::clearForm()
{
    ui->editPrenom->clear();
    ui->editNom->clear();
    ui->editEmail->clear();
    ui->spinAge->setValue(25);
    ui->spinPosition->setValue(0);
    ui->editPrenom->setFocus();
}

void Inscription::rafraichirTable(const QString& filtre)
{
    ui->tableWidget->setRowCount(0);
    int index = 0;
    for (const Personne& p : inscrits)
    {
        bool match = filtre.isEmpty()
                     || p.getNom().contains(filtre, Qt::CaseInsensitive)
                     || p.getPrenom().contains(filtre, Qt::CaseInsensitive)
                     || p.getEmail().contains(filtre, Qt::CaseInsensitive);
        if (!match) { ++index; continue; }

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        auto item = [](const QString& txt, Qt::Alignment a = Qt::AlignLeft|Qt::AlignVCenter)
        {
            QTableWidgetItem* it = new QTableWidgetItem(txt);
            it->setTextAlignment(a);
            return it;
        };
        ui->tableWidget->setItem(row, 0, item(QString::number(index + 1), Qt::AlignCenter));
        ui->tableWidget->setItem(row, 1, item(p.getPrenom()));
        ui->tableWidget->setItem(row, 2, item(p.getNom()));
        ui->tableWidget->setItem(row, 3, item(QString::number(p.getAge()), Qt::AlignCenter));
        ui->tableWidget->setItem(row, 4, item(p.getEmail()));
        ++index;
    }
    ui->spinPosition->setMaximum(qMax(0, inscrits.size()));
}

void Inscription::rafraichirStats()
{
    int n = inscrits.size();
    ui->labelNbInscrits->setText(QString::number(n));
    if (n == 0) { ui->labelAgeMoyen->setText("—"); ui->labelDernier->setText("—"); return; }
    double s = 0;
    for (const Personne& p : inscrits) s += p.getAge();
    ui->labelAgeMoyen->setText(QString::number(s / n, 'f', 1));
    ui->labelDernier->setText(inscrits.last().getPrenom() + " " + inscrits.last().getNom());
}

void Inscription::afficherMessage(const QString& msg, bool erreur)
{
    QString color = erreur ? "#c0392b" : "#27ae60";
    ui->labelMessage->setStyleSheet(QString("color: %1; font-weight: bold; font-size: 12px;").arg(color));
    ui->labelMessage->setText(erreur ? "⚠  " + msg : "✔  " + msg);
    QTimer::singleShot(4000, ui->labelMessage, [this]{ ui->labelMessage->clear(); });
}
