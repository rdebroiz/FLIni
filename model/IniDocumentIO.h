# pragma once

#include <QString>
#include <QStringList>
#include <QSettings>
#include <QFile>

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
    serviceName->setName(settings.value("ServiceName/name", QString()).toString());
    serviceName->setExeType(settings.value("ServiceName/exeType", QString()).toString());
    serviceName->setPath(settings.value("ServiceName/path", QString()).toString());
    serviceName->setMainFunction(settings.value("ServiceName/mainFunction", QString()).toString());
    serviceName->setDetail(settings.value("ServiceName/detail", QString()).toString());

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
                field = model->insertField(fieldIndex);
            settings.beginGroup(fieldName);
            field->setName(settings.value("name", QString()).toString());
            field->setType(settings.value("type", QString()).toString());
            field->setSwitchCmd(settings.value("switchCmd", QString()).toString());
            field->setRange(settings.value("range", QString()).toString());
            field->setDefaultValue(settings.value("defaultValue", QString()).toString());
            field->setOpt(settings.value("opt", QString()).toString());
            field->setDetail(settings.value("detail", QString()).toString());
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
        ServiceName *srv = model->serviceName();
        QList<Field*> fldList = model->allFields();

        text += "[ServiceName]\n";
        text += "name=" + srv->name() + ";\n";
        text += "exeType=" + srv->exeType() + ";\n";
        text += "path=" + srv->path() + ";\n";
        text += "mainFunction=" + srv->mainFunction() + ";\n";
        text += "detail=" + srv->detail() + ";\n\n";

        int end = fldList.count();
        for(int idx = 0; idx < end; ++idx)
        {
            text += "[Field_" + QString::number(idx + 1) + "]\n";
            text += "name=" + fldList[idx]->name() + ";\n";
            text += "type=" + fldList[idx]->type() + ";\n";
            text += "switchCmd=" + fldList[idx]->switchCmd() + ";\n";
            text += "range=" + fldList[idx]->range() + ";\n";
            text += "defaultValue=" + fldList[idx]->defaultValue() + ";\n";
            text += "opt=" + fldList[idx]->opt() + ";\n";
            text += "detail=" + fldList[idx]->detail() + ";\n\n";
        }
    }
    return text;
}

QString write(IniDocumentModel *model, QString const& filename)
{
    QString text = write(model);

    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream << text;
    file.close();

    return text;
}

}// end of namespace IniDocumentIO
