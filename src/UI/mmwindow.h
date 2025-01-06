#ifndef MMWINDOW_H
#define MMWINDOW_H

#include <QMainWindow>


#include <QWidget>


#include <QTimer>
#include <osgDB/ReadFile>
#include <osg/Group>
#include <osg/Node>
#include <osg/Camera>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
 
#include <osgEarth/MapNode>
#include <osgEarth/SpatialReference>
 
//#include <osgEarth/GeoTransForm>
#include <osgEarth/GeoCommon>
#include <osgEarth/SpatialReference>
#include <osgEarth/EarthManipulator>
#include <osgEarth/Ephemeris>
#include <osgEarth/Sky>
 
#include <osgUtil/Tessellator>
#include <osgEarth/GLUtils>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/TexGen>
 
#include <QApplication>
#include <QDir>
#include <QString>


namespace Ui {
class MMWindow;
}

class MMWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MMWindow(QWidget *parent = nullptr);
    ~MMWindow();

private:
    Ui::MMWindow *ui;

private:
    QTimer* _timer;		// 计时器，每5ms触发一次事件
    osgViewer::Viewer* viewer;
    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osg::Camera> camera;
    osg::ref_ptr<osg::Node> earthNode;
    osg::ref_ptr<osgEarth::MapNode> mapNode;
    osg::ref_ptr <osg::MatrixTransform> earthForm;
    osg::ref_ptr<osgEarth::EarthManipulator> em;
    tm* t_tm;
    osgEarth::SkyNode* m_pSkyNode;
    time_t now_time;
 
private:
    void InitOSG();// 初始化设置osg
    void InitUI();//界面初始化
    void InitTimer();//屏幕刷新初始化
    void InitOsgearth();//初始化osgearth
    void InitSky();//天空初始化
private slots:
    // 定时更新帧的槽函数
    void updateFrame();

};

#endif // MMWINDOW_H
