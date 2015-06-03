/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_plot_abstract_canvas.h"
#include "qwt_plot.h"
#include "qwt_painter.h"
#include <qpainter.h>
#include <qdrawutil.h>
#include <qstyle.h>
#include <qstyleoption.h>

static QWidget *qwtBGWidget( QWidget *widget )
{
    QWidget *w = widget;

    for ( ; w->parentWidget() != NULL; w = w->parentWidget() )
    {
        if ( w->autoFillBackground() || 
            w->testAttribute( Qt::WA_StyledBackground ) )
        {
            return w;
        }
    }

    return w;
}

static void qwtUpdateContentsRect( int fw, QWidget *canvas )
{
    canvas->setContentsMargins( fw, fw, fw, fw );
}

class QwtPlotAbstractCanvas::PrivateData
{
public:
    PrivateData():
        focusIndicator( NoFocusIndicator ),
        borderRadius( 0 )
    {
    }

    FocusIndicator focusIndicator;
    double borderRadius;

    QWidget *canvasWidget;
};

QwtPlotAbstractCanvas::QwtPlotAbstractCanvas( QWidget *canvasWidget )
{
    d_data = new PrivateData;
    d_data->canvasWidget = canvasWidget;

#ifndef QT_NO_CURSOR
    d_data->canvasWidget->setCursor( Qt::CrossCursor );
#endif

    d_data->canvasWidget->setAutoFillBackground( true );
}

QwtPlotAbstractCanvas::~QwtPlotAbstractCanvas()
{
    delete d_data;
}

/*!
  Set the focus indicator

  \sa FocusIndicator, focusIndicator()
*/
void QwtPlotAbstractCanvas::setFocusIndicator( FocusIndicator focusIndicator )
{
    d_data->focusIndicator = focusIndicator;
}

/*!
  \return Focus indicator

  \sa FocusIndicator, setFocusIndicator()
*/
QwtPlotAbstractCanvas::FocusIndicator QwtPlotAbstractCanvas::focusIndicator() const
{
    return d_data->focusIndicator;
}

/*!
  Draw the focus indication
  \param painter Painter
*/
void QwtPlotAbstractCanvas::drawFocusIndicator( QPainter *painter )
{
    const int margin = 1;

    QRect focusRect = d_data->canvasWidget->contentsRect();
    focusRect.setRect( focusRect.x() + margin, focusRect.y() + margin,
        focusRect.width() - 2 * margin, focusRect.height() - 2 * margin );

    QwtPainter::drawFocusRect( painter, d_data->canvasWidget, focusRect );
}

/*!
  Set the radius for the corners of the border frame

  \param radius Radius of a rounded corner
  \sa borderRadius()
*/
void QwtPlotAbstractCanvas::setBorderRadius( double radius )
{
    d_data->borderRadius = qMax( 0.0, radius );
}

/*!
  \return Radius for the corners of the border frame
  \sa setBorderRadius()
*/
double QwtPlotAbstractCanvas::borderRadius() const
{
    return d_data->borderRadius;
}

QWidget* QwtPlotAbstractCanvas::canvasWidget()
{
    return d_data->canvasWidget;
}

const QWidget* QwtPlotAbstractCanvas::canvasWidget() const
{
    return d_data->canvasWidget;
}

class QwtPlotAbstractGLCanvas::PrivateData
{
public:
    PrivateData():
        frameStyle( QFrame::Panel | QFrame::Sunken),
        lineWidth( 2 ),
        midLineWidth( 0 )
    {
    }

    ~PrivateData()
    {
    }

    QwtPlotAbstractGLCanvas::PaintAttributes paintAttributes;

    int frameStyle;
    int lineWidth;
    int midLineWidth;
};

QwtPlotAbstractGLCanvas::QwtPlotAbstractGLCanvas( QWidget *canvasWidget ):
    QwtPlotAbstractCanvas( canvasWidget )
{
    d_data = new PrivateData;

    qwtUpdateContentsRect( frameWidth(), canvasWidget );
    d_data->paintAttributes = QwtPlotAbstractGLCanvas::BackingStore;
}

QwtPlotAbstractGLCanvas::~QwtPlotAbstractGLCanvas()
{
    delete d_data;
}

