#ifndef __SCENE_MAP_H__
#define __SCENE_MAP_H__

#include "Scene_Base.h"
#include "Map.h"

class Scene_Map : public Scene_Base
{
public:

    // Inherited via Scene_Base
    bool isReady() override;
    void Load(std::string const& path) override;
    void Start() override;
    void Update() override;
    // No longer inherited

private:
    std::string currentMap = "";

    Map map;
};


#endif __SCENE_MAP_H__