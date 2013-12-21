/****************************************************************************
** Meta object code from reading C++ file 'settingseditor.h'
**
** Created: Mon Jan 28 08:32:22 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../settingseditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingseditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SettingsEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SettingsEditor[] = {
    "SettingsEditor\0\0edited(PlotSettings)\0"
    "edited()\0"
};

const QMetaObject SettingsEditor::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_SettingsEditor,
      qt_meta_data_SettingsEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SettingsEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SettingsEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SettingsEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsEditor))
        return static_cast<void*>(const_cast< SettingsEditor*>(this));
    return QFrame::qt_metacast(_clname);
}

int SettingsEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: edited((*reinterpret_cast< const PlotSettings(*)>(_a[1]))); break;
        case 1: edited(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SettingsEditor::edited(const PlotSettings & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
