#include "systemviewwidget.h"
#include <QDir>

SystemViewWidget::SystemViewWidget(QWidget *parent) : QWidget(parent), model(nullptr)
{
    gridLay = new QGridLayout(this);
    this->setLayout(gridLay);
    tree = new QTreeView(this);
    pathLine = new QLineEdit();
    pathLine->setReadOnly(true);
    model = new QStandardItemModel(this);
    back_button = new QPushButton(this);
    back_button->setText("« Back");
    gridLay->addWidget(tree,1,0,10,10);
    gridLay->addWidget(back_button,0,2,1,2);
    gridLay->addWidget(pathLine,0,4,1,2);
    setMinimumSize(500,600);

    if(QSysInfo::productType() == "windows")
    {
        disckSelBox = new QComboBox(this);
        QFileInfoList list = QDir::drives();
        QFileInfoList::const_iterator listdisk = list.begin();
        int amount = list.count();
        for(int i = 0;i<amount;i++){
            disckSelBox->addItem(listdisk->path());
            listdisk++;
        }
        if(amount > 0){
            rebuildModel(list.at(0).path());
        }
        gridLay->addWidget(disckSelBox,0,0,1,2);
        pathLine->setText(list.at(0).path());
        connect(disckSelBox,SIGNAL(activated(int)), this,SLOT(chgDisk(int)));
        connect(tree,SIGNAL(clicked(const QModelIndex &)), this,SLOT(chgPath(QModelIndex)));
        connect(back_button,SIGNAL(clicked()), this,SLOT(backSl()));
    }
    else{
        mainPath = new QPushButton(this);
        mainPath->setText("/");
        gridLay->addWidget(mainPath, 0, 0, 1, 2);
        connect(mainPath,SIGNAL(clicked()), this,SLOT(goMainPath()));
        rebuildModel("/");
    }
}

void SystemViewWidget::backSl(){
    int x = currentPath.lastIndexOf("/",currentPath.count()-2);
    if((x!= -1) || (currentPath.count("/") != 1)){
        currentPath.remove(x+1,currentPath.count());
        rebuildModel(currentPath);
    }
}


void SystemViewWidget::chgDisk(int index){
    QFileInfoList list = QDir::drives();
    rebuildModel(list.at(index).path());
}

void SystemViewWidget::chgPath(QModelIndex index){
    QString nPath = index.data().toString();
    currentPath +=nPath + "/";
    QFileInfoList list = QDir::drives();
    rebuildModel(currentPath);
}

void SystemViewWidget::goMainPath(){
    rebuildModel("/");
}

void SystemViewWidget::setNewModel(QStandardItemModel * newmodel){
    tree->setModel(newmodel);
    model = newmodel;
}

void SystemViewWidget::rebuildModel(QString str)
{
    pathLine->setText(" ");
    model->clear();
    currentPath = str;
    QList<QStandardItem*> items;
    items.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)),str));
    model->appendRow(items);

    QDir dir(str);
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
    QStringList list = dir.entryList();
    int amount = list.count();
    QList<QStandardItem*> folders;
    for(int i =0; i<amount;i++){
        QStandardItem *f =  new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i));
        folders.append(f);
    }
    items.at(0)->appendRows(folders);
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
    amount = list.count();
    QList<QStandardItem*> files;
    for(int i = 0;i<amount;i++){
        QStandardItem * f =  new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)), list.at(i));
        files.append(f);
    }
    pathLine->setText(str);
    items.at(0)->appendRows(files);
    setNewModel(model);
}

SystemViewWidget::~SystemViewWidget(){
    delete gridLay;
    delete tree;
    delete mainPath;
    delete back_button;
    delete disckSelBox;
    delete pathLine;
    delete model;
}




























