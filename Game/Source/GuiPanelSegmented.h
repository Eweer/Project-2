#ifndef __GUIPANELSEGMENTED_H__
#define __GUIPANELSEGMENTED_H__

#include "Point.h"
#include "Defs.h"

#include "TextureManager.h"

class GuiPanelSegmented
{
public:
	void Draw(iPoint originalPosition, iPoint size) const;
	void Unload() const;
	void Create(SDL_Rect const& r, iPoint a, int id, iPoint tSegments = iPoint(3, 3));
	void Create(SDL_Rect const& r, int a, int id, iPoint tSegments = iPoint(3, 3));

private:
	void DrawHorizontalSegment(iPoint topLeftPosition, SDL_Rect currentSegment, iPoint size) const;

	SDL_Rect rect{ 0 };
	iPoint advance{ 0 };
	int textureID = -1;
	iPoint textureSegments = { 3, 3 };

};

#endif // __GUIPANELSEGMENTED_H__
