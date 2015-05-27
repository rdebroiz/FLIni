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
    void _saveAsFile();

signals:
    void openFileRequest(QString const& fileName);
    void saveAsFileRequest(QString const& filename);

};
