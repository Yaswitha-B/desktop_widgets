/****************************************************************************
** Meta object code from reading C++ file 'ToDoListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../include/ToDoListWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ToDoListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_ToDoListWidget_t {
    uint offsetsAndSizes[16];
    char stringdata0[15];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[9];
    char stringdata5[11];
    char stringdata6[18];
    char stringdata7[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ToDoListWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ToDoListWidget_t qt_meta_stringdata_ToDoListWidget = {
    {
        QT_MOC_LITERAL(0, 14),  // "ToDoListWidget"
        QT_MOC_LITERAL(15, 7),  // "addTask"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 14),  // "removeTaskItem"
        QT_MOC_LITERAL(39, 8),  // "QWidget*"
        QT_MOC_LITERAL(48, 10),  // "itemWidget"
        QT_MOC_LITERAL(59, 17),  // "loadTasksFromFile"
        QT_MOC_LITERAL(77, 15)   // "saveTasksToFile"
    },
    "ToDoListWidget",
    "addTask",
    "",
    "removeTaskItem",
    "QWidget*",
    "itemWidget",
    "loadTasksFromFile",
    "saveTasksToFile"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ToDoListWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    1,   39,    2, 0x08,    2 /* Private */,
       6,    0,   42,    2, 0x08,    4 /* Private */,
       7,    0,   43,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ToDoListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_meta_stringdata_ToDoListWidget.offsetsAndSizes,
    qt_meta_data_ToDoListWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ToDoListWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ToDoListWidget, std::true_type>,
        // method 'addTask'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeTaskItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        // method 'loadTasksFromFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveTasksToFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ToDoListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ToDoListWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addTask(); break;
        case 1: _t->removeTaskItem((*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[1]))); break;
        case 2: _t->loadTasksFromFile(); break;
        case 3: _t->saveTasksToFile(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *ToDoListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToDoListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ToDoListWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int ToDoListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
