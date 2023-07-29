/****************************************************************************
** Meta object code from reading C++ file 'sqlconversationmodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Chat_qt/sqlconversationmodel.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqlconversationmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
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
struct qt_meta_stringdata_CLASSSqlConversationModelENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSqlConversationModelENDCLASS = QtMocHelpers::stringData(
    "SqlConversationModel",
    "recipient_change",
    "",
    "send_message",
    "recipient",
    "message"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSqlConversationModelENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[21];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[10];
    char stringdata5[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSqlConversationModelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSqlConversationModelENDCLASS_t qt_meta_stringdata_CLASSSqlConversationModelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 20),  // "SqlConversationModel"
        QT_MOC_LITERAL(21, 16),  // "recipient_change"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 12),  // "send_message"
        QT_MOC_LITERAL(52, 9),  // "recipient"
        QT_MOC_LITERAL(62, 7)   // "message"
    },
    "SqlConversationModel",
    "recipient_change",
    "",
    "send_message",
    "recipient",
    "message"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSqlConversationModelENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   32, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x06,    2 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    2,   27,    2, 0x02,    3 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,

 // properties: name, type, flags
       4, QMetaType::QString, 0x00015003, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject SqlConversationModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QSqlTableModel::staticMetaObject>(),
    qt_meta_stringdata_CLASSSqlConversationModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSqlConversationModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSqlConversationModelENDCLASS_t,
        // property 'recipient'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SqlConversationModel, std::true_type>,
        // method 'recipient_change'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void SqlConversationModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SqlConversationModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->recipient_change(); break;
        case 1: _t->send_message((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SqlConversationModel::*)();
            if (_t _q_method = &SqlConversationModel::recipient_change; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SqlConversationModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->recipient(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SqlConversationModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_recipient(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *SqlConversationModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SqlConversationModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSqlConversationModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QSqlTableModel::qt_metacast(_clname);
}

int SqlConversationModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlTableModel::qt_metacall(_c, _id, _a);
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
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void SqlConversationModel::recipient_change()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
