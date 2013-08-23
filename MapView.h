#pragma once

#include "GameStates.h"
#include "SoundLoader.h"
#include "Renderer.h"
#include "Font.h"
#include "Map.h"
#include "Tileset.h"
#include "StaticsCollection.h"
#include "MiniMap.h"

class MapView : public GameState {
public:
   MapView();
   ~MapView();
   virtual void OnPush();
   virtual void OnPop();
   virtual void Draw(RenderDevice::Renderer& render, unsigned int tElapsed);
   virtual void Update(const ActionMap & actions, unsigned int tElapsed);

   static const int STARTCELLX = 450;
   static const int STARTCELLY = 450;

private:
   int screenx, screeny;
   int screenxvel, screenyvel;
   int oldcellx, oldcelly;
   int mx, my;
   GUI::Font * _font;
   GUI::MiniMap * _miniMap;
   Map * _map;
   StaticsCollection _statics;
};
