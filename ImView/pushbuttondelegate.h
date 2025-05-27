#ifndef PUSHBUTTONDELEGATE_H
#define PUSHBUTTONDELEGATE_H

#include "qdialog.h"
#include <QStyledItemDelegate>
#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QTreeView>

class ButtonColumnDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    explicit ButtonColumnDelegate(QTreeView *view, QObject *parent = nullptr);
    ~ButtonColumnDelegate() override;

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

public slots:    
    bool helpEvent( QHelpEvent* e, QAbstractItemView* view,
                   const QStyleOptionViewItem& option, const QModelIndex& index) override;

protected slots:
    void btn_clicked_4();
    void btn_clicked_5();
    void btn_clicked_6();
    void btn_clicked_7();
    void btn_clicked_8();


private:
    QPushButton *btn;
    QTreeView *m_view;
    bool isOneCellInEditMode;
    QPersistentModelIndex currentEditedCellIndex;
    bool isPartOfSpan(const QModelIndex &index) const;
    bool shouldSpan(const QModelIndex &index) const;
    void m_paintFunc2(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    //void m_paintFunc1(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    //void m_paintFunc3(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void m_paintFunc4(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

signals:
    void projectFileSelected(QString projctFile);
    void projectFileSelected_2(QString projectFile_2);
    void projectFileSelected_3(QString projectFile_3);
    void projectFileSelected_4(QString projectFile_4);
    void projectFileSelected_5(QString projectFile_5);
    void projectFileSelected_6(QString projectFile_6);
};

#endif // PUSHBUTTONDELEGATE_H
