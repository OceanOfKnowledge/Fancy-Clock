#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include "mainwindow.h"
#include "preference.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Initialize UI
    ui->setupUi(this);

    //Make Clock Translucent
    setAttribute(Qt::WA_TranslucentBackground);

    //Make Clock Frameless and stay on top of the desktop
    setWindowFlags(Qt::WindowStaysOnTopHint |
                   Qt::FramelessWindowHint | windowFlags());

    //Restore saved settings
    QSettings sts;
    restoreGeometry(sts.value("MainGeometry").toByteArray());
    restoreState(sts.value("MainState").toByteArray());
    setColour();

    //Display context Menu
    connect(this,
            &MainWindow::customContextMenuRequested,
            this,
            &MainWindow::showContextMenu);

    //Create new timer object
    QTimer *timer = new QTimer(this);

    //Connect timer object's timeout signals to mainwindow's updateTime function
    connect(timer,
            &QTimer::timeout,
            this,
            &MainWindow::updateTime);

    //Start timer to emit timeout signals every 1000ms (1s)
    timer->start(1000);

    //Update current time
    updateTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Define updateTime function
void MainWindow::updateTime(){
    //Get current time from QTime class
    QTime currentTime = QTime::currentTime();

    //Convert currentTime to string with hours and minutes
    QString currentTimeText = currentTime.toString("hh:mm");

    //Cause colon to blink: if the second value is even, show space; else show colon
    if(currentTime.second() % 2 == 0){
        currentTimeText[2] = ' ';
    }

    //Display current time text in lcdNumber object
    ui->lcdNumber->display(currentTimeText);
}

/*
** Main Window functions implemented!
*/

//Show menu
void MainWindow::showContextMenu(const QPoint &pos){
    QMenu contextMenu;
    contextMenu.addAction(QString("Preference"),
                          this,
                          SLOT(showPreference()));
    contextMenu.addAction(QString("Exit"),
                          this,
                          SLOT(close()));
    contextMenu.exec(mapToGlobal(pos));
}

//Check if mouse event is right-click; else run default mouseReleaseEvent from QMainWindow class
void MainWindow::mouseReleaseEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton){
        emit customContextMenuRequested(e->pos());
    }else{
        QMainWindow::mouseReleaseEvent(e);
    }
}

//Get mouse position from any mouse event
void MainWindow::mousePressEvent(QMouseEvent *e){
    m_mousePos = e->pos();
}

//Drag the application around
void MainWindow::mouseMoveEvent(QMouseEvent *e){
    this->move(e->globalPos() - m_mousePos);
}

//Custom close event to save settings
void MainWindow::closeEvent(QCloseEvent *e){
    QSettings sts;
    sts.setValue("MainGeometry", saveGeometry());
    sts.setValue("MainState", saveState());
    e->accept();
}

//Set colour
void MainWindow::setColour(){
    QSettings sts;
    int i = sts.value("Colour").toInt();

    QPalette c;

    switch (i){
        case 0://black
            c.setColor(QPalette::Foreground, Qt::black);
            break;
        case 1://White
            c.setColor(QPalette::Foreground, Qt::white);
            break;
        case 2://Green
            c.setColor(QPalette::Foreground, Qt::green);
            break;
        case 3://Red
            c.setColor(QPalette::Foreground, Qt::red);
            break;
    }
    ui->lcdNumber->setPalette(c);
    this->update();
}

//Show Preference
void MainWindow::showPreference(){
    Preference *pre = new Preference(this);
    connect(pre,
            &Preference::accepted,
            this,
            &MainWindow::setColour); //NB: Never call connect function after exec() function
    pre->exec();
}















