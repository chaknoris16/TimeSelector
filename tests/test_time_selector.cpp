#include "test_time_selector.h"
#include "../timeselector.h"
test_Time_Selector::test_Time_Selector(QObject *parent)
    : QObject{parent}
{}

void test_Time_Selector::test_setTime()
{
    TimeSelector timeS;
    for(int i = 10; i < 240; ++i)
    {
        timeS.setTime(i);
        QCOMPARE(timeS.getCurrentTime(), i);
    }

    timeS.setTime(1);
    QVERIFY(timeS.getCurrentTime() != 1);
    QVERIFY(timeS.getCurrentTime() == 10);
    timeS.setTime(241);
    QVERIFY(timeS.getCurrentTime() != 241);
    QVERIFY(timeS.getCurrentTime() == 240);
}
