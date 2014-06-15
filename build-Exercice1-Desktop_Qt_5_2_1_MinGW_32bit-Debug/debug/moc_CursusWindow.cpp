/****************************************************************************
** Meta object code from reading C++ file 'CursusWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Projet/CursusWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CursusWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CursusEditeur_t {
    QByteArrayData data[5];
    char stringdata[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CursusEditeur_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CursusEditeur_t qt_meta_stringdata_CursusEditeur = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 13),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 12),
QT_MOC_LITERAL(4, 42, 7)
    },
    "CursusEditeur\0ajouterCursus\0\0sauverCursus\0"
    "ajoutUV\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CursusEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a,
       3,    0,   30,    2, 0x0a,
       4,    0,   31,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CursusEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CursusEditeur *_t = static_cast<CursusEditeur *>(_o);
        switch (_id) {
        case 0: _t->ajouterCursus(); break;
        case 1: _t->sauverCursus(); break;
        case 2: _t->ajoutUV(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CursusEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CursusEditeur.data,
      qt_meta_data_CursusEditeur,  qt_static_metacall, 0, 0}
};


const QMetaObject *CursusEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CursusEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CursusEditeur.stringdata))
        return static_cast<void*>(const_cast< CursusEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int CursusEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
