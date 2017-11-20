#include "mainwindow.h"
#include "vector"
#include "QGridLayout"
#include "QTimer"
#include "constants.h"
#include "fdtd_1d_maxwell.h"
#include "pulse.h"
#include "QKeyEvent"
#include "QLineEdit"
#include "QSlider"
//QGridLayout::setEnabled()

#include <iostream>
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
QSlider* slider_width;
QSlider* slider_eta;
using namespace std;
bool fourb1, fourb2;
char *tag="v1"; // used to label output files
double eslab = 1.; // permittivity of the slab
double lambda0 = 600; // nm
double tau = 5; // fs, width of the pulse
double getMax(double*, int);
/*** Computational parameters ***/
double dx = 20.0; // nm
int Nx = 2500;


int ix0 = 700;//1600

int Nslab = 200; // width of the slab
int width = 100;
int si1 = 1100; // start of the slab
int si2 = si1+100; // end of the slab

int fi1 = 5000; //
int fi2 = 2500; //

double xi = 0.5;
int No = 200; // defines the output rate

/*** start exe
ution ***/
double w0 = 2*pi*speed/lambda0; // rad/fs
double dt = xi*dx/speed; // in fs


/*** arrays for the fields ***/
double *fields = new double[3*Nx];
double *Hz = fields+0*Nx;
double *Bz =new double[Nx];
double *Bz2 =new double[Nx];
double *Ey = fields+1*Nx;
double *Dy = fields+2*Nx;
double *Dy2=new double[Nx];
double *eps = new double[Nx];
double *eta=new double[Nx];

double wmin = 0.8*w0; // rad/fs
double wmax = 1.2*w0; // rad/fs
int Nw=200;

dcomplex *ftall=new dcomplex[3*Nw];
dcomplex *ft1 = ftall + 0*Nw;
dcomplex *ft2 = ftall + 1*Nw;
dcomplex *ftth1=ftall+ 2*Nw;

int T=0; // total steps


QTimer* timer;
#define n_plot 2

int i1=1;
myCurve *elCurve[1], *magCurve[1], *epsCurve, *fourRCurve, *fourICurve, *fourThCurve, *etaConstCurve[5];
vector<vector<float>> dataE, dataH, dataFourR, dataFourI, dataEps, dataTR, dataR;

QwtPlot* d_plot[n_plot];

