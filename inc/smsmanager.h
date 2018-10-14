#ifndef SMSMANAGER_H
#define SMSMANAGER_H

#include <QObject>
#include <QString>

class SmsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString body READ getBody)
public:
    explicit SmsManager(QObject *parent = nullptr);
    static QString getServiceUuid() { return "0349f3e8-ce6e-11e8-a8d5-f2801f1b9fd1"; }
    static QString getMessageUuid() { return "0349f744-ce6e-11e8-a8d5-f2801f1b9fd1"; }

private:
    QString getName() const { return mName; }
    QString getBody() const { return mBody; }

    QString mName;
    QString mBody;

signals:
    void launchMessagePopup();

public slots:
    void updateMessage(const QString& name, const QString& body)
    {
        mName = name;
        mBody = body;
        emit launchMessagePopup();
    }
};

#endif // SMSMANAGER_H
