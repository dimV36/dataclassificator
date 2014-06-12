#ifndef COLORCHOOSERDIALOG_H
#define COLORCHOOSERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QColorDialog>
#include <QTableWidgetItem>

namespace Ui {
class ColorChooserDialog;
}

class ColorChooserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorChooserDialog(QWidget *parent = 0);
    ~ColorChooserDialog();

    void set_classmap(QMap<QString, QColor> classmap);
    QMap<QString, QColor> get_classmap() const;

private:
    Ui::ColorChooserDialog *_ui;

private slots:
    void SlotItemWasDoubleClicked(QTableWidgetItem *item);


};

#endif // COLORCHOOSERDIALOG_H
