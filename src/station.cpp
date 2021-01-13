#include "station.h"

station::station (const QString&nom, const double&x, const double&y,const int& temps):
    d_nom{nom}, d_x{x}, d_y{y}, d_distance{0.0},TempsArret{temps},aller{true}, suivant{nullptr}
{}

station::station():
    d_nom{""}, d_x{0}, d_y{0}, d_distance{0.0}, suivant{nullptr}
{
}

double station::x() const
{
    return d_x;
}

double station::y() const
{
    return d_y;
}

double station::xSuivant() const
{
    return suivant->x();
}

double station::ySuivant() const
{
    return suivant->y();
}

double station::distanceSuivant() const
{
    double x = suivant->x() - d_x;
    double y = suivant->y() - d_y;
    return sqrt(x*x + y*y);
}