void MainWindow::changeDist()
{
    qDebug()<<slider_width->value();
    for(int i=0;i<Nx;i++)
    {
        Ey[i]=0;
        Dy[i]=0;
        Dy2[i]=0;
        Bz[i]=0;
        Bz2[i]=0;
        Hz[i]=0;
//        eps[i]=0;
    }
    create_slab(Nx, eps, eta, Nx-slider_width->value(), si2, eslab);
    create_initial_dist(Nx,Dy,Hz,dx,dt,speed,ix0,tau,w0,1);
        update_Ey(Nx, Ey, Dy,Dy2, eps,eta);

        for(int i=0;i<Nx;i++)
        {
            dataEps[0][i]=dx*(i);
            dataEps[1][i]=abs(eps[i])*1;
        }
        epsCurve->signalDrawing();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    dcomplex c(1,1);
    cout<<abs(c);
    zset_mem(2*Nw, ftall, 0.0+dcomplex(0,1)*0.0);





    for(int i=0;i<Nx;i++)
    {
        Ey[i]=0;
        Dy[i]=0;
        Dy2[i]=0;
        Bz[i]=0;
        Bz2[i]=0;
        Hz[i]=0;
//        eps[i]=0;
    }



    create_slab(Nx, eps, eta, si1, si2, eslab);

    create_initial_dist(Nx,Dy,Hz,dx,dt,speed,ix0,tau,w0,1);
//    save_Dy2(Nx,Dy2,Dy);
    update_Ey(Nx, Ey, Dy,Dy2, eps,eta);
    //    create_initial_dist(Nx,Ey,Hz,dx,dt,speed,2250,tau,w0,-1);



    slider_width= new QSlider(this);
    slider_width->setRange(1,500);
    slider_width->setValue(100);
    slider_width->setOrientation(Qt::Horizontal);
//    changeDist();
    connect(slider_width,SIGNAL(sliderReleased()),this,SLOT(changeDist()));

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

    dataR.resize(2);


    dataFourR.resize(2);
    dataFourR[0].resize(Nw,0);
    dataFourR[1].resize(Nw,0);
    for(int i=0;i<Nw;i++)
    {
        dataFourR[0][i]=wmin+i*(wmax-wmin)/Nw;
        dataFourR[1][i]=0;
    }



    dataFourI.resize(2);
    dataFourI[0].resize(Nw,0);
    dataFourI[1].resize(Nw,0);
    for(int i=0;i<Nw;i++)
    {
        dataFourI[0][i]=wmin+i*(wmax-wmin)/Nw;
        dataFourI[1][i]=0;
    }


    dataTR.resize(2);
    dataTR[0].resize(Nw,0);
    dataTR[1].resize(Nw,0);

    double epsImK=4*pi*2*w0;
    for(int i=0;i<Nw;i++)
    {
        dcomplex dc(1,1);
//        dc=2.*dc;


        dataTR[0][i]=wmin+i*(wmax-wmin)/Nw;
        dataTR[1][i]=abs((sqrt(eslab-(epsImK/dataTR[0][i])*dcomplex(0,1))-1.)/
                (sqrt(eslab-(epsImK/dataTR[0][i])*dcomplex(0,1))+1.));
//        dataTR[1][i]=1;
//        sqrt(dcomplex(0,1));
//        sqrt((double)eslab-dcomplex(0,1)*(epsImK/dataTR[0][i]))+1;
    }

    dataH.resize(2);
    for(int i=0;i<2;i++)
        dataH[i].resize(Nx,0);
    for(int i=0;i<Nx;i++)
    {
        dataH[0][i]=dx*(i+0.5);
        dataH[1][i]=Hz[i];
    }


    dataEps.resize(2);
    for(int i=0;i<2;i++)
        dataEps[i].resize(Nx,0);
    for(int i=0;i<Nx;i++)
    {
        dataEps[0][i]=dx*(i);
        dataEps[1][i]=abs(eps[i])*1;
    }

    float yBond=1.5;

    d_plot[0] = new QwtPlot(this);
    drawingInit(d_plot[0],QString("ED show"));
    d_plot[0]->setAxisScale(QwtPlot::yLeft,-yBond,yBond);
    d_plot[0]->setAxisScale(QwtPlot::xBottom,0,Nx*dx);
    d_plot[0]->setAxisTitle(QwtPlot::yLeft, "Ey/E, Hz/H");
    d_plot[0]->setAxisTitle(QwtPlot::xBottom, "dist, nm");

    d_plot[1] = new QwtPlot(this);
    drawingInit(d_plot[1],QString("Fourier koefs"));
    d_plot[1]->setAxisScale(QwtPlot::yLeft,0,1);
    d_plot[1]->setAxisScale(QwtPlot::xBottom,0,80);
    d_plot[1]->setAxisTitle(QwtPlot::yLeft, "amp");
    d_plot[1]->setAxisTitle(QwtPlot::xBottom, "width, number of nodes");
    QwtPlotGrid *grid = new QwtPlotGrid(); //

        grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
        grid->attach( d_plot[1] ); // добавить сетку к полю графика

    elCurve[0]=new myCurve( dataE,d_plot[0],"ED",Qt::black,i1);
    magCurve[0]=new myCurve(dataH,d_plot[0],"ED",Qt::green,i1);
    epsCurve=new myCurve(dataEps,d_plot[0],"ED",Qt::yellow,i1);
    fourRCurve=new myCurve(dataFourR,d_plot[1],"ED",Qt::black,i1);
    fourICurve=new myCurve(dataFourI,d_plot[1],"ED",Qt::black,i1);
     fourThCurve=new myCurve(dataTR,d_plot[1],"ED",Qt::green,i1);
     etaConstCurve[0]=new myCurve(dataR,d_plot[1],"ED",QColor(0,0,0,0),Qt::black,i1);

//    elCurve[1]=new myCurve(Nx_part, dataFourR,d_plot[1],"ED",Qt::black,Qt::black,i1);

    LE=new QLineEdit("10");
    QGridLayout* MW=new QGridLayout();
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(MW);

    MW->addWidget(d_plot[0],0,0,1,2);
    MW->addWidget(d_plot[1],1,0,1,2);
    MW->addWidget(slider_width,2,0);
    MW->addWidget(LE,2,1);

    //    MW->addWidget(d_plot,2,1,2,4);
    setCentralWidget(centralWidget);
    this->resize(QSize(600,450));

    elCurve[0]->signalDrawing();
    magCurve[0]->signalDrawing();
    epsCurve->signalDrawing();

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
//    d_plot->set





}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->text()=="s")
    {
        //    qDebug()<<"hello";
        fourb1=0;
        fourb2=0;
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
    else if(event->text()=="i")
        fourb1=1;

    else if(event->text()=="r")
        fourb2=1;
    else if(event->text()=="c")
    {

    }
    else if(event->text()=="a")
    {
        dataR[0].push_back(slider_width->value());
        dataR[1].push_back(getMax(Ey,Nx));
    }

}

void MainWindow::loop()
{


    static int time_i=0;
    for(int j=0;j<LE->text().toInt();j++)
    {
        time_i+=1;

        save_mas(Nx, Bz2, Bz);
        update_Bz(Nx, Bz, Ey, xi);
        update_Hz(Nx, Hz, Bz, Bz2, eps, eta);
        save_mas(Nx, Dy2,Dy);
        update_Dy(Nx, Dy, Hz, xi);
        update_Ey(Nx, Ey, Dy, Dy2, eps, eta);

        double time=dt*(time_i+1); // for Ey
//        rfourier2(wmin, wmax, Nw, ft1, ft2, Ey[ix0+700], Ey[ix0], dt, time, fourb1, fourb2 );
//        cout<<abs(ft1[40]);

        for(int i=0;i<Nx;i++)
        {
            dataE[1][i]=Ey[i];
            dataH[1][i]=Hz[i];
        }

//        for(int i=0;i<Nw;i++)
//        {
//            dataFourR[1][i]=abs(ft2[i]/(0.0001+ft1[i]));

//        dataFourI[1][i]=abs(ft1[i]);
////        dataFourR[1][i]=abs(ft2[i]);
//        }
    }

    elCurve[0]->signalDrawing();
//    elCurve[1]->signalDrawing();
    magCurve[0]->signalDrawing();
    etaConstCurve[0]->signalDrawing();


//    fourRCurve->signalDrawing();
//    fourICurve->signalDrawing();
//    fourThCurve->signalDrawing();

    QwtText* qwtt=new QwtText(QString("time=")+QString::number(time_i*dt)+QString(" fs"));
    qwtt->setFont(QFont("Helvetica", 11,QFont::Normal));

    //    d_plot->setAxisScale(1,-500,500,200);
    d_plot[0]->setTitle( *qwtt ); // заголовок
}

double getMax(double* x, int Nx)
{
    double max=0;
for(int i=0;i<Nx;i++)
    if(max<x[i]) max=x[i];
return max;
}

MainWindow::~MainWindow()
{

}
