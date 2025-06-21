#pragma once

#include "BaseWidget.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>

class StickyNotesWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit StickyNotesWidget(QWidget *parent = nullptr);
    ~StickyNotesWidget();

private slots:
    void addNote();
    void deleteNote(QWidget *noteWidget);
    void saveNotesToFile();
    void loadNotesFromFile();

private:
    QWidget *notesContainer;
    QVBoxLayout *notesLayout;
    QScrollArea *scrollArea;
    QPushButton *addButton;

    void createNote(const QString &content = "", bool loading = false);
};
