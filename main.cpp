#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include <iostream>
#include <cstdlib>

#include "ytvideo.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    if (app.arguments().count() != 2) {
        qCritical() << "Wrong args count. Exiting.";
        return EXIT_FAILURE;
    }

    YTVideo *video = new YTVideo(app.arguments().at(1));

    QObject::connect(video, &YTVideo::gotStreamUrl, [] (const QString &videoUrl, const QString &audioUrl) {
        std::cout << "VIDEO: " << videoUrl.toUtf8().constData() << std::endl;
        std::cout << "AUDIO: " << audioUrl.toUtf8().constData() << std::endl;
        QCoreApplication::quit();
    });

    QObject::connect(video, &YTVideo::errorStreamUrl, [] (const QString &message) {
        std::cout << "ERROR: " << message.toUtf8().constData() << std::endl;
        QCoreApplication::exit(EXIT_FAILURE);
    });

    video->loadStreamUrl();

    return app.exec();
}
