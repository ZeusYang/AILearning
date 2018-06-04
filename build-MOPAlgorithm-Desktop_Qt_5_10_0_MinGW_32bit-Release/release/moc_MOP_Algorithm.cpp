/****************************************************************************
** Meta object code from reading C++ file 'MOP_Algorithm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MOPAlgorithm/Algorithm/MOP_Algorithm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MOP_Algorithm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MOP_Algorithm_t {
    QByteArrayData data[7];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MOP_Algorithm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MOP_Algorithm_t qt_meta_stringdata_MOP_Algorithm = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MOP_Algorithm"
QT_MOC_LITERAL(1, 14, 12), // "sendProgress"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "progress"
QT_MOC_LITERAL(4, 37, 8), // "sendData"
QT_MOC_LITERAL(5, 46, 17), // "vector<QVector3D>"
QT_MOC_LITERAL(6, 64, 4) // "data"

    },
    "MOP_Algorithm\0sendProgress\0\0progress\0"
    "sendData\0vector<QVector3D>\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MOP_Algorithm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void MOP_Algorithm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MOP_Algorithm *_t = static_cast<MOP_Algorithm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendProgress((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->sendData((*reinterpret_cast< const vector<QVector3D>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MOP_Algorithm::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MOP_Algorithm::sendProgress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MOP_Algorithm::*_t)(const vector<QVector3D> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MOP_Algorithm::sendData)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MOP_Algorithm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MOP_Algorithm.data,
      qt_meta_data_MOP_Algorithm,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MOP_Algorithm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MOP_Algorithm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MOP_Algorithm.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MOP_Algorithm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MOP_Algorithm::sendProgress(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MOP_Algorithm::sendData(const vector<QVector3D> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
