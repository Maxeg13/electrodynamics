#include "mainwindow.h"
#include "vector"
#include "stdio.h"
#include "QGridLayout"
#include "QTimer"
#include "constants.h"
#include "fdtd_1d_maxwell.h"
#include "pulse.h"

using namespace std;
char *tag="v1"; // used to label output files
double tau = 1.0; // fs, width of the pulse
double w0=0;
/*** Computational parameters ***/
int Nx = 4000; // number of
double dx = 20.0; // nm
double xi = 0.9;
int ix0 = 1000; //
int No = 1000; // defines the output rate
double dt = xi*dx/speed; // in fs
//printf("dx=%.12e nm, dt=%.12e fs\n", dx, dt);
/*** arrays for the fields ***/
double *fields;
double *Hz;
double *Ey;
int T=0; // total steps

QTimer* timer;
#define n_plot 2

int i1=1;
myCurve *elCurve[n_plot];
vector<vector<float>> dataV;

QwtPlot* d_plot[n_plot];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
//    qDebug()<<speed;
    fields = new double[2*Nx*sizeof(double)];
    Hz = fields+0*Nx;
    Ey = fields+1*Nx;
    create_initial_dist(Nx,Ey,Hz,dx,dt,speed,ix0,tau,w0);

    timer=new QTimer(this);
    timer->start(1);
    connect(timer,SIGNAL(timeout()), this, SLOT(loop()));

    dataV.resize(2);
    for(int i=0;i<2;i++)
        dataV[i].resize(Nx,0);

    for(int i=0;i<Nx;i++)
        dataV[0][i]=Ey[i];

    d_plot[0] = new QwtPlot(this);
    drawingInit(d_plot[0],QString("ED show"));
    d_plot[0]->setAxisScale(QwtPlot::yLeft,-1.5,1.5);
    d_plot[0]->setAxisScale(QwtPlot::xBottom,0,Nx*dx);
    d_plot[0]->setAxisTitle(QwtPlot::yLeft, "Ey");
    d_plot[0]->setAxisTitle(QwtPlot::xBottom, "time, ns");
    elCurve[0]=new myCurve(Nx, dataV[0],d_plot[0],"ED",Qt::black,Qt::black,i1);
//    d_plot[0]->setAxisScale(QwtPlot::xBottom ,0,Nx);
//    d_plot[0]->setAxisScale(QwtPlot::yLeft,-1.5,1.5);

    QGridLayout* MW=new QGridLayout();
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(MW);
    this->resize(QSize(600,450));
    MW->addWidget(d_plot[0]);
    //    MW->addWidget(d_plot,2,1,2,4);
    setCentralWidget(centralWidget);

    elCurve[0]->signalDrawing();
}

void MainWindow::drawingInit(QwtPlot* d_plot, QString title)
{
    d_plot->setAutoReplot();
    //_______232

    // настройка функций
    QwtPlotPicker *d_picker =
            new QwtPlotPicker(
                QwtPlot::xBottom, QwtPlot::yLeft, // ассоциация с осями
                QwtPlotPicker::CrossRubberBand, // стиль перпендикулярных линий
                QwtPicker::ActiveOnly, // включение/выключение
                d_plot->canvas() ); // ассоциация с полем
    // Цвет перпендикулярных линий
    d_picker->setRubberBandPen( QColor( Qt::red ) );

    // цвет координат положения указателя
    d_picker->setTrackerPen( QColor( Qt::black ) );

    // непосредственное включение вышеописанных функций
    d_picker->setStateMachine( new QwtPickerDragPointMachine() );

    // Включить возможность приближения/удаления графика
    // #include <qwt_plot_magnifier.h>
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(d_plot->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
    // Включить возможность перемещения по графику
    // #include <qwt_plot_panner.h>
    QwtPlotPanner *d_panner = new QwtPlotPanner( d_plot->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );
    // Включить отображение координат курсора и двух перпендикулярных
    // линий в месте его отображения

    QwtText* qwtt=new QwtText(title);
    qwtt->setFont(QFont("Helvetica", 11,QFont::Normal));

//    d_plot->setAxisScale(1,-500,500,200);
    d_plot->setTitle( *qwtt ); // заголовок
    d_plot->setCanvasBackground( Qt::white ); // цвет фона



}
void MainWindow::loop()
{
    update_Bz(Nx, Hz, Ey, xi);
    update_Dy(Nx, Ey, Hz, xi);
    for(int i=0;i<Nx;i++)
        dataV[0][i]=Ey[i];
    elCurve[0]->signalDrawing();


}
MainWindow::~MainWindow()
{

}
