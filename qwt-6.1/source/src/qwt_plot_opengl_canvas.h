/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifdef USING_QT5

#ifndef QWT_PLOT_OPENGL_CANVAS_H
#define QWT_PLOT_OPENGL_CANVAS_H

#include "qgl.h"
#include "qopengl.h"
#include "qwt_global.h"
#include "qwt_plot_abstract_canvas.h"
#include <qopenglwidget.h>

class QwtPlot;

class QWT_EXPORT QwtPlotOpenGLCanvas: public QOpenGLWidget, public QwtPlotAbstractGLCanvas
{
    Q_OBJECT

public:
    explicit QwtPlotOpenGLCanvas( QwtPlot * = NULL );
    explicit QwtPlotOpenGLCanvas( const QSurfaceFormat &, QwtPlot * = NULL);
    virtual ~QwtPlotOpenGLCanvas();

    Q_INVOKABLE virtual void invalidateBackingStore();
    Q_INVOKABLE QPainterPath borderPath( const QRect & ) const;

    virtual bool event( QEvent * );

public Q_SLOTS:
    void replot();

protected:
    virtual void paintEvent( QPaintEvent * );

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL( int width, int height );

private:
    class PrivateData;
    PrivateData *d_data;
};

#endif

#endif