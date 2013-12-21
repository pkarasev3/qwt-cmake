#include <qmainwindow.h>

class Plot;
class SettingsEditor;
class QwtPolarPanner;
class QwtPolarMagnifier;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = NULL );

private Q_SLOTS:
    void enableZoomMode( bool on );
    void printDocument();
    void exportDocument();

private:
    Plot *d_plot;
    QwtPolarPanner *d_panner;
    QwtPolarMagnifier *d_zoomer;
    SettingsEditor *d_settingsEditor;
};
