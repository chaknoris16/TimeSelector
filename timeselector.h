#ifndef TIMESELECTOR_H
#define TIMESELECTOR_H

#include <QWidget>
#include <QString>
#include <QValidator>
#include <QVariant>
#include <QTimer>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
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
    template <typename T>
    void setTime(const T& time);
signals:
    void timechange(int newTime);
private:
    Ui::TimeSelector *ui;
    QValidator *validator;
    QTimer* timerIncrement = new QTimer(this);
    QTimer* timerDecrement = new QTimer(this);
    int timeCounterIncrement = 5;
    void connects();
private slots:
    void timeIncrement();
    void timeDecrement();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // TIMESELECTOR_H
