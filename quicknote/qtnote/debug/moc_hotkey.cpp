/****************************************************************************
** Meta object code from reading C++ file 'hotkey.h'
**
** Created: Tue 31. Jul 13:01:16 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hotkey.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hotkey.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HotKey[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,    8,    7,    7, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_HotKey[] = {
    "HotKey\0\0keyId,modifiers\0"
    "HotKeyPressed(uint,uint)\0"
};

void HotKey::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HotKey *_t = static_cast<HotKey *>(_o);
        switch (_id) {
        case 0: _t->HotKeyPressed((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData HotKey::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HotKey::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HotKey,
      qt_meta_data_HotKey, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HotKey::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HotKey::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HotKey::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HotKey))
        return static_cast<void*>(const_cast< HotKey*>(this));
    return QObject::qt_metacast(_clname);
}

int HotKey::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void HotKey::HotKeyPressed(uint _t1, uint _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
