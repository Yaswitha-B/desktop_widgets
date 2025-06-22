#pragma once
#include <QObject>
#include <QList>
#include <QSettings>
#include <QVariantMap>
#include "BaseWidget.h"

class WidgetManager : public QObject {
    Q_OBJECT
public:
    static WidgetManager& instance();

    void loadWidgets(QWidget* parent);
    void saveWidgets();
    void addWidget(const QString& type, QWidget* parent, const QPoint& pos = QPoint(100,100));
    void removeWidget(BaseWidget* widget);

    QList<BaseWidget*> getWidgets() const;

private:
    explicit WidgetManager(QObject* parent = nullptr);
    BaseWidget* createWidget(const QString& type, QWidget* parent);
    void loadWidgetState(BaseWidget* widget, const QVariantMap& state);
    QVariantMap saveWidgetState(BaseWidget* widget) const;
    QList<BaseWidget*> m_widgets;
    QSettings m_settings;
};
