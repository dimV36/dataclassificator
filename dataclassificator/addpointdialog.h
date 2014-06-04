#ifndef ADDPOINTDIALOG_H
#define ADDPOINTDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class AddPointDialog;
}

class AddPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointDialog(QWidget *parent = 0);
    ~AddPointDialog();

private:
    Ui::AddPointDialog *_ui;

public:
    double get_x() const;
    double get_y() const;
};

#endif // ADDPOINTDIALOG_H
