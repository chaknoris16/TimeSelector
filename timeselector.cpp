#include "timeselector.h"
#include "./ui_timeselector.h"

TimeSelector::TimeSelector(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimeSelector)
{
    ui->setupUi(this);
    this->validator = new QRegularExpressionValidator(QRegularExpression("[0-9]"));
    ui->lineEdit->setValidator(this->validator);
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

template<typename T>
void TimeSelector::setTime(const T &time)
{
    ui->lineEdit->setText(QVariant(time).toString());
}

void TimeSelector::connects()
{
    connect(ui->lineEdit, &QLineEdit::textChanged, this, [this](const QString& newTime){emit this->timechange(newTime.toInt());});
    connect(timerIncrement, &QTimer::timeout, this, &TimeSelector::timeIncrement);
    connect(timerDecrement, &QTimer::timeout, this, &TimeSelector::timeDecrement);

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

void TimeSelector::timeIncrement()
{
    this->setTime(ui->lineEdit->text().toInt() + timeCounterIncrement);
}

void TimeSelector::timeDecrement()
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
            this->timeIncrement();
        }else if (delta < 0){
            this->timeDecrement();
        }
    }

    return QWidget::eventFilter(obj, event);
}
