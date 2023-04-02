/****************************************************************************
** Meta object code from reading C++ file 'flagChange.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mqtt-control/flagChange.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flagChange.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlagChange_t {
    const uint offsetsAndSize[12];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_FlagChange_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_FlagChange_t qt_meta_stringdata_FlagChange = {
    {
QT_MOC_LITERAL(0, 10), // "FlagChange"
QT_MOC_LITERAL(11, 21), // "signalIncreaseCounter"
QT_MOC_LITERAL(33, 0), // ""
QT_MOC_LITERAL(34, 4), // "int*"
QT_MOC_LITERAL(39, 13), // "globalCounter"
QT_MOC_LITERAL(53, 21) // "signalDecreaseCounter"

    },
    "FlagChange\0signalIncreaseCounter\0\0"
    "int*\0globalCounter\0signalDecreaseCounter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlagChange[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x06,    1 /* Public */,
       5,    1,   29,    2, 0x06,    3 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void FlagChange::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlagChange *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signalIncreaseCounter((*reinterpret_cast< std::add_pointer_t<int*>>(_a[1]))); break;
        case 1: _t->signalDecreaseCounter((*reinterpret_cast< std::add_pointer_t<int*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FlagChange::*)(int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlagChange::signalIncreaseCounter)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FlagChange::*)(int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlagChange::signalDecreaseCounter)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject FlagChange::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FlagChange.offsetsAndSize,
    qt_meta_data_FlagChange,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_FlagChange_t
, QtPrivate::TypeAndForceComplete<FlagChange, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int *, std::false_type>



>,
    nullptr
} };


const QMetaObject *FlagChange::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlagChange::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlagChange.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FlagChange::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FlagChange::signalIncreaseCounter(int * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlagChange::signalDecreaseCounter(int * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
