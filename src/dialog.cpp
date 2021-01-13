#include "dialog.h"
#include "ui_dialog.h"
#include "tram.h"
#include "ligne.h"
#include "station.h"
#include "reseautram.h"


Dialog::Dialog(const QString&nomFicDepart,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    QFile fichier(nomFicDepart);

    if (!fichier.open(QFile::ReadOnly))
        qDebug()<<"Ouverture du fichier impossible, essayer de mettre les fichiers dans le dossier Build du projet";

    QTextStream FicIn(&fichier);
    QString tmp = FicIn.readLine();

    ui->setupUi(this);

    scene = new QGraphicsScene{this};
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setFixedSize(1800,1000);

    QPen monPen = {Qt::blue};

    d_nombreLignes=tmp.toInt();
    int temps = FicIn.readLine().toInt();
    temps*=1000;

    voyage = new ligne* [d_nombreLignes];
    gestionTram = new reseauTram* [d_nombreLignes];

    QString* FicTab = new QString[d_nombreLignes];
    QString NomLigne;
    QString indiceLigne;

    for (int i = 0 ; i < d_nombreLignes; ++i)
    {
        indiceLigne.setNum(i+1);
        NomLigne = "Ligne" + indiceLigne+".txt";
        FicTab[i] = NomLigne;

    }

    for (int i = 0 ; i < d_nombreLignes; ++i)
    {
    voyage[i] = new ligne{FicTab[i]};
    gestionTram[i] = new reseauTram{voyage[i],FicTab[i], scene};
    voyage[i]->dessiner(scene);
    }
    delete [] FicTab;

    timer = new QTimer{this};
    connect (timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1);

    TempsApp = new QTimer{this};
    connect(TempsApp,SIGNAL(timeout()),this,SLOT(arret()));
    TempsApp->start(temps);

}

Dialog::~Dialog()
{
    for (int i = 0 ; i < d_nombreLignes;++i)
    {
        delete voyage[i];
    }
    delete [] voyage;
    for(int i =0 ; i < d_nombreLignes;++i)
    {
        delete gestionTram[i];
    }
    delete [] gestionTram;


    delete ui;
}

void Dialog::arret()
{

    this->ui->graphicsView->close();
    this->close();
    delete this->ui->graphicsView;
    delete this;
}

