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
this->setModel(new IniDocumentModel);
}


IniDocumentPresenter::~IniDocumentPresenter()
{

}

void
IniDocumentPresenter::setModel(IniDocumentModel *model)
{
    if(!m_model.isNull())
    {
        m_model->deleteLater();
    }

    m_model = model;
    m_model->setParent(this);

    emit modelChanged();

    emit serviceNameNameChanged(m_model->serviceName()->name());
    emit serviceNameExeTypeChanged(m_model->serviceName()->exeType());
    emit serviceNamePathChanged(m_model->serviceName()->path());
    emit serviceNameMainFunctionChanged(m_model->serviceName()->mainFunction());
    emit serviceNameDetailChanged(m_model->serviceName()->detail());

    QList<Field *> fieldList = m_model->allFields();
    unsigned int end = fieldList.count();
    for(int i = 0; i < end; ++i)
    {
        emit fieldAdded(i);

        emit fieldNameChanged(i, fieldList[i]->name());
        emit fieldTypeChanged(i, fieldList[i]->type());
        emit fieldSwitchCmdChanged(i, fieldList[i]->switchCmd());
        emit fieldRangeChanged(i, fieldList[i]->range());
        emit fieldDefaultValueChanged(i, fieldList[i]->defaultValue());
        emit fieldOptChanged(i, fieldList[i]->opt());
        emit fieldDetailChanged(i, fieldList[i]->detail());
    }
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
IniDocumentPresenter::changeServiceNameName(QString const &name)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->serviceName()->setName(name);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeServiceNameExeType(QString const &exeType)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->serviceName()->setExeType(exeType);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeServiceNamePath(QString const &path)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->serviceName()->setPath(path);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeServiceNameMainFunction(QString const &mainFunction)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->serviceName()->setMainFunction(mainFunction);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeServiceNameDetail(QString const &detail)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->serviceName()->setDetail(detail);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::insertField(unsigned int idx)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->insertField(idx);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }

    emit fieldAdded(idx);
}

void
IniDocumentPresenter::removeField(unsigned int idx)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->removeField(idx);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }

    emit fieldRemoved(idx);
}

void
IniDocumentPresenter::changeFieldName(unsigned int idx, QString const&  name)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->field(idx)->setName(name);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeFieldType(unsigned int idx, QString const&  type)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->field(idx)->setType(type);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeFieldSwitchCmd(unsigned int idx, QString const&  switchCmd)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->field(idx)->setSwitchCmd(switchCmd);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeFieldRange(unsigned int idx, const QString &range)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->field(idx)->setRange(range);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeFieldDefaultValue(unsigned int idx, QString const&  defaultValue)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->field(idx)->setDefaultValue(defaultValue);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void
IniDocumentPresenter::changeFieldOpt(unsigned int idx, QString const&  opt)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->field(idx)->setOpt(opt);
        this->blockSignals(false);
        emit modelContentChanged(IniDocumentIO::write(m_model));
    }
}

void IniDocumentPresenter::changeFieldDetail(unsigned int idx, QString const&  detail)
{
    if(!m_model.isNull())
    {
        this->blockSignals(true);
        m_model->field(idx)->setDetail(detail);
        this->blockSignals(false);
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
        serviceDescriptionWidget->setName(serviceName->name());
        serviceDescriptionWidget->setExeType(serviceName->exeType());
        serviceDescriptionWidget->setPath(serviceName->path());
        serviceDescriptionWidget->setMainFunction(serviceName->mainFunction());
        serviceDescriptionWidget->setDetail(serviceName->detail());
    }

    // connect presenter and view
    connect(this, SIGNAL(serviceNameNameChanged(QString)),
            serviceDescriptionWidget, SLOT(setName(QString)));
    connect(this, SIGNAL(serviceNameExeTypeChanged(QString)),
            serviceDescriptionWidget, SLOT(setExeType(QString)));
    connect(this, SIGNAL(serviceNamePathChanged(QString)),
            serviceDescriptionWidget, SLOT(setPath(QString)));
    connect(this, SIGNAL(serviceNameMainFunctionChanged(QString)),
            serviceDescriptionWidget, SLOT(setMainFunction(QString)));
    connect(this, SIGNAL(serviceNameDetailChanged(QString)),
            serviceDescriptionWidget, SLOT(setDetail(QString)));

    // connect view and presenter
    connect(serviceDescriptionWidget, SIGNAL(nameChanged(QString)),
            this, SLOT(changeServiceNameName(QString)));
    connect(serviceDescriptionWidget, SIGNAL(exeTypeChanged(QString)),
            this, SLOT(changeServiceNameExeType(QString)));
    connect(serviceDescriptionWidget, SIGNAL(pathChanged(QString)),
            this, SLOT(changeServiceNamePath(QString)));
    connect(serviceDescriptionWidget, SIGNAL(mainFunctionChanged(QString)),
            this, SLOT(changeServiceNameMainFunction(QString)));
    connect(serviceDescriptionWidget, SIGNAL(detailChanged(QString)),
            this, SLOT(changeServiceNameDetail(QString)));

    return serviceDescriptionWidget;
}

