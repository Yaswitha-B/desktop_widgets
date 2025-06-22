#include "CalendarWidget.h"
#include <QTextCharFormat>
#include <QFont>
#include <QInputDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDialog>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QLineEdit>

CalendarWidget::CalendarWidget(QWidget *parent)
    : BaseWidget(parent), currentDate(QDate::currentDate()) {

    setFixedSize(420, 380);

    calendar = new QCalendarWidget(this);
    calendar->setGridVisible(false);
    calendar->setNavigationBarVisible(false);  
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    calendar->setDateEditEnabled(false);
    calendar->setSelectedDate(currentDate);
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setMaximumDate(QDate(2100, 12, 31));

    // Removed code that sets some dates to transparent

    applyCreamyStyle();

    auto prevButton = new QPushButton("<");
    auto nextButton = new QPushButton(">");
    monthLabel = new QLabel();
    monthLabel->setAlignment(Qt::AlignCenter);
    monthLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #2f2f2f;");

    connect(prevButton, &QPushButton::clicked, this, &CalendarWidget::showPreviousMonth);
    connect(nextButton, &QPushButton::clicked, this, &CalendarWidget::showNextMonth);
    connect(calendar, &QCalendarWidget::clicked, this, &CalendarWidget::onDateClicked);
    updateMonthLabel();

    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(prevButton);
    headerLayout->addWidget(monthLabel, 1);
    headerLayout->addWidget(nextButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(calendar);
    setLayout(mainLayout);
    loadEvents();
    highlightEventDates();
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

void CalendarWidget::onDateClicked(const QDate &date) {
    QDialog dialog(this);
    dialog.setWindowTitle("Events for " + date.toString("dd MMM yyyy"));
    dialog.setStyleSheet("background:#fffbe6; font-family:'Georgia'; font-size:15px;");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QListWidget *eventListWidget = new QListWidget(&dialog);
    eventListWidget->addItems(events.value(date));
    eventListWidget->setStyleSheet("background:#fffde7; border-radius:6px; padding:6px; color:#3e3e3e;");
    layout->addWidget(eventListWidget);
    QLineEdit *eventInput = new QLineEdit(&dialog);
    eventInput->setPlaceholderText("Add a new event...");
    eventInput->setStyleSheet("background:#fffde7; border-radius:6px; padding:6px; margin-top:8px;");
    layout->addWidget(eventInput);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() == QDialog::Accepted) {
        QString text = eventInput->text().trimmed();
        if (!text.isEmpty()) {
            events[date].append(text);
            saveEvents();
            highlightEventDates();
        }
    }
}

void CalendarWidget::applyCreamyStyle() {
    calendar->setStyleSheet(R"(
        QCalendarWidget QWidget {
            background-color: #fffbe6;
        }
        QCalendarWidget QToolButton {
            background-color: transparent;
            color: #6d4c41;
            font-size: 18px;
            font-weight: bold;
        }
        QCalendarWidget QAbstractItemView {
            font-family: 'Georgia';
            font-size: 16px;
            color: #3e3e3e;
            background-color: #fffbe6;
            selection-background-color: #ffe082;
            selection-color: #4e342e;
            border-radius: 8px;
        }
        QCalendarWidget QHeaderView::section {
            background-color: #fffbe6;
            font-weight: bold;
            color: #6d4c41;
        }
        QCalendarWidget QSpinBox {
            background: #fffbe6;
        }
    )");
}

void CalendarWidget::highlightEventDates() {
    QTextCharFormat fmt;
    fmt.setBackground(QColor("#ffe082"));
    for (const QDate &date : events.keys()) {
        calendar->setDateTextFormat(date, fmt);
    }
}

void CalendarWidget::saveEvents() {
    QFile file("calendar_events.json");
    if (!file.open(QIODevice::WriteOnly)) return;
    QJsonObject root;
    for (auto it = events.begin(); it != events.end(); ++it) {
        QJsonArray arr;
        for (const QString &ev : it.value()) arr.append(ev);
        root[it.key().toString(Qt::ISODate)] = arr;
    }
    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();
}

void CalendarWidget::loadEvents() {
    QFile file("calendar_events.json");
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return;
    QJsonObject root = doc.object();
    for (const QString &key : root.keys()) {
        QDate date = QDate::fromString(key, Qt::ISODate);
        QJsonArray arr = root[key].toArray();
        QStringList evs;
        for (const QJsonValue &v : arr) evs.append(v.toString());
        events[date] = evs;
    }
}
