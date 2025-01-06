#ifndef _GIS_CONTAINTER_H_
#define _GIS_CONTAINTER_H_

#include <QApplication>
#include <osgViewer/Viewer>
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarth/ImageLayer>
#include <osgEarth/ModelLayer>
#include <osgEarth/GeoTransform>
#include <osgEarth/GLUtils>
#include <osgEarth/TileSource>
#include <osgEarth/LineSymbol>

#include <osgEarth/TMS>
#include <osgEarth/WMS>
#include <osgEarth/GDAL>
#include <osgEarth/XYZ>
#include <osgEarth/Composite>

#include <osgEarth/EarthManipulator>
#include <osgEarth/ExampleResources>
#include <osgEarth/AutoScaleCallback>

#include <osgEarth/TerrainConstraintLayer>
#include <osgEarth/OGRFeatureSource>
#include <osgEarth/FeatureImageLayer>

//#include <osgEarth/FeatureSourceLayer>
#include <osgEarth/FeatureModelLayer>

#include <osgEarth/ArcGISServer>
#include <osgEarth/Metrics>


using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Contrib;
using namespace std;


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


class GisContainer {

private:
    osgViewer::Viewer * m_pViewer;
    MapNode* m_mapNode;
    Map* m_pMap;
    ViewerFrameThread * m_pViewerFrameThread;


public:
    osgEarth::XYZImageLayer* CreateSJZWeiTuLayer();
    osgEarth::XYZImageLayer* CreateSJZWeiTuLayerLable();

    osgEarth::XYZImageLayer* CreateGaoDeTileLayer();
   

public:
    GisContainer();
    ~GisContainer();
    bool Init();
    bool Start();
    bool Run();
};





#endif