#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    web = new QWebEngineView(this);

    firstP = new QWebEnginePage(this);
    firstP->load(QUrl("http://heise.de"));

    secondP = new QWebEnginePage(this);
    secondP->load(QUrl("http://google.de"));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(switchPages()));
    timer->start(10000);

    web->setPage(firstP);
    web->show();
    ui->horizontalLayout->addWidget(web);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchPages() {
    web->page()->runJavaScript(QString("ola_infoscreen_stop();"));
    if (web->page() == firstP) {
        web->setPage(secondP);
    } else {
        web->setPage(firstP);
    }
    web->page()->runJavaScript(QString("ola_infoscreen_start();"));
}
