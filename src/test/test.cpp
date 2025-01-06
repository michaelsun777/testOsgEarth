
#include "test.h"

test::test(/* args */)
{
}

test::~test()
{
}


/// <summary>
/// 创建天地图图层
/// </summary>
/// <param name="key">天地图key</param>
/// <param name="isVector">是否是矢量图层</param>
/// <returns>天地图瓦片图层</returns>
osgEarth::XYZImageLayer* test::CreateTdtTileLayer(std::string key, bool isVector)
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
 
	std::string lySourceName = isVector ? "vec_w" : "img_w";
 
	std::string lyName = isVector ? "天地图矢量" : "天地图影像";

	key = "037c38baa313764cf7e3f792f211a871";
 
	osgEarth::URI imgUri("http://t[01234567].tianditu.com/DataServer?T="+ lySourceName +"&tk="+ key +"&l={z}&x={x}&y={y}",
		context);
 
	osgEarth::XYZImageLayer* imgLy = new osgEarth::XYZImageLayer();
 
	imgLy->setURL(imgUri);
 
	imgLy->setProfile(osgEarth::Profile::create("spherical-mercator"));
 
	imgLy->setName(lyName);
 
	imgLy->setOpacity(1);
 
	return imgLy; 
}
 

/// <summary>
/// 创建天地图注记瓦片图层
/// </summary>
/// <param name="key">天地图key</param>
/// <param name="isVector">是否是矢量图层</param>
/// <returns></returns>
osgEarth::XYZImageLayer* test::CreateTdtRemarkTileLayer(std::string key, bool isVector)
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
 
	std::string lySourceName = isVector ? "cva_w" : "cia_w";
 
	std::string lyName = isVector ? "天地图矢量注记" : "天地图影像注记";
 
	osgEarth::URI imgUri("http://t[01234567].tianditu.com/DataServer?T=" + lySourceName + "&tk=" + key + "&l={z}&x={x}&y={y}",
		context);
 
	osgEarth::XYZImageLayer* imgLy = new osgEarth::XYZImageLayer();
 
	imgLy->setURL(imgUri);
 
	imgLy->setName(lyName);
 
	imgLy->setOpacity(1);
 
	imgLy->setProfile(osgEarth::Profile::create("spherical-mercator"));
 
	return imgLy; 
}


/// <summary>
/// 
/// </summary>
/// <param name="key"></param>
/// <param name="isVector">是否是矢量图层</param>
/// <returns></returns>
osgEarth::XYZImageLayer* test::CreateTdtWeiTuLayer(std::string key, bool isVector)
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
 
	std::string lySourceName = isVector ? "img_w" : "cia_w";
 
	std::string lyName = isVector ? "天地图卫图" : "天地图卫图注记";
 
	// osgEarth::URI imgUri("http://t[01234567].tianditu.gov.cn/" + lySourceName + "/wmts?tk=" + key + "&l={z}&x={x}&y={y}",
	// 	context);
    osgEarth::URI imgUri("http://t[01234567].tianditu.gov.cn/" + lySourceName + 
    "/wmts?SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=img&STYLE=default&TILEMATRIXSET=w&FORMAT=tiles&TILEMATRIX={z}&TILEROW={y}&TILECOL={x}&tk="
    + key,context);
 
    
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
osgEarth::XYZImageLayer* test::CreateSJZWeiTuLayer(std::string key, bool isVector)
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
 
	std::string lySourceName = isVector ? "img_w" : "cia_w";
 
	std::string lyName = isVector ? "天地图卫图" : "天地图卫图注记";
 
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
osgEarth::XYZImageLayer* test::CreateSJZWeiTuLayerLable(std::string key, bool isVector)
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
 
	std::string lySourceName = isVector ? "img_w" : "cia_w";
 
	std::string lyName = isVector ? "天地图卫图" : "天地图卫图注记";
 
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

