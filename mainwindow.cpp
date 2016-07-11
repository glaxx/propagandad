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
#include <qhttpserver.hpp>
#include <qhttpserverrequest.hpp>
#include <qhttpserverresponse.hpp>


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


    connect(this, SIGNAL(urlReceived(QUrl*)), this, SLOT(onUrlReceived(QUrl*)));

    srv = new qhttp::server::QHttpServer(this);
    srv->listen(
        QHostAddress::Any, 8080,
        [=](qhttp::server::QHttpRequest *req, qhttp::server::QHttpResponse *res) {
        req->collectData(1024);

        req->onEnd([this, req, res]() {
            if(req->url().matches(QUrl("/register"), QUrl::RemoveAuthority)) {
                if((req->method() != qhttp::EHTTP_POST) || (req->collectedData().size() == 0)) {
                    res->setStatusCode(qhttp::ESTATUS_BAD_REQUEST);
                    res->end();
                } else {
                    QUrl * u = new QUrl(QString(req->collectedData()));
                    if (u->isValid() && !(u->isEmpty() ) ) {
                        emit urlReceived(u);
                        res->setStatusCode(qhttp::ESTATUS_OK);
                        res->end();
                    }
                }
            } else {
                res->setStatusCode(qhttp::ESTATUS_NOT_FOUND);
                res->end();
            }
        });

    });
}

MainWindow::~MainWindow()
{
    delete srv;
    delete firstP;
    delete secondP;
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
