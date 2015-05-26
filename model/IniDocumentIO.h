# pragma once

#include <QString>
#include <QStringList>
#include <QSettings>

#include "IniDocumentModel.h"

#include <QDebug>

namespace IniDocumentIO
{

IniDocumentModel* read(const QString &filename)
{
    IniDocumentModel *model = new IniDocumentModel();

    QSettings settings(filename, QSettings::IniFormat, NULL);
    QStringList groups = settings.childGroups();

    if(groups.contains("ServiceName"))
        groups.removeAll("ServiceName");

    IniGroup *serviceName = model->serviceName();

    settings.beginGroup("ServiceName");
    foreach (QString key, settings.childKeys())
        serviceName->setEntry(key, settings.value(key, QString()).toString());
    settings.endGroup();

    QRegExp numberRx("Field_(\\d+)");
    foreach(QString fieldName, groups)
    {
        int pos = numberRx.indexIn(fieldName);

        int fieldNumber = -1;
        if (pos > -1)
            fieldNumber = numberRx.cap(1).toInt();
        else
        {
            qDebug() << "Invalid key found in file: " << filename << " -> " << fieldName;
            continue;
        }

        // fill model if field is valid
        if(fieldNumber > 0)
        {
            unsigned int fieldIndex = fieldNumber -1;

            IniGroup *field = model->field(fieldIndex);
            if(!field)
                field = model->insertField(fieldIndex);

            settings.beginGroup(fieldName);
            foreach (QString key, settings.childKeys())
                serviceName->setEntry(key, settings.value(key, QString()).toString());
            settings.endGroup();
        }
    }

    return model;
}

QString write(IniDocumentModel *model)
{
    QString text;

    if(model)
    {
        IniGroup *serviceName = model->serviceName();
        QList<IniGroup*> fields = model->allFields();

        text += "[ServiceName]\n";
        text += "name=" + serviceName->entry("name") + ";\n";
        text += "exeType=" + serviceName->entry("exeType") + ";\n";
        text += "path=" + serviceName->entry("path") + ";\n";
        text += "mainFunction=" + serviceName->entry("mainFunction") + ";\n";
        text += "detail=" + serviceName->entry("detail") + ";\n\n";

        int end = fields.count();
        for(int idx = 0; idx < end; ++idx)
        {
            text += "[Field_" + QString::number(idx + 1) + "]\n";
            text += "name=" + fields[idx]->entry("name") + ";\n";
            text += "type=" + fields[idx]->entry("type") + ";\n";
            text += "switchCmd=" + fields[idx]->entry("switchCmd") + ";\n";
            text += "range=" + fields[idx]->entry("range") + ";\n";
            text += "defaultValue=" + fields[idx]->entry("defaultValue") + ";\n";
            text += "opt=" + fields[idx]->entry("opt") + ";\n";
            text += "detail=" + fields[idx]->entry("detail") + ";\n\n";
        }
    }
    return text;
}

}// end of namespace IniDocumentIO
