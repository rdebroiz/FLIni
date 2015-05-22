#pragma once

#include <QSettings>
#include <QRegExp>


struct ServiceName
{
    QString name;           // Le nom du service, ou traitement, par exemple AnimaNLMeans. MANDATORY
    QString exeType;        // Le service peut-être présenté sous trois formes possibles exe (pour un binaire executable),
                            // lib (pour une .dll ou un .so), batch (pour une .bat ou .sh). MANDATORY
    QString path;			// Le chemin du fichier contenant le service, par exemple /usr/bin/fli/services/Anima/NLMeans. MANDATORY
    QString mainFunction;   // nom de la fonction d'entrée quand on a à faire à une lib. Si absant la valeur est main. OPTIONAL
    QString detail;         // String donnant une explication détaillée sur le Service. OPTIONAL (Non cablé)
};

struct Field
{
    QString name;           //Non du champ, par exemple "Image d'entrée". MANDATORY;
    QString type;           //Le type du champ, les valeurs possibles sont: file, string, int, float, bool. Par exemple string. MANDATORY
    QString switchCmd;      //String donnant le commutateur allant de pair avec le feeld. OPTIONAL
    QString range;          //String donnant des indication de range de valeurs interprétable par le client. OPTIONAL
    QString defaultValue;   //defaultValue défini la valeur par défaut du paramètre par exemple. OPTIONAL
    QString opt;            //opt est un booléen qui indique si le champ optionel ou non, par default opt vaut Vrai. OPTIONAL
    QString detail;         //String donnant une explication détaillée sur le Field. OPTIONAL (Non cablé
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
    void insertField(int idx, Field *field);

    QString filename() const;
    void setFilename(QString const &filename);
};
