#include "mmwindow.h"
#include "ui_mmwindow.h"

MMWindow::MMWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MMWindow)
{
    ui->setupUi(this);
    InitOSG();
    InitOsgearth();
    InitUI();
    InitTimer();
}

MMWindow::~MMWindow()
{
    delete ui;
}

void MMWindow::InitOSG()// 初始化设置osg
{
  
}
void MMWindow::InitOsgearth()
{
    
}
void MMWindow::InitSky()
{
    //获取当前时间 初始化天空
    now_time = time(0);
    t_tm = localtime(&now_time);
    osgEarth::DateTime cur_date_time(now_time);
    osgEarth::Ephemeris* ephemeris = new osgEarth::Ephemeris;
 
    //设置黑夜明暗程度
    osgEarth::Util::SkyOptions skyOptions;
    skyOptions.ambient() = 0.3;
 
    m_pSkyNode = osgEarth::SkyNode::create(skyOptions);
    m_pSkyNode->setName("SkyNode");
    m_pSkyNode->setEphemeris(ephemeris);
    m_pSkyNode->setDateTime(cur_date_time);
    viewer->setLightingMode(osg::View::SKY_LIGHT);
    m_pSkyNode->attach(viewer, 0);
    m_pSkyNode->setLighting(true);
 
    m_pSkyNode->addChild(mapNode);
    root->addChild(m_pSkyNode);
 
}
void MMWindow::InitUI()//界面初始化
{

    
}
void MMWindow::InitTimer()//屏幕刷新初始化
{
    _timer = new QTimer;
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
    _timer->start(10);
 
}
void MMWindow::updateFrame()
{
 
    viewer->frame();
}