#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

#include "Scene_Base.h"
#include "Textures.h"

class Scene_Title : public Scene_Base
{
public:
    bool isReady() override;
    void Load(
        std::string const& path,
        LookUpXMLNodeFromString const& info,
        Window_Factory const& windowFactory
    ) override;
    void Start() override;
    void Update() override;

private:
    std::shared_ptr<SDL_Texture> background = nullptr;
};

#endif __SCENE_TITLE_H__