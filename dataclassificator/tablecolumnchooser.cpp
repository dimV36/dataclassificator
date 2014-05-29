#include "tablecolumnchooser.h"
#include "ui_tablecolumnchooser.h"

TableColumnChooser::TableColumnChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableColumnChooser)
{
    ui->setupUi(this);
}

TableColumnChooser::~TableColumnChooser()
{
    delete ui;
}
