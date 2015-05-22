#pragma once

#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>

class IniDocumentPresenter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSettings* m_settings;
    IniDocumentPresenter* m_iniDocumentPresenter;

public:
    MainWindow(QWidget *parent = NULL);
    virtual ~MainWindow();

protected:
    virtual void closeEvent(QCloseEvent *event);

};
