#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QResource>
#include <QFile>
#include <QTranslator>
#include <QApplication>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_button_clicked();

    void on_save_button_clicked();

    void on_ref_button_clicked();

    void on_only_reading_button_clicked();

    void on_ru_button_clicked();

    void on_eng_button_clicked();

    void on_black_theme_button_clicked();

    void on_white_theme_button_clicked();

protected:
    virtual void keyReleaseEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;
    QTranslator *translator;
    void lang_switch(QString lang);
};
#endif // MAINWINDOW_H
