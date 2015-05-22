#pragma once

#include <QGroupBox>

#include <QVBoxLayout>

#include "IniDocumentModel.h"

class FieldDescriptionWidget : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout *m_mainLayout;

public:
    FieldDescriptionWidget(QWidget *parent = NULL);
    virtual ~FieldDescriptionWidget();

signals:
    void newFieldRequest();
    void removeFieldRequest();

};
