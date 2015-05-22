#pragma once

#include  <QObject>
#include <QPointer>

class IniDocumentModel;

class MainWidget;
class ServiceDescriptionWidget;
class FieldDescriptionWidget;
class FieldListWidget;
class CommandWidget;
class DocumentPreviewWidget;

class IniDocumentPresenter: public QObject
{
    Q_OBJECT

private:
    QPointer<IniDocumentModel> m_model;

public:
    IniDocumentPresenter(QObject *parent = NULL);
    virtual ~IniDocumentPresenter();

    MainWidget* mainWidget() const;
    ServiceDescriptionWidget* serviceDescriptionWidget() const;
    CommandWidget* commandWidget()const;
    DocumentPreviewWidget* documentPreviewWidget() const;
    FieldListWidget* fieldListWidget() const;

public slots:
    void openIniDocument(const QString &filename);

    void changeServiceNameName(QString const &name);
    void changeServiceNameExeType(QString const &exeType);
    void changeServiceNamePath(QString const &path);
    void changeServiceNameMainFunction(QString const &mainFunction);
    void changeServiceNameDetail(QString const &detail);

    void insertField(unsigned int idx);
    void removeField(unsigned int idx);

    void changeFieldName(unsigned int idx, QString const&  name);
    void changeFieldType(unsigned int idx, QString const&  type);
    void changeFieldSwitchCmd(unsigned int idx, QString const&  switchCmd);
    void changeFieldRange(unsigned int idx, QString const&  range);
    void changeFieldDefaultValue(unsigned int idx, QString const&  defaultValue);
    void changeFieldOpt(unsigned int idx, QString const&  opt);
    void changeFieldDetail(unsigned int idx, QString const&  detail);

    void setModel(IniDocumentModel *model);
    IniDocumentModel* model();

private:
    MainWidget* _buildMainWidget() const;
    ServiceDescriptionWidget* _buildServiceDescriptionWidget() const;
    FieldListWidget* _buildFieldListWidget() const;
    DocumentPreviewWidget* _buildDocumentPreviewWidget() const;
    CommandWidget* _buildCommandWidget() const;

private slots:


signals:
    void modelChanged();
    void modelContentChanged(QString const&);
    void modelPathChanged(QString const&);

signals:
    void serviceNameNameChanged(QString const&);
    void serviceNameExeTypeChanged(QString const&);
    void serviceNamePathChanged(QString const&);
    void serviceNameMainFunctionChanged(QString const&);
    void serviceNameDetailChanged(QString const&);

signals:
    void fieldAdded(unsigned int);
    void fieldRemoved(unsigned int);

    void fieldNameChanged(unsigned int, QString const&);
    void fieldTypeChanged(unsigned int, QString const&);
    void fieldSwitchCmdChanged(unsigned int, QString const&);
    void fieldRangeChanged(unsigned int, QString const&);
    void fieldDefaultValueChanged(unsigned int, QString const&);
    void fieldOptChanged(unsigned int, QString const&);
    void fieldDetailChanged(unsigned int, QString const&);
};
