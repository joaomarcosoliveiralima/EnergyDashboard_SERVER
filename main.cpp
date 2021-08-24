#include <QCoreApplication>
#include <QFile>
#include <QString>

#include "tcp/tcpmultithreadedserver.h"
#include "http/httpwebengine.h"
#include "http/httpiodeviceresource.h"

using namespace QtWebServer;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Tcp::MultithreadedServer s;
    Http::WebEngine w;

    w.addResource(new Http::IODeviceResource(
                      "/hello",
                      new QFile("/home/joao_kde/hello.html")));

    s.setResponder(&w);
    s.listen(QHostAddress::LocalHost, 3000);
    return a.exec();
}