/*!
  \brief Changing the paint attributes

  \param attribute Paint attribute
  \param on On/Off

  \sa testPaintAttribute()
*/
void QwtPlotAbstractGLCanvas::setPaintAttribute( PaintAttribute attribute, bool on )
{   
    if ( bool( d_data->paintAttributes & attribute ) == on )
        return;
    
    if ( on )
        d_data->paintAttributes |= attribute;
    else
        d_data->paintAttributes &= ~attribute;

    if ( attribute == BackingStore )
        invalidateBackingStore();
}

/*!
  Test whether a paint attribute is enabled

  \param attribute Paint attribute
  \return true, when attribute is enabled
  \sa setPaintAttribute()
*/  
bool QwtPlotAbstractGLCanvas::testPaintAttribute( PaintAttribute attribute ) const
{   
    return d_data->paintAttributes & attribute;
}

/*!
  Set the frame style

  \param style The bitwise OR between a shape and a shadow. 
  
  \sa frameStyle(), QFrame::setFrameStyle(), 
      setFrameShadow(), setFrameShape()
 */
void QwtPlotAbstractGLCanvas::setFrameStyle( int style )
{
    if ( style != d_data->frameStyle )
    {
        d_data->frameStyle = style;
        qwtUpdateContentsRect( frameWidth(), canvasWidget() );

        canvasWidget()->update();
    }
}

/*!
  \return The bitwise OR between a frameShape() and a frameShadow()
  \sa setFrameStyle(), QFrame::frameStyle()
 */
int QwtPlotAbstractGLCanvas::frameStyle() const
{
    return d_data->frameStyle;
}

/*!
  Set the frame shadow

  \param shadow Frame shadow
  \sa frameShadow(), setFrameShape(), QFrame::setFrameShadow()
 */
void QwtPlotAbstractGLCanvas::setFrameShadow( Shadow shadow )
{
    setFrameStyle(( d_data->frameStyle & QFrame::Shape_Mask ) | shadow );
}

/*!
  \return Frame shadow
  \sa setFrameShadow(), QFrame::setFrameShadow()
 */
QwtPlotAbstractGLCanvas::Shadow QwtPlotAbstractGLCanvas::frameShadow() const
{
    return (Shadow) ( d_data->frameStyle & QFrame::Shadow_Mask );
}

/*!
  Set the frame shape

  \param shape Frame shape
  \sa frameShape(), setFrameShadow(), QFrame::frameShape()
 */
void QwtPlotAbstractGLCanvas::setFrameShape( Shape shape )
{
    setFrameStyle( ( d_data->frameStyle & QFrame::Shadow_Mask ) | shape );
}

/*!
  \return Frame shape
  \sa setFrameShape(), QFrame::frameShape()
 */
QwtPlotAbstractGLCanvas::Shape QwtPlotAbstractGLCanvas::frameShape() const
{
    return (Shape) ( d_data->frameStyle & QFrame::Shape_Mask );
}

/*!
   Set the frame line width

   The default line width is 2 pixels.

   \param width Line width of the frame
   \sa lineWidth(), setMidLineWidth()
*/
void QwtPlotAbstractGLCanvas::setLineWidth( int width )
{
    width = qMax( width, 0 );
    if ( width != d_data->lineWidth )
    {
        d_data->lineWidth = qMax( width, 0 );
        qwtUpdateContentsRect( frameWidth(), canvasWidget() );
        canvasWidget()->update();
    }
}

/*!
  \return Line width of the frame
  \sa setLineWidth(), midLineWidth()
 */
int QwtPlotAbstractGLCanvas::lineWidth() const
{
    return d_data->lineWidth;
}

/*!
   Set the frame mid line width

   The default midline width is 0 pixels.

   \param width Midline width of the frame
   \sa midLineWidth(), setLineWidth()
*/
void QwtPlotAbstractGLCanvas::setMidLineWidth( int width )
{
    width = qMax( width, 0 );
    if ( width != d_data->midLineWidth )
    {
        d_data->midLineWidth = width;
        qwtUpdateContentsRect( frameWidth(), canvasWidget() );
        canvasWidget()->update();
    }
}

/*!
  \return Midline width of the frame
  \sa setMidLineWidth(), lineWidth()
 */ 
int QwtPlotAbstractGLCanvas::midLineWidth() const
{
    return d_data->midLineWidth;
}

