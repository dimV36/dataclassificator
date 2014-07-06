#ifndef NEURALSAMPLE_H
#define NEURALSAMPLE_H

#include <QVector>
#include <QPair>

typedef QPair<QVector<double>, QVector<int> > NeuralNetworkExample;

class NeuralSample {
private:
    QVector<QVector<double> > _datas;
    QVector<QVector<int> > _targets;
public:
    NeuralSample();

    void Push(QVector<double> data, QVector<int> target);
    void Clear();
    int GetSampleSize() const;
    NeuralNetworkExample GetExample(int index);

    NeuralNetworkExample operator[] (int index);
};

#endif // NEURALSAMPLE_H
