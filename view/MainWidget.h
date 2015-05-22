#pragma once

#include <QWidget>
#include <QVBoxLayout>

class ServiceDescriptionWidget;
class FieldListWidget;
class CommandWidget;
class DocumentPreviewWidget;

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *m_leftPannelLayout;
    QVBoxLayout *m_rightPannelLayout;

public:
    MainWidget(QWidget *parent = NULL);
    virtual ~MainWidget();

public slots:
    void setServiceDescriptionWidget(ServiceDescriptionWidget *widget);
    void setCommandWidget(CommandWidget *widget);
    void setDocumentPreviewDescriptionWidget(DocumentPreviewWidget *widget);
    void setFieldListWidget(FieldListWidget* widget);
};
