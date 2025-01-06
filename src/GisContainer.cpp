#include "GisContainer.h"


GisContainer::GisContainer() {
}

GisContainer::~GisContainer() {
}


bool GisContainer::Init()
{
    osgEarth::initialize();
    m_pMap = new osgEarth::Map();
    m_pViewer = new osgViewer::Viewer();
    m_pViewer->setUpViewInWindow(0, 0, 800, 600);//根据给定的窗口参数来创建一个图形设备 参数：窗口左上角坐标x，y，宽度width，高度height，以及屏幕数screenNum
    /*
    //GeoTiff Layer
    string worldTifFilename = "D:/codes/osgEarth-Projects/osgearth3.4/data/world.tif";
    osg::ref_ptr<GDALImageLayer> gdalLayer = new GDALImageLayer();
    gdalLayer->setURL(osgEarth::URI(worldTifFilename));

    */

    /*
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = 0;
    traits->y = 0;
    traits->width = 800;
    traits->height = 600;
    traits->windowDecoration = true;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;
    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
    if (!gc.get()) {
        std::cerr << "Unable to create graphics context." << std::endl;
        return 1;
    }
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(gc.get());
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
    camera->setDrawBuffer(buffer);
    camera->setReadBuffer(buffer);
    // add this slave camera to the viewer, with a shift left of the projection matrix
    m_pViewer->addSlave(camera.get());
    */
       
    osgEarth::XYZImageLayer* sjwt = GisContainer::CreateSJZWeiTuLayer();
    osgEarth::XYZImageLayer* sjwtbi = GisContainer::CreateSJZWeiTuLayerLable();
    m_pMap->addLayer(sjwt);
    m_pMap->addLayer(sjwtbi);
    m_mapNode = new osgEarth::MapNode(m_pMap);
    m_pViewer->setRealizeOperation( new GL3RealizeOperation() );
    
    //m_pViewer->setCameraManipulator( new EarthManipulator() );
    EarthManipulator* mp = new EarthManipulator;
    /*
    Viewpoint vp("demo",
    116.25,  // 焦点经度 ，单位角度。
    39.54,  // 焦点维度 ，单位角度。
    0,   // 海拔高度 单位米。
    0,   // Heading 相机指向焦点角度，单位角度。
    -90,   // pitch 相机相对焦点俯仰角度，单位角度。
    1E7 // 距离焦点距离，这里表示距离地表经纬度点的距离，单位米。
    );

    mp->setViewpoint(vp
    , 5  // 相机移动时间，单位秒。
    );*/

    m_pViewer->setCameraManipulator(mp);


    m_pViewer->getCamera()->setSmallFeatureCullingPixelSize(-1.0f);


   
    // osgEarth::GeoTransform* geoTransform = new GeoTransform;//构建一个地球坐标系位置节点
    // geoTransform->setPosition(GeoPoint(SpatialReference::get("wgs84"), -77.013, 38.91));
   
    
    // m_mapNode->addChild(geoTransform);
    //viewer.setSceneData(rootMapNode);
    




    
    m_pViewer->setSceneData(m_mapNode);
    // Viewpoint vp("Washington", -77.013, 38.91, 0, 0, -90, 1000);
    // mp->setViewpoint(vp, 3);

    Viewpoint vp("demo",
    116.25,  // 焦点经度 ，单位角度。
    39.54,  // 焦点维度 ，单位角度。
    0,   // 海拔高度 单位米。
    0,   // Heading 相机指向焦点角度，单位角度。
    -90,   // pitch 相机相对焦点俯仰角度，单位角度。
    1E7 // 距离焦点距离，这里表示距离地表经纬度点的距离，单位米。
    );

    mp->setViewpoint(vp
    , 5  // 相机移动时间，单位秒。
    );

    
    


    return true;
}

bool GisContainer::Run()
{
    //int r = m_pViewer->run();
    // while (!m_pViewer->done())
    // {
    //     m_pViewer->frame();
    // }
    

    return true;
}

bool GisContainer::Start()
{
    //std::thread thread(std::bind(&GisContainer::Run, this));
    //thread.detach();
    //m_pViewer->realize();
    m_pViewerFrameThread = new ViewerFrameThread(m_pViewer, true);
    m_pViewerFrameThread->start();
    
    return true;
}



