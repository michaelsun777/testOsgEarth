#include "windowmain.h"
#include "ui_windowmain.h"

#include <osgEarth/GLUtils>

#include <osgEarth/TMS>
#include <osgEarth/WMS>
#include <osgEarth/GDAL>
#include <osgEarth/XYZ>
#include <osgEarth/Composite>

#include <osgEarth/ExampleResources>

WindowMain::WindowMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowMain)
{
    ui->setupUi(this);

    //resize(1200, 800);
    pOsgW = new osgQOpenGLWidget(this);
    //ui->vLayout->addWidget(pOsgW);
    m_vboxLayoutTop = new QVBoxLayout(this);
    m_btnTest = new QPushButton("测试按钮",this);
    m_btnTest->resize(100,50);
    //m_btnTest->sizeHint().setHeight(50);
    //m_btnTest->sizeHint().setWidth(100);
    m_vboxLayoutTop->addWidget(m_btnTest);


    m_vboxLayout = new QVBoxLayout(this);
    m_vboxLayout->addWidget(pOsgW);


    
    //mRoot = new osg::Group;
    //mCamera = new osgEarth::Util::EarthManipulator;
    //mEarth = osgDB::readNodeFile("simple.earth");
    //mRoot->addChild(mEarth.get());
    osgEarth::initialize();
    connect(pOsgW, SIGNAL(initialized()), this, SLOT(initOsg()));

}

WindowMain::~WindowMain()
{
    delete ui;
}


void WindowMain::initOsg()
{
    
    mViewer = pOsgW->getOsgViewer();
    //mViewer->setCameraManipulator(new osgGA::TrackballManipulator());
    //mViewer->setCameraManipulator(mCamera);
    //mViewer->setSceneData(mRoot.get());
    // earth = osgDB::readNodeFile("simple.earth");
    // if (!earth.valid())
    //     qDebug() << "File not found";
    // root->addChild(earth.get());


    Map* map = new Map();

    osgEarth::URIContext context;
	context.addHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/"
		"*;q=0.8,application/signed-exchange;v=b3;q=0.9");
	context.addHeader("Accept-Encoding", "gzip, deflate");
	context.addHeader("Accept-Language", "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6");
	context.addHeader("Cache-Control", "max-age=0");
	context.addHeader("Connection", "keep-alive");
	context.addHeader("Upgrade-Insecure-Requests", "1");
	context.addHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) "
		"Chrome/99.0.4844.51 Safari/537.36 Edg/99.0.1150.39");
 
	std::string lySourceName =  "vec_w";
 
	std::string lyName = "天地图矢量";

	std::string key = "037c38baa313764cf7e3f792f211a871";
 
	osgEarth::URI imgUri("http://t[01234567].tianditu.com/DataServer?T="+ lySourceName +"&tk="+ key +"&l={z}&x={x}&y={y}",
		context);
 
	osgEarth::XYZImageLayer* imgLy = new osgEarth::XYZImageLayer();
 
	imgLy->setURL(imgUri);
 
	imgLy->setProfile(osgEarth::Profile::create("spherical-mercator"));
 
	imgLy->setName(lyName);
 
	imgLy->setOpacity(1);
 
    
    map->addLayer(imgLy);

    MapNode* node = new MapNode( map );
// #ifndef OSG_GL3_AVAILABLE
//     // If your OSG is build with a GL2 profile, install our custom realize op
//     // to get all the shaders working:
//     mViewer->setRealizeOperation(new osgEarth::GL3RealizeOperation());
// #endif

    mViewer->setRealizeOperation( new GL3RealizeOperation() );
    mViewer->setCameraManipulator( new EarthManipulator() );
    mViewer->getCamera()->setSmallFeatureCullingPixelSize(-1.0f);
    mViewer->setSceneData( node );
    MapNodeHelper().configureView(mViewer);    
    //InitTimer();
    //update();
    //mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    mViewer->realize();


}

void WindowMain::resizeEvent(QResizeEvent *event)
{
    // 获取新的尺寸
    QSize newSize = event->size();
    // 更新标签文本以显示新的尺寸
    //sizeLabel->setText(QString("Current size: %1x%2").arg(newSize.width()).arg(newSize.height()));
    if(pOsgW != nullptr)
    {
        //m_btnTest->move(0, 0);
        //m_btnTest->resize(100, 50);
        //m_btnTest->setGeometry(0, 0, 100, 50);
        pOsgW->move(0, 50);
        pOsgW->resize(newSize.width(), newSize.height()-50);
        //pOsgW->setGeometry(0, 50, newSize.width(), newSize.height()-50);


    }

    // 调用基类的resizeEvent方法，确保事件正常传递（虽然在这个例子中不是必需的）
    QWidget::resizeEvent(event);
}

void WindowMain::updateFrame() 
{
    mViewer->frame();
}

void WindowMain::InitTimer()//屏幕刷新初始化
{
    _timer = new QTimer;
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
    _timer->start(10);
 
}