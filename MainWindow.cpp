#include "MainWindow.h"

#include "MainWidget.h"
#include "IniDocumentPresenter.h"

#include <QVBoxLayout>

#include <QDebug>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "Inria", "florent", this);

    m_iniDocumentPresenter = new IniDocumentPresenter(this);
    this->setCentralWidget(m_iniDocumentPresenter->mainWidget());

    this->restoreGeometry(m_settings->value("mainwindow/geometry").toByteArray());
}

MainWindow::~MainWindow()
{
    qDebug() << "Destroying MainWindow...";
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Close event...";
    m_settings->setValue("mainwindow/geometry", this->saveGeometry());
}

