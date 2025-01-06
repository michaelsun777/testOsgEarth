
#include <iostream>
#include <QApplication>
//#include "mainwindow.h"
#include "src/UI/windowmain.h"

#include <osgViewer/Viewer>

#include <osgEarth/MapNode>
#include <osgEarth/ImageLayer>
#include <osgEarth/ModelLayer>
#include <osgEarth/GeoTransform>
#include <osgEarth/GLUtils>

#include <osgEarth/TMS>
#include <osgEarth/WMS>
#include <osgEarth/GDAL>
#include <osgEarth/XYZ>
#include <osgEarth/Composite>

#include <osgEarth/ExampleResources>
#include <unistd.h>
#include "src/GisContainer.h"


using namespace std;
/*
class ViewerFrameThread : public OpenThreads::Thread
{
    public:

        ViewerFrameThread(osgViewer::ViewerBase* viewerBase, bool doQApplicationExit):
            _viewerBase(viewerBase),
            _doQApplicationExit(doQApplicationExit) {}

        ~ViewerFrameThread()
        {
            cancel();
            while(isRunning())
            {
                OpenThreads::Thread::YieldCurrentThread();
            }
        }

        int cancel()
        {
            _viewerBase->setDone(true);
            return 0;
        }

        void run()
        {
            int result = _viewerBase->run();

            if (_doQApplicationExit) QApplication::exit(result);
        }

        osg::ref_ptr<osgViewer::ViewerBase> _viewerBase;
        bool _doQApplicationExit;
};
*/



 
int main(int argc, char* argv[])
{
	cout << "Hello CMake." << endl;
    QApplication a(argc, argv);

    // GisContainer gis;
    // gis.Init();
    // gis.Start();

    // while (1)
    // {
    //     sleep(1);
    // }
    



    // MainWindow w;
    // //设置初始窗口大小
    // w.setGeometry(200, 100, 1200, 800);
    // //设置窗口标题名称
    // w.setWindowTitle("osgearth");
    // w.show();

    //osgEarth::initialize();

    WindowMain w;
    //设置初始窗口大小
    w.setGeometry(200, 100, 1200, 800);
    w.setWindowTitle("osgearth");
    w.show();

//     osgEarth::initialize();
//     Map* map = new Map();
//     osgEarth::URIContext context;
// 	context.addHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/"
// 		"*;q=0.8,application/signed-exchange;v=b3;q=0.9");
// 	context.addHeader("Accept-Encoding", "gzip, deflate");
// 	context.addHeader("Accept-Language", "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6");
// 	context.addHeader("Cache-Control", "max-age=0");
// 	context.addHeader("Connection", "keep-alive");
// 	context.addHeader("Upgrade-Insecure-Requests", "1");
// 	context.addHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) "
// 		"Chrome/99.0.4844.51 Safari/537.36 Edg/99.0.1150.39");
 
// 	std::string lySourceName =  "vec_w";
 
// 	std::string lyName = "天地图矢量";

// 	std::string key = "037c38baa313764cf7e3f792f211a871";
 
// 	osgEarth::URI imgUri("http://t[01234567].tianditu.com/DataServer?T="+ lySourceName +"&tk="+ key +"&l={z}&x={x}&y={y}",
// 		context);
 
// 	osgEarth::XYZImageLayer* imgLy = new osgEarth::XYZImageLayer();
 
// 	imgLy->setURL(imgUri);
 
// 	imgLy->setProfile(osgEarth::Profile::create("spherical-mercator"));
 
// 	imgLy->setName(lyName);
 
// 	imgLy->setOpacity(1);
 
    
//     map->addLayer(imgLy);

//     MapNode* node = new MapNode( map );
// // #ifndef OSG_GL3_AVAILABLE
// //     // If your OSG is build with a GL2 profile, install our custom realize op
// //     // to get all the shaders working:
// //     mViewer->setRealizeOperation(new osgEarth::GL3RealizeOperation());
// // #endif

//     osgViewer::Viewer viewer;
//     viewer.setRealizeOperation( new GL3RealizeOperation() );
//     viewer.setCameraManipulator( new EarthManipulator() );
//     viewer.getCamera()->setSmallFeatureCullingPixelSize(-1.0f);
//     viewer.setSceneData( node );

//     // add some stock OSG handlers:
//     MapNodeHelper().configureView(&viewer);

//     //int r = viewer.run();
//     ViewerFrameThread viewerThread(&viewer, true);
//     //viewerThread.startThread();
//     viewerThread.start();

//     while (1)
//     {
//         sleep(1);
//     }

    return a.exec();
}
