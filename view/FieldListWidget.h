#pragma once

#include <QScrollArea>
#include <QVBoxLayout>

class FieldDescriptionWidget;

class FieldListWidget: public QScrollArea
{
    Q_OBJECT

private:
    QList<FieldDescriptionWidget *> m_fieldWidgetList;
    QVBoxLayout *m_mainLayout;

public:
    FieldListWidget(QWidget *parent = NULL);
    virtual ~FieldListWidget();

    void addFieldDescriptionWidget(FieldDescriptionWidget* widget);
    void insertFieldDescriptionWidget(int index, FieldDescriptionWidget* widget);
    void removeFieldDescriptionWidget(FieldDescriptionWidget* widget);
};
