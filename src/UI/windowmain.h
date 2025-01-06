#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <QMainWindow>
#include <QTimer>
#include <QVBoxLayout>
#include <QPushButton>

#include <osgQOpenGL/osgQOpenGLWidget>
//#include "../../3rd/osgQt/include/osgQOpenGL/osgQOpenGLWidget"
#include <osgEarth/EarthManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/View>

#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/GUIEventHandler>
#include <osgGA/NodeTrackerManipulator>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/KeySwitchMatrixManipulator>

#include <osg/GraphicsContext>
#include <osg/Math>
#include <osg/BlendFunc>
#include <osg/BlendColor>

#include <osgEarth/ElevationQuery>
#include <osgEarth/Config>
#include <osgEarth/GeoTransform>
#include <osgEarth/MapNode>
#include <osgEarth/Terrain>

#include <osgDB/ReadFile>
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/Optimizer>
//#include <osgUtil/IntersectVisitor>
#include <QApplication>
#include <QResizeEvent>

using namespace osgEarth::Util;
using namespace osgEarth;
using namespace osgGA;



namespace Ui {
class WindowMain;
}



class WindowMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowMain(QWidget *parent = nullptr);
    ~WindowMain();
public slots:
    void initOsg();
protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    // 定时更新帧的槽函数
    void updateFrame();
private:
    void InitTimer();//屏幕刷新初始化

private:
    Ui::WindowMain *ui;

    osgQOpenGLWidget *pOsgW;
    osgViewer::Viewer *mViewer;         //场景
    osg::ref_ptr<osg::Group> mRoot;     // 根节点
    osg::ref_ptr<osg::Node> mEarth;					//地球节点
    osg::ref_ptr<osgEarth::Util::EarthManipulator>	mCamera;	//相机操作器
    QTimer* _timer;		// 计时器，每5ms触发一次事件
    QVBoxLayout * m_vboxLayoutTop = nullptr;
    QVBoxLayout * m_vboxLayout = nullptr;
    QPushButton * m_btnTest = nullptr;

};

#endif // WINDOWMAIN_H
