#include "timeselector.h"
#include "./tests/test_time_selector.h"
#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTest::qExec(new test_Time_Selector(), argc, argv);
    TimeSelector w;
    w.show();
    return a.exec();
}
