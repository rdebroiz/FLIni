#include "IniDocumentPresenter.h"

#include "IniDocumentModel.h"
#include "IniDocumentIO.h"

#include "MainWidget.h"
#include "CommandWidget.h"
#include "DocumentPreviewWidget.h"
#include "ServiceDescriptionWidget.h"
#include "FieldDescriptionWidget.h"
#include "FieldListWidget.h"

#include <QDebug>

IniDocumentPresenter::IniDocumentPresenter(QObject *parent) :
    QObject(parent)
{
    m_model = NULL;
    this->setModel(IniDocumentIO::read("/home/rdebroiz/florent/AnimaNLMeans.ini"));
}


IniDocumentPresenter::~IniDocumentPresenter()
{

}

void
IniDocumentPresenter::setModel(IniDocumentModel *model)
{
    if(!m_model.isNull())
    {
        delete m_model;
    }

    m_model = model;
    m_model->setParent(this);
}

IniDocumentModel*
IniDocumentPresenter::model()
{
    return m_model;
}

MainWidget*
IniDocumentPresenter::mainWidget() const
{
    return this->_buildMainWidget();
}

ServiceDescriptionWidget*
IniDocumentPresenter::serviceDescriptionWidget() const
{
    return this->_buildServiceDescriptionWidget();
}

CommandWidget*
IniDocumentPresenter::commandWidget()const
{
  return this->_buildCommandWidget();
}

DocumentPreviewWidget*
IniDocumentPresenter::documentPreviewWidget() const
{
    return this->_buildDocumentPreviewWidget();
}

void
IniDocumentPresenter::changeSNName(QString const &name)
{
    if(!m_model.isNull())
    {
        m_model->serviceName()->name = name;
         emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeSNExeType(QString const &exeType)
{
    if(!m_model.isNull())
    {
        m_model->serviceName()->exeType = exeType;
         emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeSNPath(QString const &path)
{
    if(!m_model.isNull())
    {
        m_model->serviceName()->path = path;
         emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeSNMainFunction(QString const &mainFunction)
{
    if(!m_model.isNull())
    {
        m_model->serviceName()->mainFunction = mainFunction;
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeSNDetail(QString const &detail)
{
    if(!m_model.isNull())
    {
        m_model->serviceName()->detail = detail;
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::openIniDocument(const QString &filename)
{

    this->setModel(IniDocumentIO::read(filename));

    emit modelPathChanged(filename);
    emit modelContentChanged(IniDocumentIO::write(m_model));
}

MainWidget*
IniDocumentPresenter::_buildMainWidget() const
{
    MainWidget *mainWidget = new MainWidget;

    mainWidget->setCommandWidget(this->_buildCommandWidget());
    mainWidget->setServiceDescriptionWidget(this->_buildServiceDescriptionWidget());
    mainWidget->setDocumentPreviewDescriptionWidget(this->_buildDocumentPreviewWidget());
    mainWidget->setFieldListWidget(this->_buildFieldListWidget());

    return mainWidget;
}

CommandWidget*
IniDocumentPresenter::_buildCommandWidget() const
{
    CommandWidget* commandWidget = new CommandWidget;

    connect(commandWidget, SIGNAL(openFileRequest(QString)),
            this, SLOT(openIniDocument(QString)));

    return commandWidget;
}

ServiceDescriptionWidget*
IniDocumentPresenter::_buildServiceDescriptionWidget() const
{
    ServiceDescriptionWidget* serviceDescriptionWidget = new ServiceDescriptionWidget;

    if(!m_model.isNull())
    {
        ServiceName *serviceName = m_model->serviceName();
        serviceDescriptionWidget = new ServiceDescriptionWidget;
        serviceDescriptionWidget->setName(serviceName->name);
        serviceDescriptionWidget->setExeType(serviceName->exeType);
        serviceDescriptionWidget->setPath(serviceName->path);
        serviceDescriptionWidget->setMainFunction(serviceName->mainFunction);
        serviceDescriptionWidget->setDetail(serviceName->detail);
    }

    connect(serviceDescriptionWidget, SIGNAL(nameChanged(QString)),
            this, SLOT(changeSNName(QString)));
    connect(serviceDescriptionWidget, SIGNAL(exeTypeChanged(QString)),
            this, SLOT(changeSNExeType(QString)));
    connect(serviceDescriptionWidget, SIGNAL(pathChanged(QString)),
            this, SLOT(changeSNPath(QString)));
    connect(serviceDescriptionWidget, SIGNAL(mainFunctionChanged(QString)),
            this, SLOT(changeSNMainFunction(QString)));
    connect(serviceDescriptionWidget, SIGNAL(detailChanged(QString)),
            this, SLOT(changeSNDetail(QString)));

    return serviceDescriptionWidget;
}

FieldDescriptionWidget*
IniDocumentPresenter::_buildFieldDescriptionWidget() const
{
    FieldDescriptionWidget *fieldDescriptionWidget = new FieldDescriptionWidget;

    return fieldDescriptionWidget;
}

FieldListWidget*
IniDocumentPresenter::_buildFieldListWidget() const
{
    FieldListWidget *fieldListWidget = new FieldListWidget;
    if(!m_model.isNull())
    {
        foreach(Field *field, m_model->allFields())
        {
            FieldDescriptionWidget *fieldDescriptionWidget = this->_buildFieldDescriptionWidget();

            fieldListWidget->addFieldDescriptionWidget(fieldDescriptionWidget);
        }
    }

    return fieldListWidget;
}

DocumentPreviewWidget*
IniDocumentPresenter::_buildDocumentPreviewWidget() const
{
    DocumentPreviewWidget* documentPreviewWidget = new DocumentPreviewWidget;

    if(!m_model.isNull())
    {
        documentPreviewWidget->setPath(m_model->filename());
        documentPreviewWidget->setContent(IniDocumentIO::write(m_model));
    }

    connect(this, SIGNAL(modelContentChanged(QString)),
            documentPreviewWidget, SLOT(setContent(QString)));
    connect(this, SIGNAL(modelPathChanged(QString)),
            documentPreviewWidget, SLOT(setPath(QString)));

    return documentPreviewWidget;
}
