#ifndef TABLECOLUMNCHOOSER_H
#define TABLECOLUMNCHOOSER_H

#include <QDialog>
#include <QListWidgetItem>
#include <QPushButton>

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
    Ui::TableColumnChooser *_ui;

public:
    void set_headers(QStringList headers);
    QStringList get_headers() const;

signals:
    void SignalItemCountInListChanged(int);

private slots:
    void SlotAddItemToChoosenList(QListWidgetItem *item);
    void SlotRemoveItemFromChoosenList(QListWidgetItem *item);
    void SlotSetEnabledOkButton(int count);

};

#endif // TABLECOLUMNCHOOSER_H
