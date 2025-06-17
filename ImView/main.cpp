#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QIcon>
#include <QuaZip-Qt5-1.5/quazip/JlCompress.h>
#include <QTranslator>
#include <QSettings>
#include <QRect>
#include <QScreen>

#include "mainwindow.h"
#include "settings.h"
#include "version.h"

int main(int argc, char *argv[])
{
    //qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    qputenv("QT_QUICK_BACKEND", "software");

    QApplication a(argc, argv);

    qDebug() << "Version:" << APP_VERSION_STRING;


    QString vers = QString("%1.%2.%3").arg(APP_VERSION_MAJOR).arg(APP_VERSION_MINOR).arg(APP_BUILD_NUMBER);
    QSettings settings( "BRU", "IM View");
    settings.setValue("version", vers);

// #ifdef GIT_HASH
//     QString gitHash = QStringLiteral(GIT_HASH);
//     QString vers2 = QString("%1.%2.%3").arg(APP_VERSION_MAJOR).arg(APP_VERSION_MINOR).arg(gitHash);
//     qDebug() << "Git hash:" << gitHash;
//     settings.setValue("version2", vers2);
// #endif


    QCoreApplication::setOrganizationName("ImView");
    QCoreApplication::setApplicationName("ImView");

    if(QGuiApplication::platformName() == QLatin1String("xcb"))
    {
        QGuiApplication::setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_24_blue.png"));
    }
    else if(QGuiApplication::platformName() == QLatin1String("wayland"))
    {
        QGuiApplication::setDesktopFileName("org.imvew.IMView.desktop");
    }

    QFont font = QApplication::font();
    font.setPointSize(10); // Устанавливаем размер шрифта в логических пикселях
    QApplication::setFont(font);

    settings.beginGroup( "language interface" );
    QString lokal = settings.value( "QtLanguage_", "").toString();
    settings.endGroup();

    //QString language = QString("QtLanguage_") + lokal;
    QTranslator *qtLanguageTranslator = new QTranslator();

    if(lokal == "ru_RU")
    {
        if (qtLanguageTranslator->load("/home/elf/ImView2_Qt6/language/QtLanguage_ru_RU.qm"))
        {
            a.installTranslator(qtLanguageTranslator);
        }
        else
        {
            qDebug() << "Translation file not loaded!";
        }
    }
    else
        if(lokal == "en_US")
        {
            if (qtLanguageTranslator->load("/home/elf/ImView2_Qt6/language/QtLanguage_en_US.qm"))
            {
                a.installTranslator(qtLanguageTranslator);
            }
            else
            {
                qDebug() << "Translation file not loaded!";
            }
        }

    // delete qtLanguageTranslator;
    // qtLanguageTranslator = nullptr;



    MainWindow w;
    QDir dir("/tmp/imview");
    if (dir.exists())
    {
        dir.removeRecursively();
    }
    if (argc == 2)
    {
        QString filename(argv[1]);
        w.LoadProject(filename);
    }

    w.show();

    return a.exec();
}
