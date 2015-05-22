#include "ServiceDescriptionWidget.h"

#include <QFormLayout>
#include <QLabel>

ServiceDescriptionWidget::ServiceDescriptionWidget(QWidget *parent) : QGroupBox(parent)
{
    QFormLayout *mainLayout = new QFormLayout();
    this->setLayout(mainLayout);

    this->setTitle(tr("Service Description"));

    m_nameLine = new QLineEdit();
    connect(m_nameLine, SIGNAL(textEdited(QString)), this, SIGNAL(nameChanged(QString)));
    mainLayout->addRow(new QLabel(tr("Name")), m_nameLine);

    m_exTypeLine = new QLineEdit();
    connect(m_exTypeLine, SIGNAL(textEdited(QString)), this, SIGNAL(exeTypeChanged(QString)));
    mainLayout->addRow(new QLabel(tr("Exe Type")), m_exTypeLine);

    m_pathLine = new QLineEdit();
    connect(m_pathLine, SIGNAL(textEdited(QString)), this, SIGNAL(pathChanged(QString)));
    mainLayout->addRow(new QLabel(tr("Path")), m_pathLine);

    m_mainFunctionLine = new QLineEdit();
    connect(m_mainFunctionLine, SIGNAL(textEdited(QString)), this, SIGNAL(mainFunctionChanged(QString)));
    mainLayout->addRow(new QLabel(tr("Main function")), m_mainFunctionLine);

    m_detailLine = new QLineEdit();
    connect(m_detailLine, SIGNAL(textEdited(QString)), this, SIGNAL(detailChanged(QString)));
    mainLayout->addRow(new QLabel(tr("Details")), m_detailLine);

}

ServiceDescriptionWidget::~ServiceDescriptionWidget()
{

}

void
ServiceDescriptionWidget::setName(QString const &name)
{
    m_nameLine->setText(name);
}

void
ServiceDescriptionWidget::setExeType(QString const &exeType)
{
    m_exTypeLine->setText(exeType);
}

void
ServiceDescriptionWidget::setPath(QString const &path)
{
    m_pathLine->setText(path);
}

void
ServiceDescriptionWidget::setMainFunction(QString const &mainFunction)
{
     m_mainFunctionLine->setText(mainFunction);
}

void
ServiceDescriptionWidget::setDetail(QString const &detail)
{
    m_detailLine->setText(detail);
}

void
ServiceDescriptionWidget::fillFromServiceName(const ServiceName &serviceName)
{
    this->setName(serviceName.name);
    this->setExeType(serviceName.exeType);
    this->setPath(serviceName.path);
    this->setMainFunction(serviceName.mainFunction);
    this->setDetail(serviceName.detail);
}
