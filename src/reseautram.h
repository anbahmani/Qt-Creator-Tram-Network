#ifndef RESEAUTRAM_H
#define RESEAUTRAM_H

#include <QFile>
#include <QColor>
#include <QGraphicsScene>
#include <QTextStream>

#include "tram.h"
#include "ligne.h"
#include "station.h"
#include "tram.h"

class reseauTram
{
public:
    reseauTram(ligne* lgn, QGraphicsScene* scn, double v);
    reseauTram(ligne* lgn,const QString& nomFichier, QGraphicsScene* scn);
    ~reseauTram();
private:
    Tram* tramTete;
    int unsigned d_nbTram;
};

#endif // RESEAUTRAM_H
