#ifndef SYSTEMVIEWWIDGET_H
#define SYSTEMVIEWWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTreeView>
#include <QComboBox>
#include <QPushButton>
#include <QStandardItemModel>
#include <QApplication>
#include <QLineEdit>
#include <QString>

Q_PROPERTY(QStandardItemModel *model READ getCurrentModel WRITE setNewModel)

class SystemViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemViewWidget(QWidget *parent = nullptr);
    ~SystemViewWidget();
    void clearTree();
    QStandardItemModel *getCurrentModel () const{
        return model;
    }
    void setNewModel(QStandardItemModel *newmodel);
    void rebuildModel(QString str);

private:
    QGridLayout *gridLay;
    QTreeView *tree;
    QPushButton *mainPath;
    QPushButton *back_button;
    QComboBox *disckSelBox;
    QLineEdit *pathLine;
    QStandardItemModel *model;
    QString currentPath;

private slots:
    void chgDisk(int index);
    void goMainPath();
    void chgPath(QModelIndex index);
    void backSl();

protected:
};

#endif // SYSTEMVIEWWIDGET_H
