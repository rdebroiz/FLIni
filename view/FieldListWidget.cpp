#include "FieldListWidget.h"

#include "FieldDescriptionWidget.h"

FieldListWidget::FieldListWidget(QWidget *parent): QScrollArea(parent)
{
    m_mainLayout = new QVBoxLayout;
    this->setLayout(m_mainLayout);
}

FieldListWidget::~FieldListWidget()
{

}

void
FieldListWidget::addFieldDescriptionWidget(FieldDescriptionWidget *widget)
{
    this->insertFieldDescriptionWidget(m_fieldWidgetList.count(), widget);
}

void
FieldListWidget::insertFieldDescriptionWidget(int index, FieldDescriptionWidget *widget)
{
    m_fieldWidgetList.insert(index, widget);
    m_mainLayout->insertWidget(index, widget);
}

void
FieldListWidget::removeFieldDescriptionWidget(FieldDescriptionWidget *widget)
{
    m_fieldWidgetList.removeAll(widget);
    m_mainLayout->removeWidget(widget);

    widget->deleteLater();
}
