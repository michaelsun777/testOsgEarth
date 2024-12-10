/* -*-c++-*- */
/* osgEarth - Geospatial SDK for OpenSceneGraph
* Copyright 2020 Pelican Mapping
* http://osgearth.org
*
* osgEarth is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

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


#include <osg/PositionAttitudeTransform>


#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

//#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarthDrivers/cache_filesystem/FileSystemCache>
//#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include <string>
#include <iostream>





using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Contrib;
using namespace std;

int usage(int argc, char** argv)
{
    OE_NOTICE
        << "\n" << argv[0]
        << "\n    [--out outFile] : write map node to outFile before exit"
        << std::endl;

    return 0;
}
// Demonstrates how to subclass ImageLayer to directly create textures
// for use in a layer.
class MyTextureLayer : public ImageLayer
{
public:
    std::string _path;
    osg::ref_ptr<osg::Texture2D> _tex;

    META_Layer(osgEarth, MyTextureLayer, Options, ImageLayer, mytexturelayer);

    void setPath(const char* path)
    {
        _path = path;
    }

    Status openImplementation()
    {
        osg::ref_ptr<osg::Image> image = osgDB::readRefImageFile(_path);
        if (image.valid())
            _tex = new osg::Texture2D(image.get());
        else
            return Status(Status::ConfigurationError, "no path");

        // Establish a geospatial profile for the layer:
        setProfile(Profile::create(Profile::GLOBAL_GEODETIC));

        // Tell the layer to call createTexture:
        setUseCreateTexture();

        // Restrict the data extents of this layer to LOD 0 (in this case)
        addDataExtent(DataExtent(getProfile()->getExtent(), 0, 0));

        return Status::OK();
    }

    TextureWindow
        createTexture(const TileKey& key, ProgressCallback* progress) const
    {
        // Set the texture matrix corresponding to the tile key:
        osg::Matrixf textureMatrix;
        key.getExtent().createScaleBias(getProfile()->getExtent(), textureMatrix);
        return TextureWindow(_tex.get(), textureMatrix);
    }
};

void checkErrors(const Layer* layer)
{
    if (layer->getStatus().isError())
    {
        OE_WARN << "Layer " << layer->getName() << " : " << layer->getStatus().message() << std::endl;
    }
}

/**
 * How to create a simple osgEarth map and display it.
 */
