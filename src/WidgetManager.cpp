#include "WidgetManager.h"
#include "ColorWidget.h"
#include "DigitalClockWidget.h"
#include "ToDoListWidget.h"
#include "CalendarWidget.h"
#include "StickyNoteWidget.h"

WidgetManager& WidgetManager::instance() {
    static WidgetManager instance;
    return instance;
}

WidgetManager::WidgetManager(QObject* parent) : QObject(parent), m_settings("MyCompany", "MyApp") {}

void WidgetManager::loadWidgets(QWidget* parent) {
    qDeleteAll(m_widgets);
    m_widgets.clear();

    int size = m_settings.beginReadArray("widgets");
    bool stickyNoteLoaded = false;
    for (int i = 0; i < size; ++i) {
        m_settings.setArrayIndex(i);
        QString type = m_settings.value("type").toString();
        QVariantMap state = m_settings.value("state").toMap();

        BaseWidget* widget = nullptr;
        if (type == "StickyNoteWidget") {
            if (stickyNoteLoaded) {
                continue; // Skip additional sticky notes
            }
            StickyNoteWidget* note = new StickyNoteWidget(parent);
            if (state.contains("noteData")) {
                note->loadNoteData(state["noteData"].toMap());
            }
            widget = note;
            stickyNoteLoaded = true;
        } else {
            widget = createWidget(type, parent);
        }

        if (widget) {
            loadWidgetState(widget, state);
            widget->show();
            m_widgets.append(widget);
        }
    }
    m_settings.endArray();
}

void WidgetManager::saveWidgets() {
    m_settings.beginWriteArray("widgets");
    for (int i = 0; i < m_widgets.size(); ++i) {
        m_settings.setArrayIndex(i);
        BaseWidget* widget = m_widgets[i];
        m_settings.setValue("type", widget->metaObject()->className());
        m_settings.setValue("state", saveWidgetState(widget));
    }
    m_settings.endArray();
    m_settings.sync();
}

void WidgetManager::addWidget(const QString& type, QWidget* parent, const QPoint& pos) {
    if (BaseWidget* widget = createWidget(type, parent)) {
        widget->move(pos);
        widget->show();
        m_widgets.append(widget);
        saveWidgets();
    }
}

void WidgetManager::removeWidget(BaseWidget* widget) {
    if (m_widgets.removeOne(widget)) {
        widget->deleteLater();
        saveWidgets();
    }
}

QList<BaseWidget*> WidgetManager::getWidgets() const {
    return m_widgets;
}

BaseWidget* WidgetManager::createWidget(const QString& type, QWidget* parent) {
    BaseWidget* widget = nullptr;
    if (type == "ColorWidget") {
        widget = new ColorWidget(parent);
    } else if (type == "DigitalClockWidget") {
        widget = new DigitalClockWidget(parent);
    } else if (type == "ToDoListWidget") {
        widget = new ToDoListWidget(parent);
    } else if (type == "CalendarWidget") {
        widget = new CalendarWidget(parent);
    } else if (type == "StickyNoteWidget") {
        widget = new StickyNoteWidget(parent);
    }

    return widget;
}

void WidgetManager::loadWidgetState(BaseWidget* widget, const QVariantMap& state) {
    if (!state.isEmpty()) {
        widget->setGeometry(state.value("geometry").toRect());
    }
}

QVariantMap WidgetManager::saveWidgetState(BaseWidget* widget) const {
    QVariantMap state;
    state["geometry"] = widget->geometry();

    if (auto* note = qobject_cast<StickyNoteWidget*>(widget)) {
        state["noteData"] = note->noteData();
    }

    return state;
}