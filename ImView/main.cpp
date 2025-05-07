#include "mainwindow.h"
#include "qscreen.h"
#include "settings.h"

#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QIcon>
#include <QuaZip-Qt5-1.5/quazip/JlCompress.h>
#include <QTranslator>
#include <QSettings>
#include <QRect>

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");


    QApplication a(argc, argv);

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


    QSettings settings( "BRU", "IM View");
    settings.beginGroup( "language interface" );
    QString lokal = settings.value( "QtLanguage_", "").toString();
    settings.endGroup();

    QString aaaaa = QString("QtLanguage_") + lokal;
    QTranslator *qtLanguageTranslator = new QTranslator();
    qtLanguageTranslator->load(aaaaa);
    qApp->installTranslator(qtLanguageTranslator);



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
