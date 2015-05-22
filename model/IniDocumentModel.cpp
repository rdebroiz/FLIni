#include "IniDocumentModel.h"

#include <QStringList>

#include <QDebug>

IniDocumentModel::IniDocumentModel(QObject *parent) :
    QObject(parent)
{
    m_serviceName = new ServiceName;
    m_fieldList << new Field;
}


IniDocumentModel::~IniDocumentModel()
{
    delete m_serviceName;
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
}

Field*
IniDocumentModel::field(unsigned int index) const
{
    Field *f = NULL;
    if(!index < m_fieldList.count())
        qDebug() << "IniDocumentModel:: Attempt to retrieve non existing field.";
    else
        f = m_fieldList[index];

    return f;
}

QList<Field* >
IniDocumentModel::allFields() const
{
    return m_fieldList;
}

void
IniDocumentModel::insertField(int idx, Field *field)
{
    m_fieldList.insert(idx, field);
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

