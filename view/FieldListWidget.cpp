#include "FieldListWidget.h"

#include "FieldDescriptionWidget.h"

#include <QDebug>

FieldListWidget::FieldListWidget(QWidget *parent): QWidget(parent)
{

    m_mainLayout = new QVBoxLayout;
    this->setLayout(m_mainLayout);
}

FieldListWidget::~FieldListWidget()
{

}

FieldDescriptionWidget*
FieldListWidget::insertFieldDescriptionWidget(unsigned int index)
{
    FieldDescriptionWidget *widget = new FieldDescriptionWidget;
    widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);

    m_fieldWidgetList.insert(index, widget);
    m_mainLayout->setStretch(m_mainLayout->count() - 1, 0);
    m_mainLayout->insertWidget(index, widget, 0, Qt::AlignTop);
    m_mainLayout->addStretch(1);

    connect(widget, SIGNAL(addFieldRequest()),
            this, SLOT(_emitAddFieldRequest()));
    connect(widget, SIGNAL(removeFieldRequest()),
            this, SLOT(_emitRemoveFieldRequest()));
    connect(widget, SIGNAL(nameChanged(QString)),
            this, SLOT(_emitNameChanged(QString)));
    connect(widget, SIGNAL(typeChanged(QString)),
            this, SLOT(_emitTypeChanged(QString)));
    connect(widget, SIGNAL(switchCmdChanged(QString)),
            this, SLOT(_emitSwitchCmdChanged(QString)));
    connect(widget, SIGNAL(rangeChanged(QString)),
            this, SLOT(_emitRangeChanged(QString)));
    connect(widget, SIGNAL(defaultValueChanged(QString)),
            this, SLOT(_emitDefaultValueChanged(QString)));
    connect(widget, SIGNAL(optChanged(QString)),
            this, SLOT(_emitOptChanged(QString)));
    connect(widget, SIGNAL(detailChanged(QString)),
            this, SLOT(_emitDetailChanged(QString)));

    this->_updateTitles();
    this->_updateRemoveAbility();

    return widget;
}

FieldDescriptionWidget*
FieldListWidget::addFieldDescriptionWidget()
{
    return this->insertFieldDescriptionWidget(m_fieldWidgetList.count());
}

void
FieldListWidget::removeFieldDescriptionWidget(unsigned int idx)
{
    m_fieldWidgetList.removeAt(idx);
    QLayoutItem *itm = m_mainLayout->takeAt(idx);
    itm->widget()->deleteLater();

    this->_updateTitles();
    this->_updateRemoveAbility();
}

void
FieldListWidget::clear()
{
    m_fieldWidgetList.clear();
    while(QLayoutItem *itm = m_mainLayout->takeAt(0))
        itm->widget()->deleteLater();
}

void
FieldListWidget::_updateTitles()
{
    int end = m_fieldWidgetList.count();
    for(int i = 0; i < end; ++i)
    {
        m_fieldWidgetList[i]->setTitle(tr("Field ") + QString::number(i+1));
    }
}

void
FieldListWidget::_updateRemoveAbility()
{
    m_fieldWidgetList[0]->setRemovable(false);

    int end = m_fieldWidgetList.count();
    for(int i = 1; i < end; ++i)
    {
        m_fieldWidgetList[i]->setRemovable(true);
    }
}

void
FieldListWidget::setName(unsigned int idx, QString const&  name)
{
    this->blockSignals(true);
    if(idx < m_fieldWidgetList.count())
        m_fieldWidgetList[idx]->setName(name);
    this->blockSignals(false);
}

void
FieldListWidget::setType(unsigned int idx, QString const&  type)
{
    this->blockSignals(true);
    if(idx < m_fieldWidgetList.count())
        m_fieldWidgetList[idx]->setType(type);
    this->blockSignals(false);
}

void
FieldListWidget::setSwitchCmd(unsigned int idx, QString const&  switchCmd)
{
    this->blockSignals(true);
    if(idx < m_fieldWidgetList.count())
        m_fieldWidgetList[idx]->setSwicthCmd(switchCmd);
    this->blockSignals(false);
}

void
FieldListWidget::setRange(unsigned int idx, QString const&  range)
{
    this->blockSignals(true);
    if(idx < m_fieldWidgetList.count())
        m_fieldWidgetList[idx]->setRange(range);
    this->blockSignals(false);
}


