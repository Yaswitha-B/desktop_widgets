#include "CalendarWidget.h"
#include <QTextCharFormat>
#include <QFont>

CalendarWidget::CalendarWidget(QWidget *parent)
    : BaseWidget(parent), currentDate(QDate::currentDate()) {

    setFixedSize(420, 380);

    calendar = new QCalendarWidget(this);
    calendar->setGridVisible(false);  // No grid lines
    calendar->setNavigationBarVisible(false);  
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    calendar->setDateEditEnabled(false);
    calendar->setSelectedDate(currentDate);
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setMaximumDate(QDate(2100, 12, 31));

    // Hide previous/next month dates
    QTextCharFormat hiddenFormat;
    hiddenFormat.setForeground(Qt::transparent);
    for (int row = 0; row < 6; ++row) {
        for (int col = 1; col <= 7; ++col) {
            QDate date = QDate(currentDate.year(), currentDate.month(), 1);
            int firstDayOfWeek = date.dayOfWeek();
            int daysInMonth = date.daysInMonth();

            int index = row * 7 + col;
            int actualDay = index - firstDayOfWeek + 1;

            if (actualDay < 1 || actualDay > daysInMonth) {
                QDate outDate = date.addDays(actualDay - 1);
                calendar->setDateTextFormat(outDate, hiddenFormat);
            }
        }
    }

    applyCreamyStyle();

    auto prevButton = new QPushButton("<");
    auto nextButton = new QPushButton(">");
    monthLabel = new QLabel();
    monthLabel->setAlignment(Qt::AlignCenter);
    monthLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #2f2f2f;");

    connect(prevButton, &QPushButton::clicked, this, &CalendarWidget::showPreviousMonth);
    connect(nextButton, &QPushButton::clicked, this, &CalendarWidget::showNextMonth);

    updateMonthLabel();

    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(prevButton);
    headerLayout->addWidget(monthLabel, 1);
    headerLayout->addWidget(nextButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(calendar);
    setLayout(mainLayout);
}

void CalendarWidget::showPreviousMonth() {
    currentDate = currentDate.addMonths(-1);
    calendar->setSelectedDate(currentDate);
    calendar->showSelectedDate();
    updateMonthLabel();
}

void CalendarWidget::showNextMonth() {
    currentDate = currentDate.addMonths(1);
    calendar->setSelectedDate(currentDate);
    calendar->showSelectedDate();
    updateMonthLabel();
}

void CalendarWidget::updateMonthLabel() {
    monthLabel->setText(currentDate.toString("MMMM yyyy"));
    calendar->setCurrentPage(currentDate.year(), currentDate.month());
}

void CalendarWidget::applyCreamyStyle() {
    calendar->setStyleSheet(R"(
        QCalendarWidget QWidget {
            background-color: #fdf5e6;
        }
        QCalendarWidget QToolButton {
            background-color: transparent;
        }
        QCalendarWidget QAbstractItemView {
            font-family: 'Georgia';
            font-size: 16px;
            color: #3e3e3e;
            background-color: #fdf5e6;
            selection-background-color: #ffecb3;
            selection-color: black;
        }
        QCalendarWidget QHeaderView::section {
            background-color: #fdf5e6;
            font-weight: bold;
        }
    )");
}
