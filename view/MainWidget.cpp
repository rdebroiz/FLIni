#include "MainWidget.h"

#include "ServiceDescriptionWidget.h"
#include "CommandWidget.h"
#include "DocumentPreviewWidget.h"
#include "FieldListWidget.h"

#include <QSplitter>

#include <QLabel>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    QSplitter *splitter = new QSplitter();
    mainLayout->addWidget(splitter);

    QWidget *leftPannelWidget = new QWidget();
    QWidget *rightPannelWidget = new QWidget();
    leftPannelWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    rightPannelWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);

    splitter->addWidget(leftPannelWidget);
    splitter->addWidget(rightPannelWidget);

    m_leftPannelLayout = new QVBoxLayout();
    m_rightPannelLayout = new QVBoxLayout();
    leftPannelWidget->setLayout(m_leftPannelLayout);
    rightPannelWidget->setLayout(m_rightPannelLayout);
}

MainWidget::~MainWidget()
{

}

void
MainWidget::setServiceDescriptionWidget(ServiceDescriptionWidget *widget)
{
//    if(QLayoutItem *itm = m_leftPannelLayout->itemAt(0))
//    {
//        delete itm->widget();
//    }
    m_leftPannelLayout->insertWidget(0, widget, Qt::AlignTop);
    widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum);
}

void
MainWidget::setFieldListWidget(FieldListWidget *widget)
{
    m_leftPannelLayout->addWidget(widget, 0, Qt::AlignTop);
    widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum);
}

void
MainWidget::setCommandWidget(CommandWidget *widget)
{
    if(QLayoutItem *itm = m_rightPannelLayout->itemAt(0))
        delete itm->widget();
    m_rightPannelLayout->insertWidget(0, widget, Qt::AlignTop);
    widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
}

void
MainWidget::setDocumentPreviewDescriptionWidget(DocumentPreviewWidget *widget)
{
    if(QLayoutItem *itm = m_rightPannelLayout->itemAt(1))
        delete itm->widget();
    m_rightPannelLayout->insertWidget(1, widget);
    widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum);
}


