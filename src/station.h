#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED

#include <QString>
#include <QGraphicsScene>
#include <cmath>

class station{
    friend class ligne;
    friend class reseauTram;
    friend class Tram;
    friend class dessin;
    friend class Dialog;
public:
    station();
    station(const QString&nom, const double&x, const double&y,const int&temps);
    double x() const;
    double y() const;

    double xSuivant() const;
    double ySuivant() const;

    double distanceSuivant() const;

private:
    QString d_nom;
    double d_x;
    double d_y;
    double d_distance;
    int TempsArret;
    bool aller;
    station* suivant;
};

#endif // STATION_H_INCLUDED
