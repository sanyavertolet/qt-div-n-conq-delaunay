#include "widget.h"

#include <QApplication>
#include <QLoggingCategory>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // disable debug messages
    QLoggingCategory::setFilterRules("*.debug=false");
    Widget w;
    w.show();
    return a.exec();
}
