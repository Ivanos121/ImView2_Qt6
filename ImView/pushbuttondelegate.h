#ifndef PUSHBUTTONDELEGATE_H
#define PUSHBUTTONDELEGATE_H

#include "qdialog.h"
#include <QStyledItemDelegate>
#include <QWidget>
#include <QPushButton>
#include <QTableView>

class ButtonColumnDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    ButtonColumnDelegate(QObject *parent = 0);
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:    
    bool helpEvent( QHelpEvent* e, QAbstractItemView* view, const QStyleOptionViewItem& option,
                   const QModelIndex& index );

private slots:    
    void btn_clicked_4();
    void btn_clicked_5();
    void btn_clicked_6();
    void btn_clicked_7();
    void btn_clicked_8();


private:
    QPushButton *btn;
    bool isOneCellInEditMode;
    QPersistentModelIndex currentEditedCellIndex;

signals:
    void projectFileSelected(QString projctFile);
    void projectFileSelected_2(QString projectFile_2);
    void projectFileSelected_3(QString projectFile_3);
    void projectFileSelected_4(QString projectFile_4);
    void projectFileSelected_5(QString projectFile_5);
    void projectFileSelected_6(QString projectFile_6);
};

#endif // PUSHBUTTONDELEGATE_H
