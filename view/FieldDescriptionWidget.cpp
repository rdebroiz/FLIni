#include "FieldDescriptionWidget.h"

#include <QPushButton>

FieldDescriptionWidget::FieldDescriptionWidget(QWidget *parent) : QGroupBox(parent)
{
    m_mainLayout = new QVBoxLayout();
    this->setLayout(m_mainLayout);

    QPushButton *removeFieldButton = new QPushButton(tr("Remove this field"));
    connect(removeFieldButton, SIGNAL(clicked()), this, SIGNAL(removeFieldRequest()));
    m_mainLayout->addWidget(removeFieldButton);

    QPushButton *addNewFieldButton = new QPushButton(tr("Add a new field"));
    connect(addNewFieldButton, SIGNAL(clicked()), this, SIGNAL(newFieldRequest()));
    m_mainLayout->addWidget(addNewFieldButton);

}

FieldDescriptionWidget::~FieldDescriptionWidget()
{

}
