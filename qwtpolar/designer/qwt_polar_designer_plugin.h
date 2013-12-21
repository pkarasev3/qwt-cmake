/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * QwtPolar Widget Library
 * Copyright (C) 2008   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef QWT_DESIGNER_PLUGIN_H
#define QWT_DESIGNER_PLUGIN_H

#include <qglobal.h>

#include <QDesignerCustomWidgetInterface>
#include <QDesignerTaskMenuExtension>
#include <QExtensionFactory>

namespace QwtPolarDesignerPlugin
{
    class PolarPlotInterface: public QObject,
        public QDesignerCustomWidgetInterface
    {
        Q_OBJECT
        Q_INTERFACES( QDesignerCustomWidgetInterface )

    public:
        PolarPlotInterface( QObject *parent );

        virtual bool isContainer() const;
        virtual QIcon icon() const;
        virtual QString domXml() const;
        virtual QString group() const;
        virtual QString includeFile() const;
        virtual QString name() const;
        virtual QString toolTip() const;
        virtual QString whatsThis() const;
        virtual QWidget *createWidget( QWidget *parent );
    };

    class CustomWidgetCollectionInterface: public QObject,
        public QDesignerCustomWidgetCollectionInterface
    {
        Q_OBJECT
        Q_INTERFACES( QDesignerCustomWidgetCollectionInterface )

#if QT_VERSION >= 0x050000
        Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface" )
#endif
    public:
        CustomWidgetCollectionInterface( QObject *parent = NULL );

        virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

    private:
        QList<QDesignerCustomWidgetInterface*> d_plugins;
    };

}

#endif
