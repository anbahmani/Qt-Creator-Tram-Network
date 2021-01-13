#ifndef LIGNE_H_INCLUDED
#define LIGNE_H_INCLUDED

#include <QColor>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QLine>
#include <QGraphicsScene>
#include <QDebug>

#include "station.h"

class ligne{
    friend class reseauTram;
    friend class Tram;
    friend class Dialog;
public:
    ligne();
    ligne(const QString&nomFichier);
    ~ligne();

    void ligneDebug() const;
    void dessiner(QGraphicsScene* scene) const;
    double distanceTramSuivant() const;
private:
    station* t;
    station* dernier;
    unsigned int d_nbStations;
    QColor couleurLigne;
};

#endif // LIGNE_H_INCLUDED
