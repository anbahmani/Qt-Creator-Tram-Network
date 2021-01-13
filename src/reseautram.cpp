#include "reseautram.h"

reseauTram::reseauTram(ligne* lgn,const QString& nomFichier, QGraphicsScene* scn) :
    tramTete{nullptr}, d_nbTram{lgn->d_nbStations}
{
    QFile fichier(nomFichier);
    if (!fichier.open(QFile::ReadOnly))
        qDebug()<<"Ouverture du fichier impossible, essayer de mettre les fichiers dans le dossier Build du projet";
    QTextStream in(&fichier);
    QString tmp;
    if(d_nbTram == 0)
        return;
      for(unsigned int i = 0; i < (d_nbTram + 1) * 4 ; ++i )
      {
          tmp = in.readLine();
      }
      tmp = in.readLine();
    station* stationCourante = lgn->t;
    tramTete = new Tram{lgn,stationCourante, tmp.toDouble()};
    Tram* tramCourant = tramTete;
    tramTete->setZValue(1);
    scn->addItem(tramTete);

    for(int unsigned i=1; i<d_nbTram; ++i)
    {
        stationCourante = stationCourante->suivant;
        tmp = in.readLine();
        tramCourant->suivant = new Tram{lgn,stationCourante, tmp.toDouble()};
        tramCourant = tramCourant->suivant;
        tramCourant->setZValue(1);
        scn->addItem(tramCourant);
    }

    tramCourant->suivant = tramTete;
}

reseauTram::~reseauTram()
{
    Tram* a = tramTete;

    for(int unsigned i =0; i<d_nbTram; ++i)
    {
        tramTete = tramTete->suivant;
        delete a;
        a = tramTete;
    }
    delete a;
}










