/****************************************************************************
** Meta object code from reading C++ file 'simwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/simwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimWindow_t {
    QByteArrayData data[21];
    char stringdata0[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimWindow_t qt_meta_stringdata_SimWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SimWindow"
QT_MOC_LITERAL(1, 10, 7), // "refresh"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "closed"
QT_MOC_LITERAL(4, 26, 12), // "getOutputCst"
QT_MOC_LITERAL(5, 39, 12), // "getOutputStt"
QT_MOC_LITERAL(6, 52, 11), // "getInputCst"
QT_MOC_LITERAL(7, 64, 11), // "getInputStt"
QT_MOC_LITERAL(8, 76, 9), // "toggleCpl"
QT_MOC_LITERAL(9, 86, 9), // "toggleEqm"
QT_MOC_LITERAL(10, 96, 18), // "launchLayoutSelect"
QT_MOC_LITERAL(11, 115, 14), // "setlayout_full"
QT_MOC_LITERAL(12, 130, 23), // "setlayout_diagramhybrid"
QT_MOC_LITERAL(13, 154, 21), // "setlayout_statehybrid"
QT_MOC_LITERAL(14, 176, 16), // "setlayout_hybrid"
QT_MOC_LITERAL(15, 193, 17), // "setlayout_diagram"
QT_MOC_LITERAL(16, 211, 15), // "setlayout_state"
QT_MOC_LITERAL(17, 227, 4), // "SKIP"
QT_MOC_LITERAL(18, 232, 9), // "PLAYPAUSE"
QT_MOC_LITERAL(19, 242, 4), // "PING"
QT_MOC_LITERAL(20, 247, 10) // "screenshot"

    },
    "SimWindow\0refresh\0\0closed\0getOutputCst\0"
    "getOutputStt\0getInputCst\0getInputStt\0"
    "toggleCpl\0toggleEqm\0launchLayoutSelect\0"
    "setlayout_full\0setlayout_diagramhybrid\0"
    "setlayout_statehybrid\0setlayout_hybrid\0"
    "setlayout_diagram\0setlayout_state\0"
    "SKIP\0PLAYPAUSE\0PING\0screenshot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    0,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  111,    2, 0x0a /* Public */,
       5,    0,  112,    2, 0x0a /* Public */,
       6,    0,  113,    2, 0x0a /* Public */,
       7,    0,  114,    2, 0x0a /* Public */,
       8,    0,  115,    2, 0x0a /* Public */,
       9,    0,  116,    2, 0x0a /* Public */,
      10,    0,  117,    2, 0x0a /* Public */,
      11,    0,  118,    2, 0x0a /* Public */,
      12,    0,  119,    2, 0x0a /* Public */,
      13,    0,  120,    2, 0x0a /* Public */,
      14,    0,  121,    2, 0x0a /* Public */,
      15,    0,  122,    2, 0x0a /* Public */,
      16,    0,  123,    2, 0x0a /* Public */,
      17,    0,  124,    2, 0x0a /* Public */,
      18,    0,  125,    2, 0x0a /* Public */,
      19,    0,  126,    2, 0x0a /* Public */,
      20,    0,  127,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SimWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refresh(); break;
        case 1: _t->closed(); break;
        case 2: _t->getOutputCst(); break;
        case 3: _t->getOutputStt(); break;
        case 4: _t->getInputCst(); break;
        case 5: _t->getInputStt(); break;
        case 6: _t->toggleCpl(); break;
        case 7: _t->toggleEqm(); break;
        case 8: _t->launchLayoutSelect(); break;
        case 9: _t->setlayout_full(); break;
        case 10: _t->setlayout_diagramhybrid(); break;
        case 11: _t->setlayout_statehybrid(); break;
        case 12: _t->setlayout_hybrid(); break;
        case 13: _t->setlayout_diagram(); break;
        case 14: _t->setlayout_state(); break;
        case 15: _t->SKIP(); break;
        case 16: _t->PLAYPAUSE(); break;
        case 17: _t->PING(); break;
        case 18: _t->screenshot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SimWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimWindow::refresh)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SimWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimWindow::closed)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SimWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SimWindow.data,
    qt_meta_data_SimWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SimWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void SimWindow::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SimWindow::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
