#include <qwidget.h>

class Plot;
class QwtScaleWidget;

class PlotWindow: public QWidget
{
public:
    PlotWindow( QWidget * = NULL );

    Plot *plot() { return d_plot; }

private:
    Plot *d_plot;
    QwtScaleWidget *d_colorScale;
};

