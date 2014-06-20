#include "nodes.h"

Nodes::Nodes(int layout_count, int neuron_in_layout) {
    _layout_count = layout_count;
    _neuron_in_layout = neuron_in_layout;
    for (int i = 0; i < _layout_count; i++) {
        QVector<QGVNode *> layout;
        for (int j = 0; j < _neuron_in_layout; j++)

}
