#include "FieldDescriptionWidget.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

FieldDescriptionWidget::FieldDescriptionWidget(QWidget *parent) : QGroupBox(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    m_removeFieldButton = new QPushButton(tr("Remove this field"));
    connect(m_removeFieldButton, SIGNAL(clicked()), this, SIGNAL(removeFieldRequest()));
    mainLayout->addWidget(m_removeFieldButton);

    QFormLayout *formLayout = new QFormLayout;
    mainLayout->addLayout(formLayout);

    m_nameLine = new QLineEdit();
    connect(m_nameLine, SIGNAL(textEdited(QString)), this, SIGNAL(nameChanged(QString)));
    formLayout->addRow(new QLabel(tr("Name")), m_nameLine);

    m_typeLine = new QLineEdit();
    connect(m_typeLine, SIGNAL(textEdited(QString)), this, SIGNAL(typeChanged(QString)));
    formLayout->addRow(new QLabel(tr("Type")), m_typeLine);

    m_switchCmdLine = new QLineEdit();
    connect(m_switchCmdLine, SIGNAL(textEdited(QString)), this, SIGNAL(switchCmdChanged(QString)));
    formLayout->addRow(new QLabel(tr("Switch Command")), m_switchCmdLine);

    m_rangeLine = new QLineEdit();
    connect(m_rangeLine, SIGNAL(textEdited(QString)), this, SIGNAL(rangeChanged(QString)));
    formLayout->addRow(new QLabel(tr("Range")), m_rangeLine);

    m_defaultValueLine= new QLineEdit();
    connect(m_defaultValueLine, SIGNAL(textEdited(QString)), this, SIGNAL(defaultValueChanged(QString)));
    formLayout->addRow(new QLabel(tr("Default value")), m_defaultValueLine);

    m_optLine = new QLineEdit();
    connect(m_optLine, SIGNAL(textEdited(QString)), this, SIGNAL(optChanged(QString)));
    formLayout->addRow(new QLabel(tr("Options")), m_optLine);

    m_detailLine = new QLineEdit();
    connect(m_detailLine, SIGNAL(textEdited(QString)), this, SIGNAL(detailChanged(QString)));
    formLayout->addRow(new QLabel(tr("Detail")), m_detailLine);

    m_addNewFieldButton = new QPushButton(tr("Add a new field"));
    connect(m_addNewFieldButton, SIGNAL(clicked()), this, SIGNAL(addFieldRequest()));
    mainLayout->addWidget(m_addNewFieldButton);

}

FieldDescriptionWidget::~FieldDescriptionWidget()
{

}

void
FieldDescriptionWidget::setRemovable(bool ability)
{
    m_removeFieldButton->setEnabled(ability);
}

void
FieldDescriptionWidget::setName(QString const &name)
{
    this->blockSignals(true);
    m_nameLine->setText(name);
    this->blockSignals(false);
}

void
FieldDescriptionWidget::setType(QString const &type)
{
    this->blockSignals(true);
    m_typeLine->setText(type);
    this->blockSignals(false);
}

void
FieldDescriptionWidget::setSwicthCmd(QString const &switchCmd)
{
    this->blockSignals(true);
    m_switchCmdLine->setText(switchCmd);
    this->blockSignals(false);
}

void
FieldDescriptionWidget::setRange(QString const &range)
{
    this->blockSignals(true);
    m_rangeLine->setText(range);
    this->blockSignals(false);
}

void
FieldDescriptionWidget::setDefaultValue(QString const &defaultValue)
{
    this->blockSignals(true);
    m_defaultValueLine->setText(defaultValue);
    this->blockSignals(false);
}

void
FieldDescriptionWidget::setOpt(QString const &opt)
{
    this->blockSignals(true);
    m_optLine->setText(opt);
    this->blockSignals(false);
}

void
FieldDescriptionWidget::setDetail(QString const &detail)
{
    this->blockSignals(true);
    m_detailLine->setText(detail);
    this->blockSignals(false);
}
