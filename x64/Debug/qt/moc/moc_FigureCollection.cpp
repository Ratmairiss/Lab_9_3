/****************************************************************************
** Meta object code from reading C++ file 'FigureCollection.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../FigureCollection.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FigureCollection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFigureCollectionENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFigureCollectionENDCLASS = QtMocHelpers::stringData(
    "FigureCollection",
    "addFigure",
    "",
    "showAllRows",
    "updateHideFigureBtn",
    "name",
    "updateHideFigureTypeBtn",
    "figType",
    "hideFigure",
    "hideFiguresWithType"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFigureCollectionENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x09,    1 /* Protected */,
       3,    0,   51,    2, 0x09,    2 /* Protected */,
       4,    1,   52,    2, 0x09,    3 /* Protected */,
       6,    1,   55,    2, 0x09,    5 /* Protected */,
       8,    0,   58,    2, 0x09,    7 /* Protected */,
       9,    0,   59,    2, 0x09,    8 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FigureCollection::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSFigureCollectionENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFigureCollectionENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFigureCollectionENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FigureCollection, std::true_type>,
        // method 'addFigure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showAllRows'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateHideFigureBtn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'updateHideFigureTypeBtn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'hideFigure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hideFiguresWithType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FigureCollection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FigureCollection *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addFigure(); break;
        case 1: _t->showAllRows(); break;
        case 2: _t->updateHideFigureBtn((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->updateHideFigureTypeBtn((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->hideFigure(); break;
        case 5: _t->hideFiguresWithType(); break;
        default: ;
        }
    }
}

const QMetaObject *FigureCollection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FigureCollection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFigureCollectionENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FigureCollection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP