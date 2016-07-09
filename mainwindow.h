#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void switchPages();

private:
    Ui::MainWindow *ui;
    QWebEngineView *web;
    QWebEnginePage *firstP;
    QWebEnginePage *secondP;
    QTimer *timer;
};

#endif // MAINWINDOW_H
