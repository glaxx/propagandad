
 #    Copyright (C) 2016 Stefan Luecke
 #
 #    This program is free software: you can redistribute it and/or modify
 #    it under the terms of the GNU Affero General Public License as published
 #    by the Free Software Foundation, either version 3 of the License, or
 #    (at your option) any later version.
 #
 #    This program is distributed in the hope that it will be useful,
 #    but WITHOUT ANY WARRANTY; without even the implied warranty of
 #    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #    GNU Affero General Public License for more details.
 #
 #    You should have received a copy of the GNU Affero General Public License
 #    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 #
 #    Authors:
 #      Stefan Luecke <glaxx@glaxx.net>
 #


QT       += core gui webenginewidgets
CONFIG   += c++14 qt thread

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = propagandad
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/qhttp/src
LIBS += -L$$PWD/qhttp/xbin -lqhttp
