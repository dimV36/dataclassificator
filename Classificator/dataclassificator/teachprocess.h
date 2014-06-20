#ifndef TEACHPROCESS_H
#define TEACHPROCESS_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class TeachProcess;
}

class TeachProcess : public QDialog
{
    Q_OBJECT

public:
    explicit TeachProcess(QWidget *parent = 0);
    ~TeachProcess();

private:
    Ui::TeachProcess *_ui;

public:
    int get_count() const;
    int get_speed() const;
};

#endif // TEACHPROCESS_H
