#pragma once
#include <QObject>
#include <QUrl>

class QUrl;

class UrlHandler : public QObject
{
    Q_OBJECT
public:
    explicit UrlHandler();
    static UrlHandler* getInstance();

signals:
    void labelSet(const QString& label);

public slots:
    void handleUrl(const QUrl& url);

private:
    static UrlHandler* m_instance;
};
