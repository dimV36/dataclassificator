#ifndef TABLECOLUMNCHOOSER_H
#define TABLECOLUMNCHOOSER_H

#include <QDialog>

namespace Ui {
class TableColumnChooser;
}

class TableColumnChooser : public QDialog
{
    Q_OBJECT

public:
    explicit TableColumnChooser(QWidget *parent = 0);
    ~TableColumnChooser();

private:
    Ui::TableColumnChooser *ui;
};

#endif // TABLECOLUMNCHOOSER_H
