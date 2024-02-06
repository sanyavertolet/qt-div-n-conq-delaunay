#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

/**
 * @brief The Widget class represents the program window itself
 */
class Widget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Widget constructor
     * @param parent parent of a new widget
     */
    Widget(QWidget *parent = nullptr);

    /**
     * Almost default destructor
     */
    ~Widget();
private:
    /**
     * @brief scene graphics view's scene
     */
    QGraphicsScene *scene;

    /**
     * @brief view graphics view capable of displaying the polygon
     */
    QGraphicsView *view;
};
#endif // WIDGET_H
