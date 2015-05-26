#pragma once

#include <QObject>
#include <QString>
#include <QPair>
#include <QList>

class IniGroup: public QObject
{
    Q_OBJECT

private:
    QList<QPair<QString, QString> > m_entries;

public:


    QString entry(QString const& key) const;
    void setEntry(QString const& key, QString const& value);

signals:
    entryChanged(QString const& key, QString const& value);
};

class IniDocumentModel : public QObject
{
    Q_OBJECT

private:
    IniGroup *m_serviceName;
    QList<IniGroup*> m_fields;

    QString m_filename;

public:
    IniDocumentModel(QObject *parent = NULL);
    virtual ~IniDocumentModel();

    IniGroup* serviceName() const;
    void setServiceName(IniGroup *serviceName);

    IniGroup* field(unsigned int idx) const;
    QList<IniGroup *> allFields() const;
    IniGroup * insertField(unsigned int idx);
    void removeField(unsigned int idx);

    QString filename() const;
    void setFilename(QString const &filename);

signals:
    void filenameChanged(QString const& filename);
    void serviceNameChanged(QString const& key, QString const& value);
    void fieldChanged(unsigned int idx, QString const& key, QString const& value);

    void fieldAdded(unsigned int idx);
    void fieldRemoved(unsigned int idx);

private slots:
    void _emitFieldChanged(QString const& key, QString const& value);
};
