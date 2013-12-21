# -*- mode: sh -*- ##############################################
# QwtPolar Widget Library
# Copyright (C) 2008   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
#################################################################

include( $${PWD}/../examples.pri )

QT          += svg

TARGET       = polardemo

SOURCES = \
	mainwindow.cpp \
	plot.cpp \
	settingseditor.cpp \
	main.cpp

HEADERS = \
	pixmaps.h \
	mainwindow.h \
	plot.h \
	settingseditor.h

