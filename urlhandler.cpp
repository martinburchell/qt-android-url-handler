
#include <QDebug>
#include <QDesktopServices>
#include <QSysInfo>
#include <QUrl>
#include <QUrlQuery>

#ifdef Q_OS_ANDROID
#include <jni.h>
#endif

#include "urlhandler.h"

UrlHandler* UrlHandler::m_instance = NULL;


UrlHandler::UrlHandler()
{
    m_instance = this;

    QDesktopServices::setUrlHandler("https", this, "handleUrl");
}


void UrlHandler::handleUrl(const QUrl& url)
{
    qDebug() << Q_FUNC_INFO << url;

    auto query = QUrlQuery(url);
    auto label = query.queryItemValue("label");
    if (!label.isEmpty()) {
        emit labelSet(label);
    }
}


UrlHandler* UrlHandler::getInstance()
{
    if (!m_instance)
        m_instance = new UrlHandler;
    return m_instance;
}

#ifdef Q_OS_ANDROID
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
  Java_io_github_martinburchell_urlhandler_CustomActivity_handleAndroidUrl(
      JNIEnv *env,
      jobject obj,
      jstring url)
{
    Q_UNUSED(obj)

    const char *url_str = env->GetStringUTFChars(url, NULL);

    UrlHandler::getInstance()->handleUrl(QUrl(url_str));

    env->ReleaseStringUTFChars(url, url_str);
}

#ifdef __cplusplus
}
#endif

#endif
