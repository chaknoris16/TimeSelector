#ifndef TEST_TIME_SELECTOR_H
#define TEST_TIME_SELECTOR_H

#include <QObject>
#include <QTest>

class test_Time_Selector : public QObject
{
    Q_OBJECT
public:
    explicit test_Time_Selector(QObject *parent = nullptr);
private slots:
    void test_setTime();
};

#endif // TEST_TIME_SELECTOR_H
