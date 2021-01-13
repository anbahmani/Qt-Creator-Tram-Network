#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w{"FichierDebut.txt"};
    w.show();
    return a.exec();
}
