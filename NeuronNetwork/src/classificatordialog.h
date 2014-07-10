#ifndef CLASSIFICATORDIALOG_H
#define CLASSIFICATORDIALOG_H

#include <QDialog>

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

};

#endif // CLASSIFICATORDIALOG_H
