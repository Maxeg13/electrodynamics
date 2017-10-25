#include "mainwindow.h"
#include "vector"
#include "stdio.h"
#include "QGridLayout"
using namespace std;

#define n_plot 2
int bufShowSize=1000;
int i1=1;
myCurve *elCurve[n_plot];
vector<vector<float>> dataV;

QwtPlot* d_plot[n_plot];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    dataV.resize(2);
    for(int i=0;i<2;i++)
        dataV[i].resize(bufShowSize,0);

    for(int i=0;i<bufShowSize;i++)
        dataV[0][i]=sin(i*0.1);

    d_plot[0] = new QwtPlot(this);
    drawingInit(d_plot[0],QString("ED show"));
    d_plot[0]->setAxisScale(QwtPlot::yLeft,-400,400);
    d_plot[0]->setAxisScale(QwtPlot::xBottom,0,bufShowSize);
    elCurve[0]=new myCurve(bufShowSize, dataV[0],d_plot[0],"ED",Qt::black,Qt::black,i1);
    d_plot[0]->setAxisScale(QwtPlot::xBottom ,0,bufShowSize);
    d_plot[0]->setAxisScale(QwtPlot::yLeft,-1.5,1.5);

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

    d_plot->setAxisScale(1,-500,500,200);
    d_plot->setTitle( *qwtt ); // заголовок
    d_plot->setCanvasBackground( Qt::white ); // цвет фона


    // Включить сетку
    // #include <qwt_plot_grid.h>
    //    QwtPlotGrid *grid = new QwtPlotGrid(); //

    //    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    //    grid->attach( d_plot ); // добавить сетку к полю графика


//    d_plot->setMinimumSize(150,140);

}

MainWindow::~MainWindow()
{

}
