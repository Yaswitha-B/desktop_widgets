#pragma once

#include "BaseWidget.h"
#include <QCalendarWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QLabel>

class CalendarWidget : public BaseWidget {
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = nullptr);

private slots:
    void showPreviousMonth();
    void showNextMonth();
    void onDateClicked(const QDate &date);

private:
    QCalendarWidget *calendar;
    QLabel *monthLabel;
    QDate currentDate;
    QMap<QDate, QStringList> events;
    void updateMonthLabel();
    void applyCreamyStyle();
    void highlightEventDates();
    void saveEvents();
    void loadEvents();
};