/*!
  \return Frame width depending on the style, line width and midline width.
 */
int QwtPlotAbstractGLCanvas::frameWidth() const
{
    return ( frameStyle() != NoFrame ) ? d_data->lineWidth : 0;
}

void QwtPlotAbstractGLCanvas::replot()
{
    invalidateBackingStore();
    
    QWidget *w = canvasWidget();
    if ( testPaintAttribute( QwtPlotAbstractGLCanvas::ImmediatePaint ) )
        w->repaint( w->contentsRect() );
    else
        w->update( w->contentsRect() );
}

/*!
  Draw the plot items
  \param painter Painter

  \sa QwtPlot::drawCanvas()
*/  
void QwtPlotAbstractGLCanvas::drawItems( QPainter *painter )
{
    QwtPlot *plot = qobject_cast< QwtPlot *>( canvasWidget()->parent() );
    if ( plot )
    {
        painter->save();
        painter->setClipRect( canvasWidget()->contentsRect(), Qt::IntersectClip );

        plot->drawCanvas( painter );

        painter->restore();
    }
}

/*!
  Draw the background of the canvas
  \param painter Painter
*/ 
void QwtPlotAbstractGLCanvas::drawBackground( QPainter *painter )
{
    painter->save();

    QWidget *w = qwtBGWidget( canvasWidget() );

    const QPoint off = canvasWidget()->mapTo( w, QPoint() );
    painter->translate( -off );

    const QRect fillRect = canvasWidget()->rect().translated( off );

    if ( w->testAttribute( Qt::WA_StyledBackground ) )
    {
        painter->setClipRect( fillRect );

        QStyleOption opt;
        opt.initFrom( w );
        w->style()->drawPrimitive( QStyle::PE_Widget, &opt, painter, w);
    }
    else 
    {
#if 0
        if ( !autoFillBackground() )
#endif
        {
            painter->fillRect( fillRect,
                w->palette().brush( w->backgroundRole() ) );
        }
    }

    painter->restore();
}

/*!
  Draw the border of the canvas
  \param painter Painter
*/
void QwtPlotAbstractGLCanvas::drawBorder( QPainter *painter )
{
    const QPalette palette = canvasWidget()->palette();

    if ( borderRadius() > 0 )
    {
        if ( frameWidth() > 0 )
        {
            QwtPainter::drawRoundedFrame( painter, QRectF( frameRect() ),
                borderRadius(), borderRadius(),
                palette, frameWidth(), frameStyle() );
        }
    }
    else
    {
        const int fw = frameWidth();
        if ( fw <= 0 )
            return;

        if ( frameShadow() == QwtPlotAbstractGLCanvas::Plain )
        {
            qDrawPlainRect( painter, frameRect(), 
                palette.shadow().color(), lineWidth() );
        }
        else
        {
            if ( frameShape() == QwtPlotAbstractGLCanvas::Box )
            {
                qDrawShadeRect( painter, frameRect(), palette,
                    frameShadow() == Sunken, lineWidth(), midLineWidth() );
            }
            else
            {
                qDrawShadePanel( painter, frameRect(), palette, 
                    frameShadow() == Sunken, lineWidth() );
            }
        }
    }
}

/*!
   \return Empty path
*/
QPainterPath QwtPlotAbstractGLCanvas::borderPath( const QRect &rect ) const
{
    Q_UNUSED( rect );
    return QPainterPath();
}

//! \return The rectangle where the frame is drawn in.
QRect QwtPlotAbstractGLCanvas::frameRect() const
{
    const int fw = frameWidth();
    return canvasWidget()->contentsRect().adjusted( -fw, -fw, fw, fw );
}

void QwtPlotAbstractGLCanvas::draw( QPainter *painter )
{
#if FIX_GL_TRANSLATION
    if ( painter->paintEngine()->type() == QPaintEngine::OpenGL2 )
    {
        // work around a translation bug of QPaintEngine::OpenGL2
        painter->translate( 1, 1 );
    }
#endif

    drawBackground( painter );
    drawItems( painter );

    if ( !canvasWidget()->testAttribute( Qt::WA_StyledBackground ) )
    { 
        if ( frameWidth() > 0 )
            drawBorder( painter );
    }
}
