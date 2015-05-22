#pragma once

#include <QWidget>

#include <QLabel>
#include <QTextEdit>


class DocumentPreviewWidget : public QWidget
{
    Q_OBJECT

private:
    QLabel *m_label;
    QTextEdit *m_textEdit;

public:
    DocumentPreviewWidget(QWidget *parent = NULL);
    virtual ~DocumentPreviewWidget();

    QString path() const;
    QString content() const;

public slots:
    void setPath(QString const& path);
    void setContent(QString const& content);

};
