#include "classificator.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Classificator w;
    w.show();

    return a.exec();
}