FieldListWidget*
IniDocumentPresenter::_buildFieldListWidget() const
{
    FieldListWidget *fieldListWidget = new FieldListWidget;
    if(!m_model.isNull())
    {
        foreach(Field *field, m_model->allFields())
        {
            FieldDescriptionWidget *fieldDescriptionWidget = fieldListWidget->addFieldDescriptionWidget();
            fieldDescriptionWidget->setName(field->name());
            fieldDescriptionWidget->setType(field->type());
            fieldDescriptionWidget->setSwicthCmd(field->switchCmd());
            fieldDescriptionWidget->setRange(field->range());
            fieldDescriptionWidget->setDefaultValue(field->defaultValue());
            fieldDescriptionWidget->setOpt(field->opt());
            fieldDescriptionWidget->setDetail(field->detail());
        }
    }

    // connect presenter and view
    connect(this, SIGNAL(modelChanged()),
            fieldListWidget, SLOT(clear()));
    connect(this, SIGNAL(fieldAdded(uint)),
            fieldListWidget, SLOT(insertFieldDescriptionWidget(uint)));
    connect(this, SIGNAL(fieldRemoved(uint)),
            fieldListWidget, SLOT(removeFieldDescriptionWidget(uint)));

    connect(this, SIGNAL(fieldNameChanged(uint,QString)),
            fieldListWidget, SLOT(setName(uint,QString)));
    connect(this, SIGNAL(fieldTypeChanged(uint,QString)),
            fieldListWidget, SLOT(setType(uint,QString)));
    connect(this, SIGNAL(fieldSwitchCmdChanged(uint,QString)),
            fieldListWidget, SLOT(setSwitchCmd(uint,QString)));
    connect(this, SIGNAL(fieldRangeChanged(uint,QString)),
            fieldListWidget, SLOT(setRange(uint,QString)));
    connect(this, SIGNAL(fieldDefaultValueChanged(uint,QString)),
            fieldListWidget, SLOT(setDefaultValue(uint,QString)));
    connect(this, SIGNAL(fieldOptChanged(uint,QString)),
            fieldListWidget, SLOT(setOpt(uint,QString)));
    connect(this, SIGNAL(fieldDetailChanged(uint,QString)),
            fieldListWidget, SLOT(setDetail(uint,QString)));


    // connect view and presenter
    connect(fieldListWidget, SIGNAL(addFieldRequest(uint)),
            this, SLOT(insertField(uint)));
    connect(fieldListWidget, SIGNAL(removeFieldRequest(uint)),
            this, SLOT(removeField(uint)));


    connect(fieldListWidget, SIGNAL(nameChanged(uint,QString)),
            this, SLOT(changeFieldName(uint,QString)));
    connect(fieldListWidget, SIGNAL(typeChanged(uint,QString)),
            this, SLOT(changeFieldType(uint,QString)));
    connect(fieldListWidget, SIGNAL(switchCmdChanged(uint,QString)),
            this, SLOT(changeFieldSwitchCmd(uint,QString)));
    connect(fieldListWidget, SIGNAL(rangeChanged(uint,QString)),
            this, SLOT(changeFieldRange(uint,QString)));
    connect(fieldListWidget, SIGNAL(defaultValueChanged(uint,QString)),
            this, SLOT(changeFieldDefaultValue(uint,QString)));
    connect(fieldListWidget, SIGNAL(optChanged(uint,QString)),
            this, SLOT(changeFieldOpt(uint,QString)));
    connect(fieldListWidget, SIGNAL(detailChanged(uint,QString)),
            this, SLOT(changeFieldDetail(uint,QString)));

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
