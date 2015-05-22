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

    ServiceName *serviceName = model->serviceName();
    serviceName->name = settings.value("ServiceName/name", QString()).toString();
    serviceName->exeType = settings.value("ServiceName/exeType", QString()).toString();
    serviceName->path = settings.value("ServiceName/path", QString()).toString();
    serviceName->mainFunction = settings.value("ServiceName/mainFunction", QString()).toString();
    serviceName->detail = settings.value("ServiceName/detail", QString()).toString();

    //update model
    model->setServiceName(serviceName);

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

            Field *field = model->field(fieldIndex);
            if(!field)
                field = new Field;
            settings.beginGroup(fieldName);
            field->name = settings.value("name", QString()).toString();
            field->type = settings.value("type", QString()).toString();
            field->switchCmd = settings.value("switchCmd", QString()).toString();
            field->range = settings.value("range", QString()).toString();
            field->defaultValue = settings.value("defaultValue", QString()).toString();
            field->opt = settings.value("opt", QString()).toString();
            field->detail = settings.value("detail", QString()).toString();
            settings.endGroup();

            model->insertField(fieldIndex, field);
        }
    }

    return model;
}

QString write(IniDocumentModel *model)
{
    QString text;

    if(model)
    {
        ServiceName *srv = model->serviceName();
        QList<Field*> fldList = model->allFields();

        text += "[ServiceName]\n";
        text += "name=" + srv->name + ";\n";
        text += "exeType=" + srv->exeType + ";\n";
        text += "path=" + srv->path + ";\n";
        text += "mainFunction=" + srv->mainFunction+ ";\n";
        text += "detail=" + srv->detail + ";\n\n";

        int end = fldList.count();
        for(int idx = 0; idx < end; ++idx)
        {
            text += "[Field_" + QString::number(idx + 1) + "]\n";
            text += "name=" + fldList[idx]->name + ";\n";
            text += "type=" + fldList[idx]->type+ ";\n";
            text += "switchCmd=" + fldList[idx]->switchCmd + ";\n";
            text += "range=" + fldList[idx]->range + ";\n";
            text += "defaultValue=" + fldList[idx]->defaultValue + ";\n";
            text += "opt=" + fldList[idx]->opt + ";\n";
            text += "detail=" + fldList[idx]->detail + ";\n\n";
        }
    }
    return text;
}

}// end of namespace IniDocumentIO
