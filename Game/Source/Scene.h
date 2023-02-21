#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

#include "GuiScreen.h"

struct SDL_Texture;

struct BGInfo
{
	std::shared_ptr<SDL_Texture>texture;
	fPoint position;
	float increase;
	fPoint size;
};

class Scene : public Module
{
public:

	Scene();

	// Destructor
	~Scene() final;

	// Called before render is available
	bool Awake(pugi::xml_node& config) final;

	// Called before the first frame
	bool Start() final;

	// Called before all Updates
	bool PreUpdate() final;

	bool Pause(int phase) final;

	// Called each loop iteration
	bool Update(float dt) final;

	// Called before all Updates
	bool PostUpdate() final;

	// Called before quitting
	bool CleanUp() final;

	bool HasSaveData() const final;
	bool LoadState(pugi::xml_node const &data) final;
	pugi::xml_node SaveState(pugi::xml_node const &) const final;

	std::string mapsPath;
	std::vector<std::string> maps;
	std::vector<GuiScreen> windows;
};

#endif // __SCENE_H__