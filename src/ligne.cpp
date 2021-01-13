#include "ligne.h"

ligne::ligne::ligne() : t{nullptr},dernier{nullptr}, d_nbStations{0}
{
}

ligne :: ligne(const QString&nomFichier) : t{nullptr},dernier{nullptr}, d_nbStations{0}
{
    QFile fichier(nomFichier);

    if (!fichier.open(QFile::ReadOnly))
        qDebug()<<"Ouverture du fichier impossible, essayer de mettre les fichiers dans le dossier Build du projet";

    QTextStream in(&fichier);

    QString tmp = in.readLine();
    d_nbStations = tmp.toInt();

    int r, v, b;

    tmp = in.readLine();
    r = tmp.toInt();
    tmp = in.readLine();
    v = tmp.toInt();
    tmp = in.readLine();
    b = tmp.toInt();

    couleurLigne = QColor(r, v, b);

    if(d_nbStations == 0)
        return;

    station* tabstations = new station[d_nbStations];

    unsigned int i = 0;

    while(i<d_nbStations)
    {
        tabstations[i].d_nom = in.readLine();
        tmp = in.readLine();
        tabstations[i].d_x = tmp.toInt();
        tmp = in.readLine();
        tabstations[i].d_y = tmp.toInt();
        tmp = in.readLine();
        tabstations[i].TempsArret = tmp.toInt();
        ++i;
    }

    t = new station(tabstations[0].d_nom, tabstations[0].d_x, tabstations[0].d_y,tabstations[0].TempsArret);
    auto pre = t;
    station* na = nullptr;
    i = 1;

    while(i<d_nbStations)
    {
        na = new station(tabstations[i].d_nom, tabstations[i].d_x, tabstations[i].d_y,tabstations[i].TempsArret);
        pre->suivant = na;
        pre->d_distance = pre->distanceSuivant();
        pre = na;
        ++i;
    }
    na->aller = false;
    i = d_nbStations - 2;

    while(i>0)
    {
        na = new station(tabstations[i].d_nom, tabstations[i].d_x, tabstations[i].d_y,tabstations[i].TempsArret);
        na->aller = false;
        pre->suivant = na;
        pre->d_distance = pre->distanceSuivant();
        pre = na;
        --i;
    }
    na->suivant = t;
    na->d_distance = na->distanceSuivant();
    dernier = na;

    delete [] tabstations;
}

ligne :: ~ligne()
{
    station* a = t;
    while(a != dernier)
    {
        t=t->suivant;
        delete a;
        a = t;
    }
    delete a;
}

void ligne::ligneDebug() const
{
    station* c = t->suivant;
        station* prec = t;

        if (t == nullptr)
        {
            return;
        }
        qDebug()<<prec->d_nom<<" "<<prec->d_x<<" , "<<prec->d_y;

        for(unsigned int i=0; i<d_nbStations-1; ++i)
        {
            qDebug()<<c->d_nom<<" "<<c->d_x<<" , "<<c->d_y;
            c = c->suivant;
            prec = prec->suivant;
        }

}
void ligne::dessiner(QGraphicsScene* scene) const
{
    station* crt = t;
    QPen pen{couleurLigne,4,Qt::SolidLine};
    QRectF stat{t->d_x-3,t->d_y-3,6,6};
    scene->addRect(stat,pen);

    for (unsigned int i = 0 ; i < d_nbStations-1; ++i)
    {
        QLineF line{crt->d_x,crt->d_y,crt->suivant->d_x,crt->suivant->d_y};
        QRectF statSuiv{crt->suivant->d_x-3,crt->suivant->d_y-3,6,6};

        scene->addLine(line,pen);
        scene->addRect(statSuiv,pen);
        crt=crt->suivant;
    }
}