/// <summary>
/// 
/// </summary>
/// <param name="key"></param>
/// <param name="isVector">是否是矢量图层</param>
/// <returns></returns>
osgEarth::XYZImageLayer* GisContainer::CreateSJZWeiTuLayer()
{
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
 
	//std::string lySourceName = isVector ? "img_w" : "cia_w";
 
	std::string lyName = "水经微卫图";//isVector ? "天地图卫图" : "天地图卫图注记";
 
	// osgEarth::URI imgUri("http://t[01234567].tianditu.gov.cn/" + lySourceName + "/wmts?tk=" + key + "&l={z}&x={x}&y={y}",
	// 	context);
    osgEarth::URI imgUri("http://10.200.1.27:1180/WeServer/wmts/1.0.0/layer_mct/default/mct/{z}/{y}/{x}.jpg",context);//10.200.1.27:1180
 
    
    XYZImageLayer* osm = new XYZImageLayer();
    //osgEarth::URI uri("http://t0.tianditu.gov.cn/img_w/wmts?SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=img&STYLE=default&TILEMATRIXSET=w&FORMAT=tiles&TILEMATRIX={z}&TILEROW={y}&TILECOL={x}&tk=yourkey");
    osm->setURL(imgUri);
    osm->setProfile(Profile::create("spherical-mercator"));
    //osm->setOpacity(0.5f); 
    osm->setOpacity(1);
	osm->setName(lyName); 
	//osm->setProfile(osgEarth::Profile::create("spherical-mercator"));
    return osm;
    
}


/// <summary>
/// 
/// </summary>
/// <param name="key"></param>
/// <param name="isVector">是否是矢量图层</param>
/// <returns></returns>
osgEarth::XYZImageLayer* GisContainer::CreateSJZWeiTuLayerLable()
{
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
 
	//std::string lySourceName = isVector ? "img_w" : "cia_w";
 
	std::string lyName = "水经微卫图标记";//isVector ? "天地图卫图" : "天地图卫图注记";
 
	// osgEarth::URI imgUri("http://t[01234567].tianditu.gov.cn/" + lySourceName + "/wmts?tk=" + key + "&l={z}&x={x}&y={y}",
	// 	context);
    osgEarth::URI imgUri("http://10.200.1.27:1180/WeServer/wmts/1.0.0/label_mct/default/mct/{z}/{y}/{x}.png",context);//10.200.1.27:1180
 
    
    XYZImageLayer* osm = new XYZImageLayer();
    //osgEarth::URI uri("http://t0.tianditu.gov.cn/img_w/wmts?SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=img&STYLE=default&TILEMATRIXSET=w&FORMAT=tiles&TILEMATRIX={z}&TILEROW={y}&TILECOL={x}&tk=yourkey");
    osm->setURL(imgUri);
    osm->setProfile(Profile::create("spherical-mercator"));
    //osm->setOpacity(0.5f); 
    osm->setOpacity(1);
	osm->setName(lyName); 
	//osm->setProfile(osgEarth::Profile::create("spherical-mercator"));
    return osm;
    
}



osgEarth::XYZImageLayer* GisContainer::CreateGaoDeTileLayer()
{
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
 
	//std::string lySourceName = isVector ? "img_w" : "cia_w";
 
	std::string lyName = "水经微卫图";//isVector ? "天地图卫图" : "天地图卫图注记";
 
	// osgEarth::URI imgUri("http://t[01234567].tianditu.gov.cn/" + lySourceName + "/wmts?tk=" + key + "&l={z}&x={x}&y={y}",
	// 	context);
    osgEarth::URI imgUri("http://10.200.1.27:1180/WeServer/wmts/1.0.0/layer_mct/default/mct/{z}/{y}/{x}.jpg",context);//10.200.1.27:1180
 
    
    XYZImageLayer* osm = new XYZImageLayer();
    //osgEarth::URI uri("http://t0.tianditu.gov.cn/img_w/wmts?SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=img&STYLE=default&TILEMATRIXSET=w&FORMAT=tiles&TILEMATRIX={z}&TILEROW={y}&TILECOL={x}&tk=yourkey");
    osm->setURL(imgUri);
    osm->setProfile(Profile::create("spherical-mercator"));
    //osm->setOpacity(0.5f); 
    osm->setOpacity(1);
	osm->setName(lyName); 
	//osm->setProfile(osgEarth::Profile::create("spherical-mercator"));
    return osm;
    
}
