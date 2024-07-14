#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QItemDelegate>

QDoubleValidator *create_validator();

class ItemDelegate : public QItemDelegate
{
    Q_OBJECT
  public:
    ItemDelegate();

  protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

  signals:
    void item_changed(const QModelIndex &index, QString previous_value) const;
};

#endif // ITEMDELEGATE_H
