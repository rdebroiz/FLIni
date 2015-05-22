#pragma once

#include <QGroupBox>

#include <QLineEdit>

#include "IniDocumentModel.h"

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

public slots:
    void setName(QString const &name);
    void setExeType(QString const &exeType);
    void setPath(QString const &path);
    void setMainFunction(QString const &mainFunction);
    void setDetail(QString const &detail);


signals:
    void nameChanged(QString const&);
    void exeTypeChanged(QString const&);
    void pathChanged(QString const&);
    void mainFunctionChanged(QString const&);
    void detailChanged(QString const&);
};
