#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->save_button->setText(tr("Save"));
    ui->open_button->setText(tr("Open"));
    ui->ref_button->setText(tr("Referance"));
    ui->only_reading_button->setText(tr("Open Only Reading"));
    ui->ru_button->setText(tr("Ru"));
    ui->eng_button->setText(tr("Eng"));
    ui->black_theme_button->setText(tr("Dark Theme"));
    ui->white_theme_button->setText(tr("Light Theme"));
    translator = new QTranslator();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete translator;
}


void MainWindow::on_open_button_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, "window", QDir::current().path(), "Text(*.txt)");
    int index = s.indexOf(".txt");

    if (s.length()!=0){
        if(index != -1 && s.length()-4 == index){
            QFile file(s);
            if(file.open(QFile::ReadOnly | QFile::ExistingOnly))
            {
                QTextStream stream(&file);
                ui->plainTextEdit->setPlainText(stream.readAll());
                ui->plainTextEdit->setReadOnly(false);
                file.close();
            }
        }
    }
}


void MainWindow::on_save_button_clicked()
{
    QString s = QFileDialog::getSaveFileName(this, "window", QDir::current().path(), "Text(*.txt)");
    if(s.length() > 0){
        QString ext = QString(&(s.data()[s.length() - 4]));
        if(ext==".txt"){
            QFile file(s);
            if(file.open(QFile::WriteOnly | QFile::NewOnly))
            {
                QTextStream stream(&file);
                stream << ui->plainTextEdit->toPlainText();
                file.close();
            }
        }
    }
}


void MainWindow::on_ref_button_clicked()
{
    QFile file (":/res/referance.txt");
    if(file.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        QTextStream stream(&file);
        ui->ref_label->setText(stream.readAll());
        file.close();
    }

}

void MainWindow::on_only_reading_button_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, "window", QDir::current().path(), "Text(*.txt)");
    int index = s.indexOf(".txt");

    if (s.length()!=0){
        if(index != -1 && s.length()-4 == index){
            QFile file(s);
            if(file.open(QFile::ReadOnly | QFile::ExistingOnly))
            {
                QTextStream stream(&file);
                ui->plainTextEdit->setPlainText(stream.readAll());
                ui->plainTextEdit->setReadOnly(true);
                file.close();
            }
        }
    }
}


void MainWindow::on_ru_button_clicked()
{
    lang_switch("ru");
}


void MainWindow::on_eng_button_clicked()
{
    lang_switch("en");
}

void MainWindow::lang_switch(QString lang){
    translator->load(":/res/switchlang_" + lang + ".qm");
    qApp->installTranslator(translator);
    ui->save_button->setText(tr("Save"));
    ui->open_button->setText(tr("Open"));
    ui->ref_button->setText(tr("Referance"));
    ui->only_reading_button->setText(tr("Open Only Reading"));
    ui->ru_button->setText(tr("Ru"));
    ui->eng_button->setText(tr("Eng"));
    ui->black_theme_button->setText(tr("Dark Theme"));
    ui->white_theme_button->setText(tr("Light Theme"));
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_O && event->modifiers() == Qt::ControlModifier){
        on_open_button_clicked();
    }
    if(event->key() == Qt::Key_S && event->modifiers() == Qt::ControlModifier){
        on_save_button_clicked();
    }
    if(event->key() == Qt::Key_N && event->modifiers() == Qt::ControlModifier){
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setReadOnly(false);
    }
    if(event->key() == Qt::Key_Q && event->modifiers() == Qt::ControlModifier){
        qApp->quit();
    }
}



void MainWindow::on_black_theme_button_clicked()
{
    qApp->setStyleSheet("QMainWindow { background-color:#808080} QPushButton {background-color:#A9A9A9; color:#000000;}");
}


void MainWindow::on_white_theme_button_clicked()
{
    qApp->setStyleSheet("QMainWindow { background-color:#F5FFFA } QPushButton {background-color:#F0F8FF; color:#808080}");
}

