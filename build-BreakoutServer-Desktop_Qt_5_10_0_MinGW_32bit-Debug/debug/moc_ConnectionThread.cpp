/****************************************************************************
** Meta object code from reading C++ file 'ConnectionThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BreakoutServer/ConnectionThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConnectionThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionThread_t {
    QByteArrayData data[10];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionThread_t qt_meta_stringdata_ConnectionThread = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ConnectionThread"
QT_MOC_LITERAL(1, 17, 7), // "revData"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "sendDat"
QT_MOC_LITERAL(4, 34, 4), // "data"
QT_MOC_LITERAL(5, 39, 2), // "id"
QT_MOC_LITERAL(6, 42, 13), // "disconnectTCP"
QT_MOC_LITERAL(7, 56, 8), // "sendData"
QT_MOC_LITERAL(8, 65, 8), // "recvData"
QT_MOC_LITERAL(9, 74, 16) // "disconnectToHost"

    },
    "ConnectionThread\0revData\0\0sendDat\0"
    "data\0id\0disconnectTCP\0sendData\0recvData\0"
    "disconnectToHost"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       3,    2,   49,    2, 0x06 /* Public */,
       6,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   57,    2, 0x08 /* Private */,
       8,    2,   62,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    2,    2,
    QMetaType::Void,

       0        // eod
};

void ConnectionThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConnectionThread *_t = static_cast<ConnectionThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->revData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->sendDat((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->disconnectTCP((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sendData((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->recvData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 5: _t->disconnectToHost(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ConnectionThread::*_t)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionThread::revData)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ConnectionThread::*_t)(QByteArray , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionThread::sendDat)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ConnectionThread::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionThread::disconnectTCP)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ConnectionThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ConnectionThread.data,
      qt_meta_data_ConnectionThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConnectionThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ConnectionThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ConnectionThread::revData(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConnectionThread::sendDat(QByteArray _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConnectionThread::disconnectTCP(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
