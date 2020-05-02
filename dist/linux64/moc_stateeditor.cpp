/****************************************************************************
** Meta object code from reading C++ file 'stateeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TIPE/src/stateeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stateeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StateEditor_t {
    QByteArrayData data[15];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StateEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StateEditor_t qt_meta_stringdata_StateEditor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "StateEditor"
QT_MOC_LITERAL(1, 12, 7), // "refresh"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "incrOneS"
QT_MOC_LITERAL(4, 30, 8), // "incrTthS"
QT_MOC_LITERAL(5, 39, 8), // "incrHthS"
QT_MOC_LITERAL(6, 48, 8), // "decrOneS"
QT_MOC_LITERAL(7, 57, 8), // "decrTthS"
QT_MOC_LITERAL(8, 66, 8), // "decrHthS"
QT_MOC_LITERAL(9, 75, 8), // "incrOneT"
QT_MOC_LITERAL(10, 84, 8), // "incrTthT"
QT_MOC_LITERAL(11, 93, 8), // "incrHthT"
QT_MOC_LITERAL(12, 102, 8), // "decrOneT"
QT_MOC_LITERAL(13, 111, 8), // "decrTthT"
QT_MOC_LITERAL(14, 120, 8) // "decrHthT"

    },
    "StateEditor\0refresh\0\0incrOneS\0incrTthS\0"
    "incrHthS\0decrOneS\0decrTthS\0decrHthS\0"
    "incrOneT\0incrTthT\0incrHthT\0decrOneT\0"
    "decrTthT\0decrHthT"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StateEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StateEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StateEditor *_t = static_cast<StateEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refresh(); break;
        case 1: _t->incrOneS(); break;
        case 2: _t->incrTthS(); break;
        case 3: _t->incrHthS(); break;
        case 4: _t->decrOneS(); break;
        case 5: _t->decrTthS(); break;
        case 6: _t->decrHthS(); break;
        case 7: _t->incrOneT(); break;
        case 8: _t->incrTthT(); break;
        case 9: _t->incrHthT(); break;
        case 10: _t->decrOneT(); break;
        case 11: _t->decrTthT(); break;
        case 12: _t->decrHthT(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject StateEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StateEditor.data,
      qt_meta_data_StateEditor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StateEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StateEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StateEditor.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int StateEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
