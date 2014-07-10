#include "node.h"

Node::Node(QGVScene *scene, QString label) {
    _scene = scene;
    _node = _scene -> addNode(label);
    _edges = QVector<QGVEdge*>();
}


Node::~Node() {
    _edges.clear();
    delete _node;
}


QGVNode* Node::get_node() const {
    return _node;
}


QVector<QGVEdge*> Node::get_edges() const {
    return _edges;
}


QGVScene* Node::get_scene() const {
    return _scene;
}


void Node::set_node(QGVNode *node) {
    _node = node;
}


void Node::set_edges(QVector<QGVEdge*> edges) {
    _edges = edges;
}


void Node::set_scene(QGVScene *scene) {
    _scene = scene;
}


void Node::AddEdge(Node *node, const QString label) {
    QGVEdge *edge = _scene -> addEdge(_node, node -> get_node(), label);
    edge -> setAttribute("fontsize", "60");
    _edges.push_back(edge);
}


void Node::RemoveEdge(int index) {
    if (index >= 0 && index < _edges.size()) {
        _scene -> removeItem(_edges[index]);
    }
}
