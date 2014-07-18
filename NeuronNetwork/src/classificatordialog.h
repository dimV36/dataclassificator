#ifndef CLASSIFICATORDIALOG_H
#define CLASSIFICATORDIALOG_H

#include <QDialog>
#include <QMap>
#include <QFileDialog>

#define CLASS_SECTION 0
#define NETWORK_RESPONSE_SECTION 1
#define STATUS_SECTION 2

#define PERCENT_SECTION 1

namespace Ui {
class ClassificatorDialog;
}

class ClassificatorDialog : public QDialog {
    Q_OBJECT

private:
    Ui::ClassificatorDialog *_ui;
    QMap<QString, int> _statistic_map;
    QMap<QString, int> _class_counts;

public:
    explicit ClassificatorDialog(QWidget *parent = 0);
    ~ClassificatorDialog();

    void set_data(QList<QPair<QString, QString> > data);
    QStringList get_statistic() const;

    QString get_file_name() const;

private:
    void UpdateMapStatistic(QString class_name, QString status);
    void SetStatistic();

private slots:
    void SlotSetStatisticHidden();
    void on__button_change_file_name_clicked();
};

#endif // CLASSIFICATORDIALOG_H
