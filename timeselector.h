#ifndef TIMESELECTOR_H
#define TIMESELECTOR_H

#include <QWidget>
#include <QString>
#include <QVariant>
#include <QTimer>
#include <QWheelEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class TimeSelector;
}
QT_END_NAMESPACE

class TimeSelector : public QWidget
{
    Q_OBJECT
public:
    TimeSelector(QWidget *parent = nullptr);
    ~TimeSelector();
    int getCurrentTime();
public slots:
    void setTime(int time);
signals:
    void timechange(int newTime);
private:
    Ui::TimeSelector *ui;
    QTimer* timerIncrement = new QTimer(this);
    QTimer* timerDecrement = new QTimer(this);
    void connects();
    int timeCounterIncrement = 5;
    int minMins = 10;
    int maxMins = 240;
private slots:
    void timeIncrementing();
    void timeDecrementing();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // TIMESELECTOR_H
