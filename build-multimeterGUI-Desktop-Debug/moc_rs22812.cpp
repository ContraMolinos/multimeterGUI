/****************************************************************************
** Meta object code from reading C++ file 'rs22812.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../rs22812.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rs22812.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RS22812_t {
    QByteArrayData data[6];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RS22812_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RS22812_t qt_meta_stringdata_RS22812 = {
    {
QT_MOC_LITERAL(0, 0, 7), // "RS22812"
QT_MOC_LITERAL(1, 8, 7), // "newMode"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 7), // "newData"
QT_MOC_LITERAL(4, 25, 8), // "newValue"
QT_MOC_LITERAL(5, 34, 4) // "data"

    },
    "RS22812\0newMode\0\0newData\0newValue\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RS22812[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    5,

       0        // eod
};

void RS22812::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RS22812 *_t = static_cast<RS22812 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newMode(); break;
        case 1: _t->newData(); break;
        case 2: _t->newValue((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RS22812::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RS22812::newMode)) {
                *result = 0;
            }
        }
        {
            typedef void (RS22812::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RS22812::newData)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject RS22812::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RS22812.data,
      qt_meta_data_RS22812,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RS22812::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RS22812::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RS22812.stringdata0))
        return static_cast<void*>(const_cast< RS22812*>(this));
    return QObject::qt_metacast(_clname);
}

int RS22812::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void RS22812::newMode()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void RS22812::newData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
