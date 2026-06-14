#include "inscription.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("Fusion");

    Inscription fenetre;
    fenetre.setWindowTitle("Gestionnaire d'Inscriptions");
    fenetre.resize(980, 660);
    fenetre.show();

    return app.exec();
}
