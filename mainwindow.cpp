#include "mainwindow.h"
#include "vector"
#include "QGridLayout"
#include "QTimer"
#include "constants.h"
#include "fdtd_1d_maxwell.h"
#include "pulse.h"
#include "QKeyEvent"
#include "QLineEdit"


 #include<stdio.h>
 #include<stdlib.h>
//#include<string.h>
 #include<math.h>
 #include<complex>

#include"mater.h"
#include"set_mem.h"
#include"rfourier.h"
typedef  complex<double> dcomplex;


QLineEdit* LE;
using namespace std;

char *tag="v1"; // used to label output files
double eslab = 4.0; // permittivity of the slab
double lambda0 = 1000; // nm
double tau = 8; // fs, width of the pulse

/*** Computational parameters ***/
double dx = 20.0; // nm
int Nx = 20000; // number of
int Nx_part=Nx/4;

int ix0 = 9000;

int Nslab = 200; // width of the slab

int si1 = 10000; // start of the slab
int si2 = si1+Nslab-1; // end of the slab

int fi1 = 7500; //
int fi2 = si2+10; //

double xi = 0.9;
int No = 200; // defines the output rate

/*** start exe
ution ***/
double w0 = 2*pi*speed/lambda0; // rad/fs
double dt = xi*dx/speed; // in fs


/*** arrays for the fields ***/
double *fields = new double[3*Nx];
double *Hz = fields+0*Nx;
double *Ey = fields+1*Nx;
double *Dy = fields+2*Nx;
double *eps = new double[Nx];


double wmin = 0.8*w0; // rad/fs
double wmax = 1.2*w0; // rad/fs
int Nw=200;

dcomplex *ftall=new dcomplex[2*Nw];
dcomplex *ft1 = ftall + 0*Nw;
dcomplex *ft2 = ftall + 1*Nw;

int T=0; // total steps


QTimer* timer;
#define n_plot 2

int i1=1;
myCurve *elCurve[n_plot], *magCurve[n_plot];
vector<vector<float>> dataE, dataH, dataWave;

QwtPlot* d_plot[n_plot];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    zset_mem(2*Nw, ftall, 0.0+dcomplex(0,1)*0.0);
    create_slab(Nx, eps, si1, si2, eslab);
//    output_eps_x(Nx, eps, dx, tag);
    create_initial_dist(Nx, Dy, Hz, dx, dt,speed, ix0, tau, w0,1);
    update_Ey(Nx, Ey, Dy, eps);
