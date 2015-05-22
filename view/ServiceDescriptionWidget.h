#pragma once

#include <QGroupBox>

#include "IniDocumentModel.h"

#include <QLineEdit>
#include <QTextEdit>


class ServiceDescriptionWidget : public QGroupBox
{
    Q_OBJECT

private:
    QLineEdit *m_nameLine;
    QLineEdit *m_exTypeLine;
    QLineEdit *m_pathLine;
    QLineEdit *m_mainFunctionLine;
    QLineEdit *m_detailLine;

public:
    ServiceDescriptionWidget(QWidget *parent = NULL);
    virtual ~ServiceDescriptionWidget();

    void setName(QString const &name);
    void setExeType(QString const &exeType);
    void setPath(QString const &path);
    void setMainFunction(QString const &mainFunction);
    void setDetail(QString const &detail);

    void fillFromServiceName(ServiceName const &serviceName);

signals:
    void nameChanged(QString name);
    void exeTypeChanged(QString name);
    void pathChanged(QString name);
    void mainFunctionChanged(QString name);
    void detailChanged(QString name);
};
