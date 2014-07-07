#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGVEdge.h>
#include <QGVNode.h>
#include <QGVScene.h>

class Node {
private:
    QGVNode *_node;
    QGVScene *_scene;
    QVector<QGVEdge*> _edges;
public:
    Node(QGVScene *scene, QString label = QString());
    ~Node();

    QGVNode *get_node() const;
    QVector<QGVEdge*> get_edges() const;
    QGVScene* get_scene() const;

    void set_node(QGVNode *node);
    void set_edges(QVector<QGVEdge *> edges);
    void set_scene(QGVScene *scene);

    void AddEdge(Node *node, const QString label = QString());
    void RemoveEdge(int index);
signals:

public slots:

};

#endif // NODE_H