void
FieldListWidget::setDefaultValue(unsigned int idx, QString const&  defaultValue)
{
    this->blockSignals(true);
    if(idx < m_fieldWidgetList.count())
        m_fieldWidgetList[idx]->setDefaultValue(defaultValue);
    this->blockSignals(false);
}

void
FieldListWidget::setOpt(unsigned int idx, QString const&  opt)
{
    this->blockSignals(true);
    if(idx < m_fieldWidgetList.count())
        m_fieldWidgetList[idx]->setOpt(opt);
    this->blockSignals(false);
}

void
FieldListWidget::setDetail(unsigned int idx, QString const&  detail)
{
    this->blockSignals(true);
    if(idx < m_fieldWidgetList.count())
        m_fieldWidgetList[idx]->setDetail(detail);
    this->blockSignals(false);
}

void
FieldListWidget::_emitAddFieldRequest()
{
    FieldDescriptionWidget *fieldDescriptionWidget = qobject_cast<FieldDescriptionWidget *>(QObject::sender());
    if(fieldDescriptionWidget)
    {
        int idx = m_fieldWidgetList.indexOf(fieldDescriptionWidget);
        emit addFieldRequest(idx);
    }
}

void
FieldListWidget::_emitRemoveFieldRequest()
{
    FieldDescriptionWidget *fieldDescriptionWidget = qobject_cast<FieldDescriptionWidget *>(QObject::sender());
    if(fieldDescriptionWidget)
    {
        int idx = m_fieldWidgetList.indexOf(fieldDescriptionWidget);
        emit removeFieldRequest(idx);
    }
}

void
FieldListWidget::_emitNameChanged(QString const& name)
{
    FieldDescriptionWidget *fieldDescriptionWidget = qobject_cast<FieldDescriptionWidget *>(QObject::sender());
    if(fieldDescriptionWidget)
    {
        int idx = m_fieldWidgetList.indexOf(fieldDescriptionWidget);
        emit nameChanged(idx, name);
    }
}

void
FieldListWidget::_emitTypeChanged(QString const& type)
{
    FieldDescriptionWidget *fieldDescriptionWidget = qobject_cast<FieldDescriptionWidget *>(QObject::sender());
    if(fieldDescriptionWidget)
    {
        int idx = m_fieldWidgetList.indexOf(fieldDescriptionWidget);
        emit typeChanged(idx, type);
    }
}

void
FieldListWidget::_emitSwitchCmdChanged(QString const& switchCmd)
{
    FieldDescriptionWidget *fieldDescriptionWidget = qobject_cast<FieldDescriptionWidget *>(QObject::sender());
    if(fieldDescriptionWidget)
    {
        int idx = m_fieldWidgetList.indexOf(fieldDescriptionWidget);
        emit switchCmdChanged(idx, switchCmd);
    }
}

void
FieldListWidget::_emitRangeChanged(QString const&  range)
{
    FieldDescriptionWidget *fieldDescriptionWidget = qobject_cast<FieldDescriptionWidget *>(QObject::sender());
    if(fieldDescriptionWidget)
    {
        int idx = m_fieldWidgetList.indexOf(fieldDescriptionWidget);
        emit rangeChanged(idx, range);
    }
}

void
FieldListWidget::_emitDefaultValueChanged(QString const& defaultValue)
{
    FieldDescriptionWidget *fieldDescriptionWidget = qobject_cast<FieldDescriptionWidget *>(QObject::sender());
    if(fieldDescriptionWidget)
    {
        int idx = m_fieldWidgetList.indexOf(fieldDescriptionWidget);
        emit defaultValueChanged(idx, defaultValue);
    }
}

void
FieldListWidget::_emitOptChanged(QString const& opt)
{
    FieldDescriptionWidget *fieldDescriptionWidget = qobject_cast<FieldDescriptionWidget *>(QObject::sender());
    if(fieldDescriptionWidget)
    {
        int idx = m_fieldWidgetList.indexOf(fieldDescriptionWidget);
        emit optChanged(idx, opt);
    }
}

void
FieldListWidget::_emitDetailChanged(QString const& detail)
{
    FieldDescriptionWidget *fieldDescriptionWidget = qobject_cast<FieldDescriptionWidget *>(QObject::sender());
    if(fieldDescriptionWidget)
    {
        int idx = m_fieldWidgetList.indexOf(fieldDescriptionWidget);
        emit detailChanged(idx, detail);
    }
}
