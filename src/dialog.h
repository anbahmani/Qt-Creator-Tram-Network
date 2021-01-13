#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>

#include "ligne.h"
#include "station.h"
#include "reseautram.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(const QString&nomFicDepart,QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QGraphicsScene* scene;
    QTimer* timer;
    ligne** voyage;
    int d_nombreLignes;
    reseauTram** gestionTram;

    QTimer* TempsApp;
private slots :
    void arret();

};
#endif // DIALOG_H
