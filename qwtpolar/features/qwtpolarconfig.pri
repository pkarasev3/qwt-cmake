# -*- mode: sh -*- ##############################################
# QwtPolar Widget Library
# Copyright (C) 2008   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
#################################################################

######################################################################
# Install paths
######################################################################

QWT_POLAR_VER_MAJ      = 1
QWT_POLAR_VER_MIN      = 0
QWT_POLAR_VER_PAT      = 0
QWT_POLAR_VERSION      = $${QWT_POLAR_VER_MAJ}.$${QWT_POLAR_VER_MIN}.$${QWT_POLAR_VER_PAT}

#unix {
    QWT_POLAR_INSTALL_PREFIX    = /a/new/sr/proton/d13/longvo01/EesofTools/Linux/gcc462/linux_x86_64/qwtpolar/1.1.1/linux_x86_64
#}

#win32 {
#    QWT_POLAR_INSTALL_PREFIX    = C:/QwtPolar-$$QWT_POLAR_VERSION-svn
#}

QWT_POLAR_INSTALL_DOCS      = $${QWT_POLAR_INSTALL_PREFIX}/doc
QWT_POLAR_INSTALL_HEADERS   = $${QWT_POLAR_INSTALL_PREFIX}/include
QWT_POLAR_INSTALL_LIBS      = $${QWT_POLAR_INSTALL_PREFIX}/lib

######################################################################
# Designer plugin
######################################################################

#QWT_POLAR_INSTALL_PLUGINS   = $${QWT_POLAR_INSTALL_PREFIX}/plugins/designer
# QWT_POLAR_INSTALL_PLUGINS   = $${QT_INSTALL_PREFIX}/plugins/designer

######################################################################
# Build the static/shared libraries.
# If QwtPolarDll is enabled, a shared library is built, otherwise
# it will be a static library.
######################################################################

QWT_POLAR_CONFIG           += QwtPolarDll

######################################################################
# If you want to export a plot to a SVG document
######################################################################

QWT_POLAR_CONFIG     += QwtPolarSvg

######################################################################
# Features
# When building a QwtPolar application with qmake you might want to load
# the compiler/linker flags, that are required to build a Qwt application
# from qwtpolar.prf. Therefore all you need to do is to add 
# "CONFIG += qwtpolar" to your project file and take care, that 
# qwtpolar.prf can be found by qmake.
# ( see http://doc.trolltech.com/4.7/qmake-advanced-usage.html#adding-new-configuration-features )
# I recommend not to install the QwtPolar features together with the
# Qt features, because you will have to reinstall the QwtPolar features,
# with every Qt upgrade. 
######################################################################

QWT_POLAR_INSTALL_FEATURES  = $${QWT_POLAR_INSTALL_PREFIX}/features
# QWT_INSTALL_FEATURES  = $${QT_INSTALL_PREFIX}/features

######################################################################
# If you want to build the QwtPolar designer plugin,
# enable the line below.
# Otherwise you have to build it from the designer directory.
######################################################################

#QWT_POLAR_CONFIG     += QwtPolarDesigner

######################################################################
# If you want to auto build the examples, enable the line below
# Otherwise you have to build them from the examples directory.
######################################################################

# QWT_POLAR_CONFIG     += QwtPolarExamples
