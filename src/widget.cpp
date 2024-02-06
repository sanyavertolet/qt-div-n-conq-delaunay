#include "widget.h"
#include "interactivegraphicsscene.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    scene = new InteractiveGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColorConstants::White));
    scene->setSceneRect(0, 0, 10, 10);

    view = new QGraphicsView(this);
    view->setScene(scene);
    view->resize(width(), height());
    view->setBackgroundBrush(QBrush(QColorConstants::White));
}

Widget::~Widget() {
    delete view;
    delete scene;
}
