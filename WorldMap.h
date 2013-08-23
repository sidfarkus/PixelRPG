#pragma once

#include "GameStates.h"
#include "SoundLoader.h"
#include "Renderer.h"
#include "Font.h"
#include "Map.h"
#include "Tileset.h"

class WorldMap : public GameState {
public:
   WorldMap();
   ~WorldMap();
   virtual void OnPush();
   virtual void OnPop();
   virtual void Draw(RenderDevice::Renderer& render, unsigned int tElapsed);
   virtual void Update(const ActionMap & actions, unsigned int tElapsed);

private:
   IMAGEHANDLE mapimg;
};
