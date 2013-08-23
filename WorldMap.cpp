#include "WorldMap.h"
#include "Resources.h"
#include <sstream>

#pragma warning(disable : 4482)

WorldMap::WorldMap()  {
   mapimg = ImageLoader::Load((MAP_PATH + "Worldmap.png").c_str());
}

WorldMap::~WorldMap()  {
}

void WorldMap::OnPush() {
}

void WorldMap::OnPop() {
}

void WorldMap::Draw(RenderDevice::Renderer& render, unsigned int tElapsed)  {
   render.Drawimage(mapimg, 0, 0, render.ScreenWidth(), render.ScreenHeight());
}

void WorldMap::Update(const ActionMap & actions, unsigned int tElapsed)  {
   if (actions.GetInputState()->KeyDown(SDLKey::SDLK_m))  {
      GameStates::QueuePop();
   }
}