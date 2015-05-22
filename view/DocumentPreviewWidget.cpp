#include "DocumentPreviewWidget.h"

#include <QVBoxLayout>


DocumentPreviewWidget::DocumentPreviewWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    m_label = new QLabel(tr("No Open Document"));
    m_textEdit = new QTextEdit();
    m_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    m_textEdit->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum);
    m_textEdit->setReadOnly(true);

    mainLayout->addWidget(m_label);
    mainLayout->addWidget(m_textEdit);

}

DocumentPreviewWidget::~DocumentPreviewWidget()
{

}


QString
DocumentPreviewWidget::path() const
{
    return m_label->text();
}

QString
DocumentPreviewWidget::content() const
{
    return m_textEdit->toPlainText();
}

void
DocumentPreviewWidget::setPath(QString const& path)
{
    m_label->setText(path);
}

void
DocumentPreviewWidget::setContent(QString const& content)
{
    m_textEdit->setText(content);
}
