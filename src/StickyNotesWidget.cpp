#include "StickyNotesWidget.h"
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>

StickyNotesWidget::StickyNotesWidget(QWidget *parent)
    : BaseWidget(parent)
{
    addButton = new QPushButton("Add Note", this);
    addButton->setMinimumHeight(30);

    scrollArea = new QScrollArea(this);
    notesContainer = new QWidget();
    notesLayout = new QVBoxLayout(notesContainer);
    notesLayout->setAlignment(Qt::AlignTop);

    notesContainer->setLayout(notesLayout);
    scrollArea->setWidget(notesContainer);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumHeight(300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &StickyNotesWidget::addNote);

    loadNotesFromFile();
}

StickyNotesWidget::~StickyNotesWidget()
{
    saveNotesToFile();
}

void StickyNotesWidget::addNote()
{
    createNote();
}

void StickyNotesWidget::createNote(const QString &content, bool loading)
{
    QWidget *noteWidget = new QWidget(this);
    QVBoxLayout *noteLayout = new QVBoxLayout(noteWidget);

    QTextEdit *textEdit = new QTextEdit();
    textEdit->setText(content);
    textEdit->setMinimumHeight(100);

    QPushButton *deleteBtn = new QPushButton("❌ Delete");
    deleteBtn->setFixedWidth(80);

    noteLayout->addWidget(textEdit);
    noteLayout->addWidget(deleteBtn, 0, Qt::AlignRight);
    noteWidget->setLayout(noteLayout);

    notesLayout->addWidget(noteWidget);

    connect(deleteBtn, &QPushButton::clicked, this, [=]() {
        deleteNote(noteWidget);
    });

    if (!loading)
        saveNotesToFile();
}

void StickyNotesWidget::deleteNote(QWidget *noteWidget)
{
    notesLayout->removeWidget(noteWidget);
    noteWidget->deleteLater();
    saveNotesToFile();
}

void StickyNotesWidget::saveNotesToFile()
{
    QFile file("notes.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < notesLayout->count(); ++i) {
            QWidget *widget = notesLayout->itemAt(i)->widget();
            QTextEdit *textEdit = widget->findChild<QTextEdit *>();
            if (textEdit)
                out << textEdit->toPlainText() << "\n###NOTE_SPLIT###\n";
        }
        file.close();
    }
}

void StickyNotesWidget::loadNotesFromFile()
{
    QFile file("notes.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString data = in.readAll();
        QStringList notes = data.split("###NOTE_SPLIT###", Qt::SkipEmptyParts);
        for (const QString &note : notes) {
            createNote(note.trimmed(), true);
        }
        file.close();
    }
}
