#pragma once

#include <QSettings>
#include <QRegExp>


class ServiceName: public QObject
{
    Q_OBJECT
private:
    QString m_name;           // Le nom du service, ou traitement, par exemple AnimaNLMeans. MANDATORY
    QString m_exeType;        // Le service peut-être présenté sous trois formes possibles exe (pour un binaire executable),
                            // lib (pour une .dll ou un .so), batch (pour une .bat ou .sh). MANDATORY
    QString m_path;			// Le chemin du fichier contenant le service, par exemple /usr/bin/fli/services/Anima/NLMeans. MANDATORY
    QString m_mainFunction;   // nom de la fonction d'entrée quand on a à faire à une lib. Si absant la valeur est main. OPTIONAL
    QString m_detail;         // String donnant une explication détaillée sur le Service. OPTIONAL (Non cablé)

public:
    QString name() const;
    QString exeType() const;
    QString path() const;
    QString mainFunction() const;
    QString detail() const;

public slots:
    void setName(QString const& name);
    void setExeType(QString const& exeType);
    void setPath(QString const& path);
    void setMainFunction(QString const& mainFunction);
    void setDetail(QString const& detail);


signals:
    void nameChanged(QString const&);
    void exeTypeChanged(QString const&);
    void pathChanged(QString const&);
    void mainFunctionChanged(QString const&);
    void detailChanged(QString const&);

};

class Field: public QObject
{
    Q_OBJECT
private:
    QString m_name;           //Non du champ, par exemple "Image d'entrée". MANDATORY;
    QString m_type;           //Le type du champ, les valeurs possibles sont: file, string, int, float, bool. Par exemple string. MANDATORY
    QString m_switchCmd;      //String donnant le commutateur allant de pair avec le feeld. OPTIONAL
    QString m_range;          //String donnant des indication de range de valeurs interprétable par le client. OPTIONAL
    QString m_defaultValue;   //defaultValue défini la valeur par défaut du paramètre par exemple. OPTIONAL
    QString m_opt;            //opt est un booléen qui indique si le champ optionel ou non, par default opt vaut Vrai. OPTIONAL
    QString m_detail;         //String donnant une explication détaillée sur le Field. OPTIONAL (Non cablé

public:
    QString name() const;
    QString type() const;
    QString switchCmd() const;
    QString range() const;
    QString defaultValue() const;
    QString opt() const;
    QString detail() const;

public:
    void setName(QString const& name);
    void setType(QString const& type);
    void setSwitchCmd(QString const& switchCmd);
    void setRange(QString const& range);
    void setDefaultValue(QString const& defaultValue);
    void setOpt(QString const& opt);
    void setDetail(QString const& detail);

signals:
    void nameChanged(QString const&);
    void typeChanged(QString const&);
    void switchCmdChanged(QString const&);
    void rangeChanged(QString const&);
    void defaultValueChanged(QString const&);
    void optChanged(QString const&);
    void detailChanged(QString const&);

};

class IniDocumentModel : public QObject
{
    Q_OBJECT

private:
    ServiceName *m_serviceName;
    QList<Field *> m_fieldList;

    QString m_filename;

public:
    IniDocumentModel(QObject *parent = NULL);
    virtual ~IniDocumentModel();

    ServiceName* serviceName() const;
    void setServiceName(ServiceName *serviceName);

    Field* field(unsigned int index) const;
    QList<Field *> allFields() const;
    Field * insertField(unsigned int index);
    void removeField(unsigned int index);

    QString filename() const;
    void setFilename(QString const &filename);

signals:
    void serviceNameNameChanged(QString const&);
    void serviceNameExeTypeChanged(QString const&);
    void serviceNamePathChanged(QString const&);
    void serviceNameMainFunctionChanged(QString const&);
    void serviceNameDetailChanged(QString const&);

signals:
    void fieldNameChanged(unsigned int, QString const&);
    void fieldTypeChanged(unsigned int, QString const&);
    void fieldSwitchCmdChanged(unsigned int, QString const&);
    void fieldRangeChanged(unsigned int, QString const&);
    void fieldDefaultValueChanged(unsigned int, QString const&);
    void fieldOptChanged(unsigned int, QString const&);
    void fieldDetailChanged(unsigned int, QString const&);

private slots:
    void _emitFieldNameChanged(QString const& name);
    void _emitFieldTypeChanged(QString const& type);
    void _emitFieldSwitchCmdChanged(QString const& switchCmd);
    void _emitFieldRangeChanged(QString const&  range);
    void _emitFieldDefaultValueChanged(QString const& defaultValue);
    void _emitFieldOptChanged(QString const& opt);
    void _emitFieldDetailChanged(QString const& detail);

};
