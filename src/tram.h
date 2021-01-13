#ifndef TRAM_H
#define TRAM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include <cmath>
#include <QPoint>
#include <QTime>
#include <QSize>

#include "station.h"
#include "ligne.h"

class Tram : public QGraphicsItem
{
    friend class reseauTram;
public:

    Tram(ligne* l ,station* sta, double v);

    QRectF boundingRect() const override;
    void paint(QPainter *peintre, const QStyleOptionGraphicsItem *option = nullptr, QWidget *widget = nullptr) override;

    double x() const;
    double xSuiv() const;
    double y() const;
    double ySuiv() const;

    double diffT() const;
    double distanceTramSuivant() const;

    bool tramSuivantProche() const;
    bool arretSuivantOccupee() const;
    bool ADU() const;

protected:
    void advance(int phase) override;

private :
    double vitesse;
    double diffADU;

    int d_x;
    int d_y;

    QPointF position;
    QSize taille;
    station* stationDepart;
    QTime TimeTo;

    ligne* principale;
    Tram* suivant;
};

#endif // TRAM_H
