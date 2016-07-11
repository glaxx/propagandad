/*
 *    Copyright (C) 2016 Stefan Luecke
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Affero General Public License as published
 *    by the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    Authors:
 *      Stefan Luecke <glaxx@glaxx.net>
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("propagandad");
    web = new QWebEngineView(this);

    firstP = new QWebEnginePage(this);
    firstP->load(QUrl("http://kuchengabel.de"));

    secondP = new QWebEnginePage(this);
    secondP->load(QUrl("http://endless.horse"));

    q = new QQueue<QUrl>;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(switchPages()));
    timer->start(10000);

    web->setPage(firstP);
    web->show();

    ui->horizontalLayout->addWidget(web);
    this->showFullScreen();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete q;
}

void MainWindow::onUrlReceived(QUrl * u) {
    qDebug() << Q_FUNC_INFO;
    q->enqueue(*u);
}

void MainWindow::switchPages() {
    web->page()->runJavaScript(QString("ola_infoscreen_stop();"));
    if (web->page() == firstP) {
        web->setPage(secondP);
        if( !(q->isEmpty() ) ) {
            firstP->setUrl(q->dequeue());
        }
    } else {
        web->setPage(firstP);
        if( !(q->isEmpty() ) ) {
            secondP->setUrl(q->dequeue());
        }
    }
    web->page()->runJavaScript(QString("ola_infoscreen_start();"));
}
