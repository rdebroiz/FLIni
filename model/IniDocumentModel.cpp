#include "IniDocumentModel.h"

#include <QStringList>

#include <QDebug>

// ServiceName ---------------------------------------------

QString
ServiceName::name() const
{
    return m_name;
}

QString
ServiceName::exeType() const
{
    return m_exeType;
}

QString
ServiceName::path() const
{
    return m_path;
}

QString
ServiceName::mainFunction() const
{
    return m_mainFunction;
}

QString
ServiceName::detail() const
{
    return m_detail;
}

void
ServiceName::setName(QString const& name)
{
    m_name = name;
    emit nameChanged(m_name);
}

void
ServiceName::setExeType(QString const& exeType)
{
    m_exeType = exeType;
    emit exeTypeChanged(exeType);
}

void
ServiceName::setPath(QString const& path)
{
    m_path = path;
    emit pathChanged(m_path);
}

void
ServiceName::setMainFunction(QString const& mainFunction)
{
    m_mainFunction = mainFunction;
    emit mainFunctionChanged(mainFunction);
}
void
ServiceName::setDetail(QString const& detail)
{
    m_detail = detail;
    emit detailChanged(detail);
}

// Field ---------------------------------------------------

QString
Field::name() const
{
    return m_name;
}

QString
Field::type() const
{
    return m_type;
}

QString
Field::switchCmd() const
{
    return m_switchCmd;
}

QString
Field::range() const
{
    return m_range;
}

QString
Field::defaultValue() const
{
    return m_defaultValue;
}

QString
Field::opt() const
{
    return m_opt;
}

QString
Field::detail() const
{
    return m_detail;
}

void
Field::setName(const QString &name)
{
    m_name = name;
    emit nameChanged(m_name);
}

void
Field::setType(const QString &type)
{
    m_type = type;
    emit typeChanged(m_type);
}

void
Field::setSwitchCmd(const QString &switchCmd)
{
    m_switchCmd = switchCmd;
    emit switchCmdChanged(switchCmd);
}

void
Field::setRange(const QString &range)
{
    m_range = range;
    emit rangeChanged(m_range);
}

void
Field::setDefaultValue(const QString &defaultValue)
{
    m_defaultValue = defaultValue;
    emit defaultValueChanged(m_defaultValue);
}

void
Field::setOpt(const QString &opt)
{
    m_opt = opt;
    emit optChanged(m_opt);
}

void
Field::setDetail(const QString &detail)
{
    m_detail = detail;
    emit detailChanged(detail);
}

// IninDocumentModel ---------------------------------------

IniDocumentModel::IniDocumentModel(QObject *parent) :
    QObject(parent)
{
    m_serviceName = new ServiceName;
    m_fieldList << new Field;
}


IniDocumentModel::~IniDocumentModel()
{
    if(!m_serviceName.isNull())
        m_serviceName->deleteLater();
    // QList auto deallocate raw pointer in destructor.
    m_fieldList.clear();
}

ServiceName*
IniDocumentModel::serviceName() const
{
    return m_serviceName;
}

void
IniDocumentModel::setServiceName(ServiceName*  serviceName)
{
    m_serviceName = serviceName;

    connect(m_serviceName, SIGNAL(nameChanged(QString)),
            this, SIGNAL(serviceNameNameChanged(QString)));
    connect(m_serviceName, SIGNAL(exeTypeChanged(QString)),
            this, SIGNAL(serviceNameExeTypeChanged(QString)));
    connect(m_serviceName, SIGNAL(pathChanged(QString)),
            this, SIGNAL(serviceNamePathChanged(QString)));
    connect(m_serviceName, SIGNAL(mainFunctionChanged(QString)),
            this, SIGNAL(serviceNameMainFunctionChanged(QString)));
    connect(m_serviceName, SIGNAL(detailChanged(QString)),
            this, SIGNAL(serviceNameDetailChanged(QString)));
}

