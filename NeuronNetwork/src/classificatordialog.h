#ifndef CLASSIFICATORDIALOG_H
#define CLASSIFICATORDIALOG_H

#include <QDialog>

#define CLASS_SECTION 0
#define NETWORK_RESPONSE_SECTION 1
#define STATUS_SECTION 2

namespace Ui {
class ClassificatorDialog;
}

class ClassificatorDialog : public QDialog {
    Q_OBJECT

private:
    Ui::ClassificatorDialog *_ui;

public:
    explicit ClassificatorDialog(QWidget *parent = 0);
    ~ClassificatorDialog();

    void set_data(QList<QPair<QString, QString> > data);
};

#endif // CLASSIFICATORDIALOG_H
