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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QTimer>
#include <QQueue>
#include <QUrl>
#include <qhttpserver.hpp>

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
    void onUrlReceived(QUrl * u);

signals:
    void urlReceived(QUrl * u);

private:
    Ui::MainWindow *ui;
    QWebEngineView *web;
    QWebEnginePage *firstP;
    QWebEnginePage *secondP;
    QTimer *timer;
    qhttp::server::QHttpServer *srv;
    QQueue<QUrl> *q;
};

#endif // MAINWINDOW_H
