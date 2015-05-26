#include "IniDocumentModel.h"

#include <QStringList>

#include <QDebug>

// IniGroup ------------------------------------------------

QString

IniGroup::keys()
{
    return m_keys;
}

IniGroup::entry(const QString &key) const
{
    return m_entries[key];
}

void
IniGroup::setEntry(const QString &key, const QString &value)
{
    if(!m_keys.contains(key))
        m_keys << key;
    m_entries[key] = value;
    emit entryChanged(key, value);
}

// IninDocumentModel ---------------------------------------

IniDocumentModel::IniDocumentModel(QObject *parent) :
    QObject(parent)
{
    m_serviceName = new IniGroup(this);
    m_serviceName->setEntry("name", "");
    m_serviceName->setEntry("exeType", "");
    m_serviceName->setEntry("path", "");
    m_serviceName->setEntry("mainFunction", "");
    m_serviceName->setEntry("detail", "");

    this->insertField(0);
}


IniDocumentModel::~IniDocumentModel()
{
    delete m_serviceName;
    // QList auto deallocate raw pointer in destructor.
    m_fields.clear();
}

ServiceName*
IniDocumentModel::serviceName() const
{
    return m_serviceName;
}

void
IniDocumentModel::setServiceName(IniGroup* serviceName)
{
    m_serviceName = serviceName;
    connect(m_serviceName, SIGNAL(entryChanged(QString,QString)),
            this, SIGNAL(serviceNameChanged(QString, QString)));
}

IniGroup*
IniDocumentModel::field(unsigned int idx) const
{
    IniGroup *f = NULL;
    if(!(index < m_fieldList.count()))
//        qDebug() << "IniDocumentModel:: Attempt to retrieve non existing field.";
        ;
    else
        f = m_fields[idx];

    return f;
}

QList<IniGroup* >
IniDocumentModel::allFields() const
{
    return m_fields;
}

IniGroup*
IniDocumentModel::insertField(unsigned int idx)
{
    IniGroup* field = new IniGroup(this);
    field->setEntry("name", "");
    field->setEntry("type", "");
    field->setEntry("switchCmd", "");
    field->setEntry("range", "");
    field->setEntry("defaultValue", "");
    field->setEntry("opt", "");
    field->setEntry("detail", "");

    m_fields.insert(idx, field);

    connect(field, SIGNAL(entryChanged(QString,QString)),
            this, SLOT(_emitFieldChanged(QString,QString)));

    emit fieldAdded(idx);
    return field;
}

void
IniDocumentModel::removeField(unsigned int idx)
{
    m_fields.removeAt(idx);
    emit fiedRemoved(idx);
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
    emit filenameChanged(filename);
}

void
IniDocumentModel::_emitFieldChanged(const QString &key, const QString &value)
{
    IniGroup *field = qobject_cast<IniGroup *>(QObject::sender());
    if(field)
    {
        int idx = m_fields.indexOf(field);
        emit fieldNameChanged(idx, key, value);
    }
}
