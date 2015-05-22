#include "CommandWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSettings>
#include <QDir>
#include <QFileDialog>

CommandWidget::CommandWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    QPushButton *openFileButton = new QPushButton(tr("Open Ini Document"));
    connect (openFileButton, SIGNAL(clicked()), this, SLOT(_openFile()));

    mainLayout->addWidget(openFileButton);
}

CommandWidget::~CommandWidget()
{

}

void
CommandWidget::_openFile()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Inria", "florent", this);

    QString openFileDir = settings.value("CommandWidget/OpenFileDir", QDir::homePath()).toString();
    QString filename = QFileDialog::getOpenFileName(0,
                                                    tr("Open Ini Document"),
                                                    openFileDir,
                                                    tr("Ini (*.ini)"));

    // If user doesn't cancel.
    if(!filename.isEmpty())
    {
        settings.setValue("CommandWidget/OpenFileDir", filename);
        emit openFileRequest(filename);
    }
}
