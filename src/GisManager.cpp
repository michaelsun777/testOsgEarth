#include "GisManager.h"


GisManager::GisManager(/* args */)
{
}

GisManager::~GisManager()
{

}



bool GisManager::Init()
{
    GisContainer gc;
    gc.Init();
    gc.Start();
    
    return true;
}