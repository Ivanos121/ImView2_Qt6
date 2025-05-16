#include "itogs.h"
#include "ui_itogs.h"
#include <QPainter>
#include <QPrintDialog>
#include <QTimer>
#include <QDateTime>
#include <QTextTable>
#include <QPrintPreviewDialog>

#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "datas.h"
#include "base.h"


int nn;

Itogs::Itogs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Itogs)
{
    ui->setupUi(this);
    QFont font;
    font.setFamily(QStringLiteral("Calibri"));
    font.setPointSize(20);
    font.setBold(false);
    font.setUnderline(false);
    font.setItalic(false);
    connect(ui->pushButton, &QPushButton::clicked, this, &Itogs::report);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Itogs::print_report);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Itogs::clear_report);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Itogs::preview_report);
}

Itogs::~Itogs()
{
    delete ui;
}

void Itogs::report()
{
    int nn=40;
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    ui->textEdit->clear();
    ui->textEdit->setReadOnly(true);

    ui->textEdit->append("ПРОТОКОЛ");
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.setBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
    for (QTextBlock::iterator it = cursor.block().begin(); !(it.atEnd()); ++it)
    {
        QTextCharFormat charFormat = it.fragment().charFormat();
        charFormat.setFont(QFont("Calibri", 15, QFont::Bold));

        QTextCursor tempCursor = cursor;
        tempCursor.setPosition(it.fragment().position());
        tempCursor.setPosition(it.fragment().position() + it.fragment().length(), QTextCursor::KeepAnchor);
        tempCursor.setCharFormat(charFormat);
    }

    ui->textEdit->append("проведения испытаний асинхронных двигателей");
    cursor = ui->textEdit->textCursor();
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    textBlockFormat.setBottomMargin(20);
    cursor.setBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
    for (QTextBlock::iterator it = cursor.block().begin(); !(it.atEnd()); ++it)
    {
        QTextCharFormat charFormat = it.fragment().charFormat();
        charFormat.setFont(QFont("Calibri", 15, QFont::Bold));

        QTextCursor tempCursor = cursor;
        tempCursor.setPosition(it.fragment().position());
        tempCursor.setPosition(it.fragment().position() + it.fragment().length(), QTextCursor::KeepAnchor);
        tempCursor.setCharFormat(charFormat);
    }


    ui->textEdit->append("Дата проведения испытаний: "+cd.toString("dd.MM.yyyy")+ct.toString("   HH:mm:ss"));
    cursor = ui->textEdit->textCursor();
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignJustify);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);

    ui->textEdit->append("Характеристики испытуемого асинхронного двигателя");
    cursor = ui->textEdit->textCursor();
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setBottomMargin(20);
    textBlockFormat.setAlignment(Qt::AlignJustify);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);


    QTextCursor cur = ui->textEdit->textCursor();
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignLeft);
    tableFormat.setBorderStyle( QTextTableFormat::BorderStyle_Solid );
    tableFormat.setCellPadding( 4 );
    tableFormat.setCellSpacing( 0 );
    tableFormat.setWidth( QTextLength( QTextLength::PercentageLength, nn ) );
    tableFormat.setBottomMargin(20);
    QTextTable* table = cur.insertTable(8, 2, tableFormat);

    for (int i=0;i<8 ;i++ )
    {
        QTextTableCell   cell = table->cellAt(i, 1);
        QTextCharFormat  cellFormat = cell.format();

        cellFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
        cell.setFormat(cellFormat);

        QTextBlockFormat centerAlignment;
        centerAlignment.setAlignment(Qt::AlignHCenter);

        cur = table->cellAt(i, 1).firstCursorPosition();
        cur.setBlockFormat(centerAlignment);
     }

    table->cellAt(0, 0).firstCursorPosition().insertText("Марка двигателя: ");
    table->cellAt(1, 0).firstCursorPosition().insertText("Номинальная частота вращения , рад/с: ");
    table->cellAt(2, 0).firstCursorPosition().insertText("Номинальное напряжение фазы, В: ");
    table->cellAt(3, 0).firstCursorPosition().insertText("Номинальное напряжение фазы, В: ");
    table->cellAt(4, 0).firstCursorPosition().insertText("Номинальный коэффициент мощности: ");
    table->cellAt(5, 0).firstCursorPosition().insertText("Номинальный КПД: ");
    table->cellAt(6, 0).firstCursorPosition().insertText("Кратность максимального момента: ");
    table->cellAt(7, 0).firstCursorPosition().insertText("Синхронная частота вращения, об/мин: ");
    table->cellAt(0, 1).firstCursorPosition().insertText(base.name);
    table->cellAt(1, 1).firstCursorPosition().insertText(QString::number((double)base.P_nom));
    table->cellAt(2, 1).firstCursorPosition().insertText(QString::number((double)base.n_nom));
    table->cellAt(3, 1).firstCursorPosition().insertText(QString::number((double)base.U_fnom));
    table->cellAt(4, 1).firstCursorPosition().insertText(QString::number((double)base.cosf_nom));
    table->cellAt(5, 1).firstCursorPosition().insertText(QString::number((double)base.kpd_nom));
    table->cellAt(6, 1).firstCursorPosition().insertText(QString::number((double)base.muk));
    table->cellAt(7, 1).firstCursorPosition().insertText(QString::number((double)base.n_0));



    cursor = ui->textEdit->textCursor();
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setBottomMargin(20);
    textBlockFormat.setAlignment(Qt::AlignJustify);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);

    ui->textEdit->append("Идентификация параметров Т-образной схемы замещения асинхронного двигателя");
    cursor = ui->textEdit->textCursor();
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignJustify);
    textBlockFormat.setBottomMargin(20);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);

    QTextCursor curs = ui->textEdit->textCursor();
    QTextTableFormat tableFormat2;
    tableFormat2.setAlignment(Qt::AlignLeft);
    tableFormat2.setBorderStyle( QTextTableFormat::BorderStyle_Solid );
    tableFormat2.setCellPadding( 4 );
    tableFormat2.setCellSpacing( 0 );
    tableFormat2.setWidth( QTextLength( QTextLength::PercentageLength, nn));
    tableFormat2.setBottomMargin(20);
    QTextTable* table2 = curs.insertTable(5, 2, tableFormat2);
    for (int i=0;i<5 ;i++ )
    {
        QTextTableCell   cell = table2->cellAt(i, 1);
        QTextCharFormat  cellFormat2 = cell.format();

        cellFormat2.setVerticalAlignment(QTextCharFormat::AlignMiddle);
        cell.setFormat(cellFormat2);

        QTextBlockFormat centerAlignment2;
        centerAlignment2.setAlignment(Qt::AlignHCenter);

        curs = table2->cellAt(i, 1).firstCursorPosition();
        curs.setBlockFormat(centerAlignment2);
}

    table2->cellAt(0, 0).firstCursorPosition().insertText("Активное сопротивление фазы статора, Ом: ");
    table2->cellAt(1, 0).firstCursorPosition().insertText("Активное сопротивление фазы ротора, Ом: ");
    table2->cellAt(2, 0).firstCursorPosition().insertText("Индуктивность фазы статора, Гн: ");
    table2->cellAt(3, 0).firstCursorPosition().insertText("Индуктивность фазы ротора, Гн: ");
    table2->cellAt(4, 0).firstCursorPosition().insertText("Индуктивность взаимоиндукции, Гн: ");
    table2->cellAt(0, 1).firstCursorPosition().insertText(QString::number((double)base.R1, 'f', 3));
    table2->cellAt(1, 1).firstCursorPosition().insertText(QString::number((double)base.R2, 'f', 3));
    table2->cellAt(2, 1).firstCursorPosition().insertText(QString::number((double)base.L1, 'f', 3));
    table2->cellAt(3, 1).firstCursorPosition().insertText(QString::number((double)base.L2, 'f', 3));
    table2->cellAt(4, 1).firstCursorPosition().insertText(QString::number((double)base.Lm, 'f', 3));

    ui->textEdit->append("Энергетические показатели");
    cursor = ui->textEdit->textCursor();
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setBottomMargin(20);
    textBlockFormat.setAlignment(Qt::AlignJustify);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);

    QTextCursor curss = ui->textEdit->textCursor();
    QTextTableFormat tableFormat3;
    tableFormat3.setAlignment(Qt::AlignLeft);
    tableFormat3.setBorderStyle( QTextTableFormat::BorderStyle_Solid );
    tableFormat3.setCellPadding( 4 );
    tableFormat3.setCellSpacing( 0 );
    tableFormat3.setWidth( QTextLength( QTextLength::PercentageLength, nn));
    tableFormat3.setBottomMargin(20);
    QTextTable* table3 = curss.insertTable(22, 2, tableFormat3);
    for (int i=0;i<22 ;i++ )
    {
        QTextTableCell   cell = table3->cellAt(i, 1);
        QTextCharFormat  cellFormat3 = cell.format();

        cellFormat3.setVerticalAlignment(QTextCharFormat::AlignMiddle);
        cell.setFormat(cellFormat3);

        QTextBlockFormat centerAlignment3;
        centerAlignment3.setAlignment(Qt::AlignHCenter);

        curss = table3->cellAt(i, 1).firstCursorPosition();
        curss.setBlockFormat(centerAlignment3);
}

    table3->cellAt(0, 0).firstCursorPosition().insertText("Ток фазы А, А");
    table3->cellAt(1, 0).firstCursorPosition().insertText("Напряжение фазы А, В");
    table3->cellAt(2, 0).firstCursorPosition().insertText("Активная мощность фазы А, Вт");
    table3->cellAt(3, 0).firstCursorPosition().insertText("Реактивная мощность фазы А, ВА");
    table3->cellAt(4, 0).firstCursorPosition().insertText("Полная мощность фазы А, ВАР");
    table3->cellAt(5, 0).firstCursorPosition().insertText("Коэффициент мощности фазы А");
    table3->cellAt(6, 0).firstCursorPosition().insertText("Ток фазы В, А");
    table3->cellAt(7, 0).firstCursorPosition().insertText("Напряжение фазы В, В");
    table3->cellAt(8, 0).firstCursorPosition().insertText("Активная мощность фазы В, Вт");
    table3->cellAt(9, 0).firstCursorPosition().insertText("Реактивная мощность фазы В, ВА");
    table3->cellAt(10, 0).firstCursorPosition().insertText("Полная мощность фазы В, ВАР");
    table3->cellAt(11, 0).firstCursorPosition().insertText("Коэффициент мощности фазы В");
    table3->cellAt(12, 0).firstCursorPosition().insertText("Ток фазы С, А");
    table3->cellAt(13, 0).firstCursorPosition().insertText("Напряжение фазы С, В");
    table3->cellAt(14, 0).firstCursorPosition().insertText("Активная мощность фазы С, Вт");
    table3->cellAt(15, 0).firstCursorPosition().insertText("Реактивная мощность фазы С, ВА");
    table3->cellAt(16, 0).firstCursorPosition().insertText("Полная мощность фазы С, ВАР");
    table3->cellAt(17, 0).firstCursorPosition().insertText("Коэффициент мощности фазы С");
    table3->cellAt(18, 0).firstCursorPosition().insertText("Трехфазная активная мощность, Вт");
    table3->cellAt(19, 0).firstCursorPosition().insertText("Трехфазная реактивная мощность, ВА");
    table3->cellAt(20, 0).firstCursorPosition().insertText("Трехфазная полная мощность, ВАР");
    table3->cellAt(21, 0).firstCursorPosition().insertText("Коэффициент мощности фазы С");

    table3->cellAt(0, 1).firstCursorPosition().insertText(QString::number((double)base.i_a, 'f', 3));
    table3->cellAt(1, 1).firstCursorPosition().insertText(QString::number((double)base.u_a, 'f', 3));
    table3->cellAt(2, 1).firstCursorPosition().insertText(QString::number((double)base.p_akt_a, 'f', 3));
    table3->cellAt(3, 1).firstCursorPosition().insertText(QString::number((double)base.p_react_a, 'f', 3));
    table3->cellAt(4, 1).firstCursorPosition().insertText(QString::number((double)base.p_poln_a, 'f', 3));
    table3->cellAt(5, 1).firstCursorPosition().insertText(QString::number((double)base.cosf_a, 'f', 3));
    table3->cellAt(6, 1).firstCursorPosition().insertText(QString::number((double)base.i_b, 'f', 3));
    table3->cellAt(7, 1).firstCursorPosition().insertText(QString::number((double)base.u_b, 'f', 3));
    table3->cellAt(8, 1).firstCursorPosition().insertText(QString::number((double)base.p_akt_b, 'f', 3));
    table3->cellAt(9, 1).firstCursorPosition().insertText(QString::number((double)base.p_react_b, 'f', 3));
    table3->cellAt(10, 1).firstCursorPosition().insertText(QString::number((double)base.p_poln_b, 'f', 3));
    table3->cellAt(11, 1).firstCursorPosition().insertText(QString::number((double)base.cosf_b, 'f', 3));
    table3->cellAt(12, 1).firstCursorPosition().insertText(QString::number((double)base.i_c, 'f', 3));
    table3->cellAt(13, 1).firstCursorPosition().insertText(QString::number((double)base.u_c, 'f', 3));
    table3->cellAt(14, 1).firstCursorPosition().insertText(QString::number((double)base.p_akt_c, 'f', 3));
    table3->cellAt(15, 1).firstCursorPosition().insertText(QString::number((double)base.p_react_c, 'f', 3));
    table3->cellAt(16, 1).firstCursorPosition().insertText(QString::number((double)base.p_poln_c, 'f', 3));
    table3->cellAt(17, 1).firstCursorPosition().insertText(QString::number((double)base.cosf_c, 'f', 3));
    table3->cellAt(18, 1).firstCursorPosition().insertText(QString::number((double)base.p_akt, 'f', 3));
    table3->cellAt(19, 1).firstCursorPosition().insertText(QString::number((double)base.p_react, 'f', 3));
    table3->cellAt(20, 1).firstCursorPosition().insertText(QString::number((double)base.p_poln, 'f', 3));
    table3->cellAt(21, 1).firstCursorPosition().insertText(QString::number((double)base.cosf, 'f', 3));
}

void Itogs::print_report()
{
    nn=100;
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Document"));
      if (ui->textEdit->textCursor().hasSelection())
          dialog->setOption(QAbstractPrintDialog::PrintSelection);
      if (dialog->exec() != QDialog::Accepted)
          return;
           QTextDocument *doc = ui->textEdit->document();
      doc->print(&printer);
}

void Itogs::clear_report()
{
    ui->textEdit->clear();
}

void Itogs::preview_report()
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPageSize(QPageSize::A4));
    printer->setPageOrientation(QPageLayout::Portrait);
    printer->setFullPage(true);

    QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(printer);
    connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
    printPreview->setWindowTitle("Preview Dialog");
    Qt::WindowFlags flags(Qt::WindowTitleHint);
    printPreview->setWindowFlags(flags);
    printPreview->showMaximized();
    printPreview->exec();
}

void Itogs::print(QPrinter *printer)
{
    ui->textEdit->print(printer);
}

MainWindow* Itogs::getMainWindow()
{
    foreach (QWidget *w, qApp->topLevelWidgets())
        if (MainWindow* mainWin = qobject_cast<MainWindow*>(w))
            return mainWin;
    return nullptr;
}
