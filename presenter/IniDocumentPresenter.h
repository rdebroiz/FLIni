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
    void changeSNName(QString const &name);
    void changeSNExeType(QString const &exeType);
    void changeSNPath(QString const &path);
    void changeSNMainFunction(QString const &mainFunction);
    void changeSNDetail(QString const &detail);
    void openIniDocument(const QString &filename);

    void setModel(IniDocumentModel *model);
    IniDocumentModel* model();

private:
    MainWidget* _buildMainWidget() const;
    ServiceDescriptionWidget* _buildServiceDescriptionWidget() const;
    FieldListWidget* _buildFieldListWidget() const;
    FieldDescriptionWidget* _buildFieldDescriptionWidget() const;
    DocumentPreviewWidget* _buildDocumentPreviewWidget() const;
    CommandWidget* _buildCommandWidget() const;

private slots:


signals:
    void modelContentChanged(QString const&);
    void modelPathChanged(QString const&);
};
