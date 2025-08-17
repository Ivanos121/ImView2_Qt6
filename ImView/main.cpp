#include <QApplication>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QIcon>
#include <QuaZip-Qt5-1.5/quazip/JlCompress.h>
#include <QTranslator>
#include <QSettings>
#include <QRect>
#include <QScreen>
#include <QSqlError>
#include <QSqlDatabase>
#include <QLoggingCategory>

#include "mainwindow.h"
#include "settings.h"

void close_sql_base()
{
   // qDebug() << "Closing database connections";
    {
        QSqlDatabase sda = QSqlDatabase::database("connection1");
        if (sda.isOpen()) {
            sda.close();
        }
    }
    QSqlDatabase::removeDatabase("connection1");

    {
        QSqlDatabase sdb = QSqlDatabase::database("connection2");
        if (sdb.isOpen()) {
            sdb.close();
        }
    }
    QSqlDatabase::removeDatabase("connection2");

    {
        QSqlDatabase sdc = QSqlDatabase::database("connection3");
        if (sdc.isOpen()) {
            sdc.close();
        }
    }
    QSqlDatabase::removeDatabase("connection3");

    {
        QSqlDatabase sdd = QSqlDatabase::database("connection4");
        if (sdd.isOpen()) {
            sdd.close();
        }
    }
    QSqlDatabase::removeDatabase("connection4");

}

int main(int argc, char *argv[])
{
    int res;
    QApplication a(argc, argv);
    {
        //QLoggingCategory::setFilterRules(QStringLiteral("*.debug=true"));
        /*QSqlDatabase::removeDatabase("connection1");
        QSqlDatabase::removeDatabase("connection2");
        QSqlDatabase::removeDatabase("connection3");
        QSqlDatabase::removeDatabase("connection4");*/

        QSqlDatabase sda = QSqlDatabase::addDatabase("QSQLITE", "connection1");
        sda.setDatabaseName(QFileInfo("../data/base_db/mydb.db").absoluteFilePath());
        sda.open();
        // if (!sda.open()) {
        //     qDebug() << "Ошибка открытия базы данных 1:" << sda.lastError().text();
        //     return -1;
        // }
        // else
        // {
        //     qDebug() << "база загружена";
        // }

        QSqlDatabase::removeDatabase("connection2");
        QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE", "connection2");
        sdb.setDatabaseName(QFileInfo("../data/base_db/ventdb.db").absoluteFilePath());
        sdb.open();
        // if (!sdb.open()) {
        //     qDebug() << "Ошибка открытия базы данных 2:" << sdb.lastError().text();
        //     return -1;
        // }
        // else
        // {
        //     qDebug() << "база загружена2";
        // }

        QSqlDatabase sdc = QSqlDatabase::addDatabase("QSQLITE", "connection3"); //объявление базы данных sqlite3
        sdc.setDatabaseName(QFileInfo("../data/base_db/netdb.db").absoluteFilePath());
        sdc.open();
        // if (!sdc.open()) {
        //     qDebug() << "Ошибка открытия базы данных 3:" << sdc.lastError().text();
        //     return -1;
        // }
        // else
        // {
        //     qDebug() << "база загружена3";
        // }

        QSqlDatabase sdd = QSqlDatabase::addDatabase("QSQLITE","connection4");
        sdd.setDatabaseName(QFileInfo("../data/base_db/netdb2.db").absoluteFilePath());
        sdd.open();
        // if (!sdc.open()) {
        //     qDebug() << "Ошибка открытия базы данных 4:" << sdd.lastError().text();
        //     return -1;
        // }
        // else
        // {
        //     qDebug() << "база загружена4";
        // }

        qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
        qputenv("QT_QUICK_BACKEND", "software");

        QSettings settings( "BRU", "IM View");

        QCoreApplication::setOrganizationName("ImView");
        QCoreApplication::setApplicationName("ImView");
        a.setWindowIcon(QIcon(":/icons/data/img/icons/IM_16x16.png"));

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

        MainWindow w;

        // Получаем размеры экрана
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();

        // Устанавливаем состояние окна в "обычное" (не максимизированное)
        w.setWindowState(Qt::WindowNoState);

        // Устанавливаем размер окна равным размеру экрана
        w.resize(screenGeometry.size());
        w.setWindowFlag(Qt::FramelessWindowHint, false);

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

        res = a.exec();
    }

    close_sql_base();

    return res;
}
