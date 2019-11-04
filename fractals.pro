#***********************************************
# Fractals
#
# Author: Erica
#
# License: GNU General Public License Usage
#***********************************************

TEMPLATE = app
TARGET = fractals
OBJECTS_DIR = ./obj
INCLUDEPATH += .
QT += core gui
QT += widgets

CONFIG += release

# Input
SOURCES += src/*.cc
HEADERS += src/*.h
