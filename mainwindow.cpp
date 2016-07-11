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
