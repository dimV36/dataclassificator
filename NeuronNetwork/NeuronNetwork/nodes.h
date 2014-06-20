#ifndef NODES_H
#define NODES_H

#include <QVector>
#include <QGVCore/QGVNode.h>

class Nodes
{
private:
    QVector<QVector<QGVNode *> > _nodes;
    int _layout_count;
    int _neuron_in_layout;

public:
    Nodes(int layout_count, int neuron_in_layout);

};

#endif // NODES_H
