#pragma once



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






class test
{
private:
    /* data */
public:
    test(/* args */);
    ~test();

    osgEarth::XYZImageLayer* CreateTdtTileLayer(std::string key, bool isVector);
    osgEarth::XYZImageLayer* CreateTdtRemarkTileLayer(std::string key, bool isVector);
    osgEarth::XYZImageLayer* CreateTdtWeiTuLayer(std::string key, bool isVector);

    osgEarth::XYZImageLayer* CreateSJZWeiTuLayer(std::string key, bool isVector);
    osgEarth::XYZImageLayer* CreateSJZWeiTuLayerLable(std::string key, bool isVector);
};





    
    // osgEarth::XYZImageLayer * wtmsWt = CreateTdtWeiTuLayer("037c38baa313764cf7e3f792f211a871", true);    
    // map->addLayer(wtmsWt);

    // osgEarth::XYZImageLayer * wtmsWtBj = CreateTdtWeiTuLayer("037c38baa313764cf7e3f792f211a871", false);
    
    // map->addLayer(wtmsWtBj);


    // osgEarth::XYZImageLayer* osmTdt = CreateTdtTileLayer("037c38baa313764cf7e3f792f211a871", true);
    // map->addLayer(osmTdt);

    // osgEarth::XYZImageLayer* osmTdtRemark = CreateTdtRemarkTileLayer("037c38baa313764cf7e3f792f211a871", true);
    // map->addLayer(osmTdtRemark);
    
    //水经注图 wmts
    // osgEarth::XYZImageLayer* osmsjzRemark = CreateSJZWeiTuLayer("037c38baa313764cf7e3f792f211a871", true);
    // map->addLayer(osmsjzRemark);

    // osgEarth::XYZImageLayer* osmsjzRemarkLable = CreateSJZWeiTuLayerLable("037c38baa313764cf7e3f792f211a871", true);
    // map->addLayer(osmsjzRemarkLable);