Field*
IniDocumentModel::field(unsigned int index) const
{
    Field *f = NULL;
    if(!(index < m_fieldList.count()))
//        qDebug() << "IniDocumentModel:: Attempt to retrieve non existing field.";
        ;
    else
        f = m_fieldList[index];

    return f;
}

QList<Field* >
IniDocumentModel::allFields() const
{
    return m_fieldList;
}

Field*
IniDocumentModel::insertField(unsigned int index)
{
    Field* field = new Field;

    m_fieldList.insert(index, field);

    connect(field, SIGNAL(nameChanged(QString)),
            this, SLOT(_emitFieldNameChanged(QString)));
    connect(field, SIGNAL(typeChanged(QString)),
            this, SLOT(_emitFieldTypeChanged(QString)));
    connect(field, SIGNAL(switchCmdChanged(QString)),
            this, SLOT(_emitFieldSwitchCmdChanged(QString)));
    connect(field, SIGNAL(rangeChanged(QString)),
            this, SLOT(_emitFieldRangeChanged(QString)));
    connect(field, SIGNAL(defaultValueChanged(QString)),
            this, SLOT(_emitFieldDefaultValueChanged(QString)));
    connect(field, SIGNAL(optChanged(QString)),
            this, SLOT(_emitFieldOptChanged(QString)));
    connect(field, SIGNAL(detailChanged(QString)),
            this, SLOT(_emitFieldDetailChanged(QString)));

    return field;
}

void
IniDocumentModel::removeField(unsigned int index)
{
    m_fieldList.removeAt(index);
}

QString
IniDocumentModel::filename() const
{
    return m_filename;
}

void
IniDocumentModel::setFilename(const QString &filename)
{
    m_filename = filename;
}

void
IniDocumentModel::_emitFieldNameChanged(const QString& name)
{
    Field *field = qobject_cast<Field *>(QObject::sender());
    if(field != NULL)
    {
        int idx = m_fieldList.indexOf(field);
        emit fieldNameChanged(idx, name);
    }
}

void
IniDocumentModel::_emitFieldTypeChanged(const QString &type)
{
    Field *field = qobject_cast<Field *>(QObject::sender());
    if(field != NULL)
    {
        int idx = m_fieldList.indexOf(field);
        emit fieldTypeChanged(idx, type);
    }
}

void
IniDocumentModel::_emitFieldSwitchCmdChanged(const QString &switchCmd)
{
    Field *field = qobject_cast<Field *>(QObject::sender());
    if(field != NULL)
    {
        int idx = m_fieldList.indexOf(field);
        emit fieldSwitchCmdChanged(idx, switchCmd);
    }
}

void
IniDocumentModel::_emitFieldRangeChanged(const QString &range)
{
    Field *field = qobject_cast<Field *>(QObject::sender());
    if(field != NULL)
    {
        int idx = m_fieldList.indexOf(field);
        emit fieldRangeChanged(idx, range);
    }
}

void
IniDocumentModel::_emitFieldDefaultValueChanged(const QString &defaultValue)
{
    Field *field = qobject_cast<Field *>(QObject::sender());
    if(field != NULL)
    {
        int idx = m_fieldList.indexOf(field);
        emit fieldDefaultValueChanged(idx, defaultValue);
    }
}

void
IniDocumentModel::_emitFieldOptChanged(const QString &opt)
{
    Field *field = qobject_cast<Field *>(QObject::sender());
    if(field != NULL)
    {
        int idx = m_fieldList.indexOf(field);
        emit fieldOptChanged(idx, opt);
    }
}

void
IniDocumentModel::_emitFieldDetailChanged(const QString &detail)
{
    Field *field = qobject_cast<Field *>(QObject::sender());
    if(field != NULL)
    {
        int idx = m_fieldList.indexOf(field);
        emit fieldDetailChanged(idx, detail);
    }
}
