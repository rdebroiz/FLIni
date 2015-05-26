#pragma once

#include <QScrollArea>
#include <QVBoxLayout>

class FieldDescriptionWidget;

class FieldListWidget: public QScrollArea
{
    Q_OBJECT

private:
    QList<FieldDescriptionWidget *> m_fieldWidgetList;
    QVBoxLayout *m_mainLayout;

public:
    FieldListWidget(QWidget *parent = NULL);
    virtual ~FieldListWidget();

public slots:
    FieldDescriptionWidget* insertFieldDescriptionWidget(unsigned int index);
    FieldDescriptionWidget* addFieldDescriptionWidget();
    void removeFieldDescriptionWidget(unsigned idx);
    void clear();

    void setName(unsigned int idx, QString const&  name);
    void setType(unsigned int idx, QString const&  type);
    void setSwitchCmd(unsigned int idx, QString const&  switchCmd);
    void setRange(unsigned int idx, QString const&  range);
    void setDefaultValue(unsigned int idx, QString const&  defaultValue);
    void setOpt(unsigned int idx, QString const&  opt);
    void setDetail(unsigned int idx, QString const&  detail);

signals:
    void addFieldRequest(unsigned int);
    void removeFieldRequest(unsigned int);

    void nameChanged(unsigned int, QString const&);
    void typeChanged(unsigned int, QString const&);
    void switchCmdChanged(unsigned int, QString const&);
    void rangeChanged(unsigned int, QString const&);
    void defaultValueChanged(unsigned int, QString const&);
    void optChanged(unsigned int, QString const&);
    void detailChanged(unsigned int, QString const&);

private:
    void _updateTitles();

private slots:
    void _emitAddFieldRequest();
    void _emitRemoveFieldRequest();
    void _emitNameChanged(QString const& name);
    void _emitTypeChanged(QString const& type);
    void _emitSwitchCmdChanged(QString const& switchCmd);
    void _emitRangeChanged(QString const&  range);
    void _emitDefaultValueChanged(QString const& defaultValue);
    void _emitOptChanged(QString const& opt);
    void _emitDetailChanged(QString const& detail);
};
