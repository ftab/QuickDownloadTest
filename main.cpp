#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QNetworkReply>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject* parent = nullptr) : QObject(parent)
    {

    };
    Q_INVOKABLE void downloadFile(const QString &url)
    {
        QNetworkAccessManager manager;
        QNetworkRequest request((QUrl(url)));
        m_reply = manager.get(request);

        QObject::connect(m_reply, &QNetworkReply::finished, this, &Downloader::on_fileDownloaded);
        QObject::connect(m_reply, &QNetworkReply::errorOccurred, this, &Downloader::on_errorOccurred);
    };
    Q_INVOKABLE QByteArray data()
    {
        return m_data;
    };
    Q_INVOKABLE QString toString()
    {
        return QString(m_data);
    };
public slots:
    void on_fileDownloaded()
    {
        if (m_reply->error() == QNetworkReply::NoError)
        {
            m_data = m_reply->readAll();
            qDebug() << "Download success";
            emit success();
        }
        else
        {
            qDebug() << "Download error:" << m_reply->errorString();
            emit error();
        }
        m_reply->deleteLater();
        m_reply = nullptr;
    };
    void on_errorOccurred(QNetworkReply::NetworkError error)
    {
        qDebug() << "Download error occurred:" << error;
    };
signals:
    void error();
    void success();
private:
    QByteArray m_data;
    QNetworkReply *m_reply{nullptr};
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();
    auto downloader = new Downloader();
    context->setContextProperty("Downloader", downloader);
    engine.loadFromModule("QuickDownloadTest", "Main");

    return app.exec();
}
