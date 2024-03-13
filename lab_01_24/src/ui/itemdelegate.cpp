#include "itemdelegate.h"
#include "./mainwindow.h"

QDoubleValidator* create_validator()
{
    QDoubleValidator *validator = new QDoubleValidator;

    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);
    validator->setLocale(locale);

    return validator;
}


ItemDelegate::ItemDelegate()
{

}


QWidget* ItemDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    auto *editor = new QLineEdit(parent);
    QDoubleValidator *validator = new QDoubleValidator;

    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);
    validator->setLocale(locale);

    editor->setValidator(create_validator());
    return editor;
}

void ItemDelegate::setModelData(QWidget *editor,
                                QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QString pre_data = model->data(index).toString();
    QItemDelegate::setModelData(editor, model, index);
    if (model->data(index).toString() != pre_data)
        emit item_changed(index, pre_data);
}