//    output_Ey_vs_x(Nx, Ey, 0, dx, tag);
    //    qDebug()<<speed;
    //    fields = new double[2*Nx*sizeof(double)];
    //    Hz = fields+0*Nx;
    //    Ey = fields+1*Nx;
    for(int i=0;i<Nx;i++)
    {
        Ey[i]=0;
        Dy[i]=0;
        Hz[i]=0;
        eps[i]=0;
    }
    //    create_initial_monochrom(Ey,Hz,dx,2*pi/5000.,dx*Nx/4,1);
    //    create_initial_monochrom(Ey,Hz,dx,2*pi/5000.,dx*Nx/4,-1);
    //create_initial_monochrom(Ey,Hz,dx,2*pi/40.,10000,1);

    create_initial_dist(Nx,Ey,Hz,dx,dt,speed,2000,tau,w0,1);
    //    create_initial_dist(Nx,Ey,Hz,dx,dt,speed,2250,tau,w0,-1);

    timer=new QTimer(this);
    timer->start(42);
    //    connect(timer,SIGNAL(timeout()), this, SLOT(loop()));

    dataE.resize(2);
    for(int i=0;i<2;i++)
        dataE[i].resize(Nx,0);
    for(int i=0;i<Nx;i++)
    {
        dataE[0][i]=dx*i;
        dataE[1][i]=Ey[i];
    }

    dataWave.resize(2);
    dataWave[0].resize(Nx_part,0);
    dataWave[1].resize(Nx_part,0);
    for(int i=0;i<Nx_part;i++)
    {
        dataWave[0][i]=dataE[0][i];
        dataWave[1][i]=dataE[1][i];
    }

    dataH.resize(2);
    for(int i=0;i<2;i++)
        dataH[i].resize(Nx,0);
    for(int i=0;i<Nx;i++)
    {
        dataH[0][i]=dx*(i+0.5);
        dataH[1][i]=Hz[i];
    }

    float yBond=1.5;

    d_plot[0] = new QwtPlot(this);
    drawingInit(d_plot[0],QString("ED show"));
    d_plot[0]->setAxisScale(QwtPlot::yLeft,-yBond,yBond);
    d_plot[0]->setAxisScale(QwtPlot::xBottom,0,Nx*dx);
    d_plot[0]->setAxisTitle(QwtPlot::yLeft, "Ey/E, Hz/H");
    d_plot[0]->setAxisTitle(QwtPlot::xBottom, "dist, nm");

    d_plot[1] = new QwtPlot(this);
    drawingInit(d_plot[1],QString("wave"));
    d_plot[1]->setAxisScale(QwtPlot::yLeft,-yBond,yBond);
    d_plot[1]->setAxisScale(QwtPlot::xBottom,0,Nx_part*dx);
    d_plot[1]->setAxisTitle(QwtPlot::yLeft, "Ey/E");
    d_plot[1]->setAxisTitle(QwtPlot::xBottom, "dist, nm");

    elCurve[0]=new myCurve(Nx, dataE,d_plot[0],"ED",Qt::black,Qt::black,i1);
    magCurve[0]=new myCurve(Nx, dataH,d_plot[0],"ED",Qt::green,Qt::green,i1);

    elCurve[1]=new myCurve(Nx_part, dataWave,d_plot[1],"ED",Qt::black,Qt::black,i1);

    LE=new QLineEdit("10");
    QGridLayout* MW=new QGridLayout();
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(MW);

    MW->addWidget(d_plot[0],0,0);
    MW->addWidget(d_plot[1],1,0);
    MW->addWidget(LE,2,0);
    //    MW->addWidget(d_plot,2,1,2,4);
    setCentralWidget(centralWidget);
    this->resize(QSize(600,450));

    elCurve[0]->signalDrawing();
    elCurve[1]->signalDrawing();
    magCurve[0]->signalDrawing();


    //    keyPressEvent(QKeyEvent *event);
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->text()=="s")
    {
        //    qDebug()<<"hello";
        static int dis_i;
        dis_i++;
        dis_i%=2;
        switch(dis_i)
        {
        case 1:
            disconnect(timer,SIGNAL(timeout()), this, SLOT(loop()));break;
        case 0:
            connect(timer,SIGNAL(timeout()), this, SLOT(loop()));break;
        }
    }
    else if(event->text()==" ")
    {
        loop();
    }
}

void MainWindow::loop()
{
    //    QString::toInt()
    static int time_i=0;
    for(int j=0;j<LE->text().toInt();j++)
    {
        time_i+=1;

        update_Bz(Nx, Hz, Ey, xi);
        update_Dy(Nx, Dy, Hz, xi);
        update_Ey(Nx, Ey, Dy, eps);
        for(int i=0;i<Nx;i++)
        {
            dataE[1][i]=Ey[i];
            dataH[1][i]=Hz[i];
        }


        for(int i=0;i<Nx_part;i++)
        {
            //            dataWave[0][i]=dataE[0][time_i+200-100+i];
            //            dataWave[1][i]=dataE[1][time_i+200-100+i];
        }
    }
    qDebug()<<time_i;

    elCurve[0]->signalDrawing();
    elCurve[1]->signalDrawing();
    magCurve[0]->signalDrawing();

    QwtText* qwtt=new QwtText(QString("time=")+QString::number(time_i*dt)+QString(" fs"));
    qwtt->setFont(QFont("Helvetica", 11,QFont::Normal));

    //    d_plot->setAxisScale(1,-500,500,200);
    d_plot[0]->setTitle( *qwtt ); // заголовок
}
MainWindow::~MainWindow()
{

}
