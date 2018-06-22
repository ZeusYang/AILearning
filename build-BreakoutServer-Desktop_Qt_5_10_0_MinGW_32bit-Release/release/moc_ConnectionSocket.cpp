/****************************************************************************
** Meta object code from reading C++ file 'ConnectionSocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BreakoutServer/ConnectionSocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConnectionSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionSocket_t {
    QByteArrayData data[7];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionSocket_t qt_meta_stringdata_ConnectionSocket = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ConnectionSocket"
QT_MOC_LITERAL(1, 17, 7), // "revData"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "recvData"
QT_MOC_LITERAL(4, 35, 7), // "sendMsg"
QT_MOC_LITERAL(5, 43, 3), // "msg"
QT_MOC_LITERAL(6, 47, 2) // "id"

    },
    "ConnectionSocket\0revData\0\0recvData\0"
    "sendMsg\0msg\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   34,    2, 0x0a /* Public */,
       4,    2,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,    5,    6,

       0        // eod
};

void ConnectionSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConnectionSocket *_t = static_cast<ConnectionSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->revData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->recvData(); break;
        case 2: _t->sendMsg((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ConnectionSocket::*_t)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionSocket::revData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ConnectionSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_ConnectionSocket.data,
      qt_meta_data_ConnectionSocket,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConnectionSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionSocket.stringdata0))
        return static_cast<void*>(this);
    return QTcpSocket::qt_metacast(_clname);
}

int ConnectionSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
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
void ConnectionSocket::revData(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
