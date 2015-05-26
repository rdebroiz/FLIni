#pragma once

#include <QGroupBox>

#include <QLineEdit>

#include "IniDocumentModel.h"

class FieldDescriptionWidget : public QGroupBox
{
    Q_OBJECT

private:
    QLineEdit *m_nameLine;
    QLineEdit *m_typeLine;
    QLineEdit *m_switchCmdLine;
    QLineEdit *m_rangeLine;
    QLineEdit *m_defaultValueLine;
    QLineEdit *m_optLine;
    QLineEdit *m_detailLine;

public:
    FieldDescriptionWidget(QWidget *parent = NULL);
    virtual ~FieldDescriptionWidget();

public slots:
    void setName(QString const &name);
    void setType(QString const &type);
    void setSwicthCmd(QString const &switchCmd);
    void setRange(QString const &range);
    void setDefaultValue(QString const &defaultValue);
    void setOpt(QString const &opt);
    void setDetail(QString const &detail);


signals:
    void addFieldRequest();
    void removeFieldRequest();

    void nameChanged(QString const&);
    void typeChanged(QString const&);
    void switchCmdChanged(QString const&);
    void rangeChanged(QString const&);
    void defaultValueChanged(QString const&);
    void optChanged(QString const&);
    void detailChanged(QString const&);
};
