#include "tram.h"

Tram::Tram(ligne* l ,station* sta, double v) :
    vitesse{v}, diffADU{0}, stationDepart{sta}, TimeTo{QTime::currentTime()}, principale{l},
    suivant{nullptr}
{
    d_x = stationDepart->x();
    d_y = stationDepart->y();

    taille = QSize(14, 14);
    position = QPointF(-7, -7);

    setPos(mapFromParent(0, 0));
}

QRectF Tram::boundingRect() const
{
    return QRectF(position , QSize(14, 14));
}

void Tram::paint(QPainter *peintre, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF tram = boundingRect();
    QBrush brush{Qt::yellow};

    if(stationDepart->aller)
       {
          brush.setColor(Qt::lightGray);
       }
       else{
            brush.setColor(Qt::black);
       }
      peintre->fillRect(tram, brush);
      peintre->drawRect(tram);

}

void Tram::advance(int phase)
{
    if (!phase) return;

    if(diffT()>diffADU && ADU() && distanceTramSuivant()<50)
    {
        diffADU = diffT();
        TimeTo = QTime::currentTime().addSecs(stationDepart->TempsArret);
    }
    else if(diffT()>diffADU)
    {
        diffADU = 0;
        double dt = vitesse*diffT();
        double p = dt/ stationDepart->distanceSuivant();

        if(dt>=0)
        {
            if(p<1)
            {
                d_x = p*stationDepart->xSuivant() + (1-p) * stationDepart->x();
                d_y = p*stationDepart->ySuivant() + (1-p) * stationDepart->y();
            }
            else
            {
                d_x = stationDepart->xSuivant();
                d_y = stationDepart->ySuivant();

                stationDepart = stationDepart->suivant;

                TimeTo = QTime::currentTime().addSecs(stationDepart->TempsArret);
            }
        }
        setPos(d_x, d_y);
    }
}

double Tram::x() const
{
    return d_x;
}

double Tram::xSuiv() const
{
    return suivant->x();
}

double Tram::y() const
{
    return d_y;
}

double Tram::ySuiv() const
{
    return suivant->y();
}

bool Tram::tramSuivantProche() const
{
    return suivant->stationDepart->xSuivant()==stationDepart->xSuivant() && suivant->stationDepart->ySuivant()==stationDepart->ySuivant();
}

bool Tram::arretSuivantOccupee() const
{
    return xSuiv()==stationDepart->xSuivant() && ySuiv()==stationDepart->ySuivant();
}

bool Tram::ADU() const
{
    return tramSuivantProche() || arretSuivantOccupee();
}

double Tram::diffT() const
{
    double tmp = TimeTo.msecsTo(QTime::currentTime());
    tmp = tmp/1000;
    return tmp;
}

double Tram::distanceTramSuivant() const
{
    double a=(x()-xSuiv()) , b=(y()-ySuiv());
    double dist = sqrt((a*a)+(b*b));
    return dist;
}
