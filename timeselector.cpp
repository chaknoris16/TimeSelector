#include "timeselector.h"
#include "./ui_timeselector.h"

TimeSelector::TimeSelector(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimeSelector)
{
    ui->setupUi(this);
    ui->lineEdit->installEventFilter(this);
    this->timerIncrement->setInterval(50);
    this->timerDecrement->setInterval(50);
    connects();

}

TimeSelector::~TimeSelector()
{
    delete ui;
}

int TimeSelector::getCurrentTime()
{
    return ui->lineEdit->text().toInt();
}

void TimeSelector::setTime(int time)
{
    if(time > this->maxMins)
    {
        ui->lineEdit->setText(QString::number(this->maxMins));
    } else if(time < this->minMins)
    {
        ui->lineEdit->setText(QString::number(this->minMins));
    }else
    {
        ui->lineEdit->setText(QVariant(time).toString());
    }
}

void TimeSelector::connects()
{
    connect(ui->lineEdit, &QLineEdit::textChanged, this, [this](const QString& newTime){emit this->timechange(newTime.toInt());});
    connect(timerIncrement, &QTimer::timeout, this, &TimeSelector::timeIncrementing);
    connect(timerDecrement, &QTimer::timeout, this, &TimeSelector::timeDecrementing);
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, [this](){
        this->setTime(this->getCurrentTime());
    });
    connect(ui->UpButton, &QPushButton::pressed, this, [this](){
        timerIncrement->start();
    });

    connect(ui->DownButton, &QPushButton::pressed, this, [this](){
        timerDecrement->start();
    });

    connect(ui->UpButton, &QPushButton::released, this, [this](){
        timerIncrement->stop();
    });

    connect(ui->DownButton, &QPushButton::released, this, [this](){
        timerDecrement->stop();
    });
}

void TimeSelector::timeIncrementing()
{
    this->setTime(ui->lineEdit->text().toInt() + timeCounterIncrement);
}

void TimeSelector::timeDecrementing()
{
    int currentTime = ui->lineEdit->text().toInt();
    if(currentTime >= 1) {
        this->setTime(currentTime - timeCounterIncrement);
    }
}

bool TimeSelector::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEdit && event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);

        int delta = wheelEvent->angleDelta().y();
        if (delta > 0)
        {
            this->timeIncrementing();
        }else if (delta < 0){
            this->timeDecrementing();
        }
    }

    return QWidget::eventFilter(obj, event);
}
