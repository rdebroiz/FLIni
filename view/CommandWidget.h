#pragma once

#include <QWidget>

class CommandWidget : public QWidget
{
    Q_OBJECT

public:
    CommandWidget(QWidget *parent = NULL);
    virtual ~CommandWidget();

private slots:
    void _openFile();

signals:
    void openFileRequest(QString fileName);

};
