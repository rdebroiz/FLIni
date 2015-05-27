#include "MainWidget.h"

#include "ServiceDescriptionWidget.h"
#include "CommandWidget.h"
#include "DocumentPreviewWidget.h"
#include "FieldListWidget.h"

#include <QSplitter>
#include <QScrollArea>
#include <QLabel>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    QSplitter *splitter = new QSplitter();
    mainLayout->addWidget(splitter);

    QScrollArea *leftPannelWidget = new QScrollArea;
    QFrame *leftPannelContainer = new QFrame;

    leftPannelContainer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    leftPannelWidget->setWidget(leftPannelContainer);

    leftPannelWidget->setFrameStyle(QFrame::NoFrame);
    leftPannelWidget->setAttribute(Qt::WA_MacShowFocusRect, false);
    leftPannelWidget->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    leftPannelWidget->setWidgetResizable(true);

    leftPannelWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    leftPannelWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    leftPannelWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);

    m_leftPannelLayout = new QVBoxLayout();
    leftPannelContainer->setLayout(m_leftPannelLayout);
    m_leftPannelLayout->setSizeConstraint(QLayout::SetMinimumSize);


    QWidget *rightPannelWidget = new QWidget();
    leftPannelWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    rightPannelWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);

    splitter->addWidget(leftPannelWidget);
    splitter->addWidget(rightPannelWidget);

    m_rightPannelLayout = new QVBoxLayout();
    rightPannelWidget->setLayout(m_rightPannelLayout);
}

MainWidget::~MainWidget()
{

}

void
MainWidget::setServiceDescriptionWidget(ServiceDescriptionWidget *widget)
{
    if(m_leftPannelLayout->count() > 1)
    {
        QLayoutItem *itm = m_leftPannelLayout->takeAt(0);
        if(itm->widget() != NULL)
            itm->widget()->deleteLater();
    }
    m_leftPannelLayout->insertWidget(0, widget, Qt::AlignTop);
    widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
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
    {
        if(itm->widget() != NULL)
            itm->widget()->deleteLater();
    }
    m_rightPannelLayout->insertWidget(0, widget, Qt::AlignTop);
    widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
}

void
MainWidget::setDocumentPreviewDescriptionWidget(DocumentPreviewWidget *widget)
{
    if(QLayoutItem *itm = m_rightPannelLayout->itemAt(1))
    {
        if(itm->widget() != NULL)
            itm->widget()->deleteLater();
    }
    m_rightPannelLayout->insertWidget(1, widget);
    widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum);
}


