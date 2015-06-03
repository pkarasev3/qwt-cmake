/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef QWT_PLOT_ABSTRACT_CANVAS_H
#define QWT_PLOT_ABSTRACT_CANVAS_H

#include "qwt_global.h"
#include <qframe.h>

class QWT_EXPORT QwtPlotAbstractCanvas
{
    Q_GADGET

public:
    /*!
      \brief Focus indicator
      The default setting is NoFocusIndicator
      \sa setFocusIndicator(), focusIndicator(), paintFocus()
    */

    enum FocusIndicator
    {
        //! Don't paint a focus indicator
        NoFocusIndicator,

        /*!
          The focus is related to the complete canvas.
          Paint the focus indicator using paintFocus()
         */
        CanvasFocusIndicator,

        /*!
          The focus is related to an item (curve, point, ...) on
          the canvas. It is up to the application to display a
          focus indication using f.e. highlighting.
         */
        ItemFocusIndicator
    };

    explicit QwtPlotAbstractCanvas( QWidget *canvasWidget );
    virtual ~QwtPlotAbstractCanvas();

    void setFocusIndicator( FocusIndicator );
    FocusIndicator focusIndicator() const;

    void setBorderRadius( double );
    double borderRadius() const;

protected:
    QWidget* canvasWidget();
    const QWidget* canvasWidget() const;

    virtual void drawFocusIndicator( QPainter * );

private:
    class PrivateData;
    PrivateData *d_data;
};

class QWT_EXPORT QwtPlotAbstractGLCanvas: public QwtPlotAbstractCanvas
{
    Q_GADGET

    Q_ENUMS( Shape Shadow )

    Q_PROPERTY( Shadow frameShadow READ frameShadow WRITE setFrameShadow )
    Q_PROPERTY( Shape frameShape READ frameShape WRITE setFrameShape )
    Q_PROPERTY( int lineWidth READ lineWidth WRITE setLineWidth )
    Q_PROPERTY( int midLineWidth READ midLineWidth WRITE setMidLineWidth )
    Q_PROPERTY( int frameWidth READ frameWidth )
    Q_PROPERTY( QRect frameRect READ frameRect DESIGNABLE false )

public:
    /*!
      \brief Paint attributes

      The default setting enables BackingStore and Opaque.

      \sa setPaintAttribute(), testPaintAttribute()
     */
    enum PaintAttribute
    {
        /*!
          \brief Paint double buffered reusing the content 
                 of the pixmap buffer when possible. 

          Using a backing store might improve the performance
          significantly, when working with widget overlays ( like rubber bands ).
          Disabling the cache might improve the performance for
          incremental paints (using QwtPlotDirectPainter ).

          \sa backingStore(), invalidateBackingStore()
         */
        BackingStore = 1,

        /*!
          When ImmediatePaint is set replot() calls repaint()
          instead of update().

          \sa replot(), QWidget::repaint(), QWidget::update()
         */
        ImmediatePaint = 8,
    };

    //! Paint attributes
    typedef QFlags<PaintAttribute> PaintAttributes;

    /*!
        \brief Frame shadow

         Unfortunately it is not possible to use QFrame::Shadow
         as a property of a widget that is not derived from QFrame.
         The following enum is made for the designer only. It is safe
         to use QFrame::Shadow instead.
     */
    enum Shadow
    {
        //! QFrame::Plain
        Plain = QFrame::Plain,

        //! QFrame::Raised
        Raised = QFrame::Raised,

        //! QFrame::Sunken
        Sunken = QFrame::Sunken
    };

    /*!
        \brief Frame shape

        Unfortunately it is not possible to use QFrame::Shape
        as a property of a widget that is not derived from QFrame.
        The following enum is made for the designer only. It is safe
        to use QFrame::Shadow instead.

        \note QFrame::StyledPanel and QFrame::WinPanel are unsuported 
              and will be displayed as QFrame::Panel.
     */
    enum Shape
    {
        NoFrame = QFrame::NoFrame,

        Box = QFrame::Box,
        Panel = QFrame::Panel
    };

    explicit QwtPlotAbstractGLCanvas( QWidget *canvasWidget );
    virtual ~QwtPlotAbstractGLCanvas();

    void setPaintAttribute( PaintAttribute, bool on = true );
    bool testPaintAttribute( PaintAttribute ) const;

    void setFrameStyle( int style );
    int frameStyle() const;

    void setFrameShadow( Shadow );
    Shadow frameShadow() const;

    void setFrameShape( Shape );
    Shape frameShape() const;

    void setLineWidth( int );
    int lineWidth() const;

    void setMidLineWidth( int );
    int midLineWidth() const;

    int frameWidth() const;
    QRect frameRect() const;

    QPainterPath borderPath( const QRect & ) const;
    virtual void invalidateBackingStore() = 0;

protected:
    void replot();

    void draw( QPainter * );
    virtual void drawBackground( QPainter * );
    virtual void drawBorder( QPainter * );
    virtual void drawItems( QPainter * );

private:
    class PrivateData;
    PrivateData *d_data;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( QwtPlotAbstractGLCanvas::PaintAttributes )

#endif
