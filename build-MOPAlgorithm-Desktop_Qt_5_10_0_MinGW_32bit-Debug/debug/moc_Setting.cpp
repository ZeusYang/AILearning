/****************************************************************************
** Meta object code from reading C++ file 'Setting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MOPAlgorithm/Setting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Setting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Setting_t {
    QByteArrayData data[14];
    char stringdata0[280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Setting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Setting_t qt_meta_stringdata_Setting = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Setting"
QT_MOC_LITERAL(1, 8, 5), // "begin"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 4), // "type"
QT_MOC_LITERAL(4, 20, 11), // "setProgress"
QT_MOC_LITERAL(5, 32, 8), // "progress"
QT_MOC_LITERAL(6, 41, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(7, 63, 39), // "on_algorithmComboBox_currentT..."
QT_MOC_LITERAL(8, 103, 4), // "arg1"
QT_MOC_LITERAL(9, 108, 32), // "on_groupLineEdit_editingFinished"
QT_MOC_LITERAL(10, 141, 36), // "on_objectComboBox_currentText..."
QT_MOC_LITERAL(11, 178, 39), // "on_dimensionComboBox_currentT..."
QT_MOC_LITERAL(12, 218, 37), // "on_generationLineEdit_editing..."
QT_MOC_LITERAL(13, 256, 23) // "on_pushButton_2_clicked"

    },
    "Setting\0begin\0\0type\0setProgress\0"
    "progress\0on_pushButton_clicked\0"
    "on_algorithmComboBox_currentTextChanged\0"
    "arg1\0on_groupLineEdit_editingFinished\0"
    "on_objectComboBox_currentTextChanged\0"
    "on_dimensionComboBox_currentTextChanged\0"
    "on_generationLineEdit_editingFinished\0"
    "on_pushButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Setting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   62,    2, 0x0a /* Public */,
       6,    0,   65,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    1,   70,    2, 0x08 /* Private */,
      11,    1,   73,    2, 0x08 /* Private */,
      12,    0,   76,    2, 0x08 /* Private */,
      13,    0,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Setting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Setting *_t = static_cast<Setting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->begin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setProgress((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->on_algorithmComboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_groupLineEdit_editingFinished(); break;
        case 5: _t->on_objectComboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_dimensionComboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_generationLineEdit_editingFinished(); break;
        case 8: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Setting::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Setting::begin)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Setting::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Setting.data,
      qt_meta_data_Setting,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Setting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Setting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Setting.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Setting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Setting::begin(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
