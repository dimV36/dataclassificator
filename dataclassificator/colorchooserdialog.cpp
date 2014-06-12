#include "colorchooserdialog.h"
#include "ui_colorchooserdialog.h"

#include <QDebug>

ColorChooserDialog::ColorChooserDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::ColorChooserDialog) {
    _ui -> setupUi(this);

    _ui -> _button_box -> button(_ui -> _button_box -> Cancel) -> setText(tr("Отмена"));
    connect(_ui -> _table, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(SlotItemWasDoubleClicked(QTableWidgetItem *)));

}


/**
 * Деструктор
 * @brief ColorChooserDialog::~ColorChooserDialog
 */
ColorChooserDialog::~ColorChooserDialog() {
    delete _ui;
}


/**
 * Добавление имён классов в таблицу
 * @brief ColorChooserDialog::set_classes
 * @param classes
 */
void ColorChooserDialog::set_classmap(QMap<QString, QColor> classmap) {
    _ui -> _table -> setRowCount(classmap.size());
    for (int i = 0; i < classmap.size(); i++) {
        QTableWidgetItem *class_name_item = new QTableWidgetItem(classmap.keys()[i]);
        QPixmap pixmap(10, 10);
        pixmap.fill(classmap.values()[i]);
        class_name_item -> setIcon(QIcon(pixmap));
        _ui -> _table -> setItem(i, 0, class_name_item);
    }
}


/**
 * Получить карту цветов
 * @brief ColorChooserDialog::get_classmap
 * @return
 */
QMap<QString, QColor> ColorChooserDialog::get_classmap() const {
    QMap<QString, QColor> result;
    for (int i = 0; i < _ui -> _table -> rowCount(); i++) {
        QTableWidgetItem *item = _ui -> _table -> item(i, 0);
        /* Получаем иконку элемента таблицы*/
        QPixmap pixmap = item -> icon().pixmap(10, 10);
        result[item -> text()] = QColor(pixmap.toImage().pixel(0, 0));
    }
    return result;
}


/**
 * Слот редактирования цветов
 * @brief ColorChooserDialog::SlotItemWasDoubleClicked
 * @param item
 */
void ColorChooserDialog::SlotItemWasDoubleClicked(QTableWidgetItem *item) {
    QColor color = QColorDialog::getColor();
    QPixmap pixmap(10, 10);
    pixmap.fill(color);
    item -> setIcon(QIcon(pixmap));
}