int main(int argc, char** argv)
{
    osgEarth::initialize();

    //osg::ArgumentParser arguments(&argc,argv);
    //if (arguments.read("--help"))
    //    return usage(argc, argv);

    // create the empty map.
    Map* map = new Map();
    osgViewer::Viewer viewer;
    viewer.setUpViewInWindow(0,100,800,600);
    viewer.setReleaseContextAtEndOfFrameHint(false);

    // set camera manipulator
    viewer.setCameraManipulator(new EarthManipulator);

    // Map is datamodel for collection of layers.
    osg::ref_ptr<osgEarth::Map> rootMap = new osgEarth::Map;
    // GeoTiff Layer
    string worldTifFilename = "/home/amplesky/osg/testOsgearth/data/world.tif";

    osg::ref_ptr<GDALImageLayer> gdalLayer = new GDALImageLayer();

    gdalLayer->setURL(osgEarth::URI(worldTifFilename));

    // TMS   
    string source = "http://127.0.0.1:9000/bigemap.1rx7l48u/tms/tilemapresource.xml?access_token=pk.eyJ1IjoiY3VzX2RjMXQ4NWVnIiwiYSI6IjA2YzFtYzB6c2pzcXV5OGk1eGhpemxsc2kifQ.Hk9BJPFtpErxmlWuyd9kUw";

    osg::ref_ptr<TMSImageLayer> someLayer = new TMSImageLayer();
    someLayer->setURL(osgEarth::URI(source));

    // MapNode is the render or visualization of Map.
    osg::ref_ptr<osgEarth::MapNode> rootMapNode = new osgEarth::MapNode(rootMap.get());

    rootMap->addLayer(gdalLayer);
    rootMap->addLayer(someLayer);
    viewer.setSceneData(rootMapNode);

    return Metrics::run(viewer);

    //map->addImageLayer(new osgEarth::ImageLayerOptions("arcgis_layer", arcgisServerOptions));
    
 
    // 设置初始视图，这部分根据需要进行配置
    // map->setInitialRange(
    //     osgEarth::Bounds(-120, 30, -100, 40), // 边界框
    //     16                                   // 缩放级别
    // );
 

    // add a simple imagery layer using the GDAL driver:
    // GDALImageLayer* imagery = new GDALImageLayer();
    // imagery->setURL("./data/world.tif");
    // map->addLayer(imagery);

    // add a TMS (Tile Map Service) elevation layer:
    //TMSElevationLayer* elevation = new TMSElevationLayer();
    //elevation->setURL("http://readymap.org/readymap/tiles/1.0.0/116/");
    //elevation->setURL("http://127.0.0.1:9000/bigemap.1rx7l48u/tms/tilemapresource.xml?access_token=pk.eyJ1IjoiY3VzXzhyYWRwY2E2IiwiYSI6IjA2YzFtYzB6c2pzcXV5OGk1eGhpemxsc2kifQ.8-5AB1uHH4VGhmDehuDJag");
    //map->addLayer( elevation );

    // add a semi-transparent XYZ layer:
    //XYZImageLayer* osm = new XYZImageLayer();
    //osm->setURL("http://[abc].tile.openstreetmap.org/{z}/{x}/{y}.png");
    //osm->setURL("http://127.0.0.1:9000/bigemap.tian-map/tms/{z}/{x}/{y}.png?access_token=pk.eyJ1IjoiY3VzXzhyYWRwY2E2IiwiYSI6IjA2YzFtYzB6c2pzcXV5OGk1eGhpemxsc2kifQ.8-5AB1uHH4VGhmDehuDJag");
    //osm->setProfile(Profile::create(Profile::SPHERICAL_MERCATOR));
    //osm->setOpacity(0.5f);
    //map->addLayer(osm);

    // a custom layer that displays a user texture:
    // MyTextureLayer* texLayer = new MyTextureLayer();
    // texLayer->setPath("../data/grid2.png");
    // texLayer->setOpacity(0.5f);
    // map->addLayer(texLayer);

    // add a WMS radar layer with transparency, and disable caching since
    // this layer updates on the server periodically.
    // WMSImageLayer* wms = new WMSImageLayer();
    // wms->setURL("http://mesonet.agron.iastate.edu/cgi-bin/wms/nexrad/n0r.cgi");
    // wms->setFormat("png");
    // wms->setLayers("nexrad-n0r");
    // wms->setSRS("EPSG:4326");
    // wms->setTransparent(true);
    // wms->options().cachePolicy() = CachePolicy::NO_CACHE;
    // map->addLayer(wms);

    // Add a composite image layer that combines two other sources:
    // GDALImageLayer* comp1 = new GDALImageLayer();
    // comp1->setURL("../data/boston-inset-wgs84.tif");
    // GDALImageLayer* comp2 = new GDALImageLayer();
    // comp2->setURL("../data/nyc-inset-wgs84.tif");
    // CompositeImageLayer* compImage = new CompositeImageLayer();
    // compImage->addLayer(comp1);
    // compImage->addLayer(comp2);
    // map->addLayer(compImage);

    // Add a composite elevation layer tha tcombines two other sources:
    // GDALElevationLayer* elev1 = new GDALElevationLayer();
    // elev1->setURL("../data/terrain/mt_fuji_90m.tif");
    // GDALElevationLayer* elev2 = new GDALElevationLayer();
    // elev2->setURL("../data/terrain/mt_everest_90m.tif");
    // CompositeElevationLayer* compElev = new CompositeElevationLayer();
    // compElev->addLayer(elev1);
    // compElev->addLayer(elev2);
    // map->addLayer(compElev);

    // Terrain Constraint Layer:
    // Polygon* maskGeom = new Polygon();
    // maskGeom->push_back(osg::Vec3d(-111.0466, 42.0015, 0));
    // maskGeom->push_back(osg::Vec3d(-111.0467, 40.9979, 0));
    // maskGeom->push_back(osg::Vec3d(-109.0501, 41.0007, 0));
    // maskGeom->push_back(osg::Vec3d(-109.0452, 36.9991, 0));
    // maskGeom->push_back(osg::Vec3d(-114.0506, 37.0004, 0));
    // maskGeom->push_back(osg::Vec3d(-114.0417, 41.9937, 0));

    // OGRFeatureSource* maskFeatures = new OGRFeatureSource();
    // maskFeatures->setGeometry(maskGeom);
    // maskFeatures->setProfile(Profile::create(Profile::GLOBAL_GEODETIC));

    // if (maskFeatures->open().isOK())
    // {
    //     TerrainConstraintLayer* maskLayer = new TerrainConstraintLayer();
    //     maskLayer->setFeatureSource(maskFeatures);
    //     map->addLayer(maskLayer);
    // }

    // put a model on the map atop Pike's Peak, Colorado, USA
    // auto modelLayer = new ModelLayer();
    // modelLayer->setURL("../data/red_flag.osg.2000.scale");
    // modelLayer->setLocation(GeoPoint(SpatialReference::get("wgs84"), -105.042292, 38.840829));
    // map->addLayer(modelLayer);

    // make the map scene graph:
    //MapNode* node = new MapNode( map );

    // initialize a viewer:
    
    //osgViewer::Viewer viewer();
    // viewer.setRealizeOperation( new GL3RealizeOperation() );
    // viewer.setCameraManipulator( new EarthManipulator() );
    // viewer.getCamera()->setSmallFeatureCullingPixelSize(-1.0f);
    // viewer.setSceneData( node );

    // add some stock OSG handlers:
    //MapNodeHelper().configureView(&viewer);

    //int r = viewer.run();

    // std::string outFile;
    // if (arguments.read("--out", outFile))
    //     osgDB::writeNodeFile(*node, outFile);

    //return r;
}