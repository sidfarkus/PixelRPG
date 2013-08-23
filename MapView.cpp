#include "MapView.h"
#include "Resources.h"
#include <sstream>

#pragma warning(disable : 4482)

MapView::MapView()  {
   _font = new GUI::Font((FONTS_PATH + "testfont.fnt").c_str());
   _map = new Map(MAP_PATH + "World.png");
   _map->RegisterTileType(new Tileset(TILES_PATH + "grass.png", Cell::TILESIZE), 0x00B49F6E);
   _map->RegisterTileType(new Tileset(TILES_PATH + "water.png", Cell::TILESIZE), 0x000F87AF);

   _miniMap = new GUI::MiniMap((GUI_PATH + "wideframe.png").c_str(), *_map, 8, 620, 0, 150, 150);

   screenx = 0;
   screeny = 0;
   screenxvel = 0;
   screenyvel = 0;
   oldcellx = 0;
   oldcelly = 0;
}

MapView::~MapView()  {
   delete _font;
   delete _map;
   delete _miniMap;
   _miniMap = NULL;
   _map = NULL;
   _font = NULL;
}

void MapView::OnPush() {
   screenx = Cell::CELLWIDTH * STARTCELLX;
   screeny = Cell::CELLWIDTH * STARTCELLY;
   oldcellx = STARTCELLX;
   oldcelly = STARTCELLY;
   _map->SetView(MapCoord(STARTCELLX, STARTCELLY));

   // load static objects
   ImageAnimation image((STATICS_PATH + "basichouse.png").c_str(), 0, 64, 1, 1);
   StaticObject * temp = new StaticObject("Test House", image, screenx, screeny);
   _statics.AddStatic(temp);

   SoundLoader::PlayMusic(MUSIC_PATH + "Walking.it", true);
}

void MapView::OnPop() {
   SoundLoader::PlayMusic(MUSIC_PATH + "Theme.xm", true);
   _statics.RemoveStatic("Test House");
}

void MapView::Draw(RenderDevice::Renderer& render, unsigned int tElapsed)  {
   std::ostringstream os;

   os << "Mouse X: " << mx << " Y: " << my;

   _map->DrawView(render, screenx, screeny);
   
   _statics.DrawStatics(render, tElapsed, screenx, screeny);

   _font->Draw(render, os.str(), 0, 0);
   _miniMap->Draw(render, tElapsed);
}

void MapView::Update(const ActionMap & actions, unsigned int tElapsed)  {
   const InputState & input = *actions.GetInputState();

   mx = screenx + input.mouseX;
   my = screeny + input.mouseY;
   oldcellx = screenx / Cell::CELLWIDTH;
   oldcelly = screeny / Cell::CELLWIDTH;

   if (input.KeyDown(SDLKey::SDLK_ESCAPE))  {
      GameStates::Swap("Main Menu");
   } else if (input.KeyDown(SDLKey::SDLK_m))  {
      GameStates::QueuePush("World Map");
   }

   if (actions.GetState("up") == ActionState::Pressed)  {
      screenyvel += -1;
   }

   if (actions.GetState("down") == ActionState::Pressed)  {
      screenyvel += 1;
   }

   if (actions.GetState("left") == ActionState::Pressed)  {
      screenxvel += -1;
   }

   if (actions.GetState("right") == ActionState::Pressed)  {
      screenxvel += 1;
   }

   if (actions.GetState("up") == ActionState::Released || 
       actions.GetState("down") == ActionState::Released)  {
      screenyvel = 0;
   }

   if (actions.GetState("left") == ActionState::Released || 
       actions.GetState("right") == ActionState::Released)  {
      screenxvel = 0;
   }

   screenx += (screenxvel * (int) tElapsed) / 4;
   screeny += (screenyvel * (int) tElapsed) / 4;

   if (screenx < 0) screenx = 0;
   if (screenx > Cell::CELLWIDTH * _map->Width()) screenx = Cell::CELLWIDTH * _map->Width();
   
   if (screeny < 0) screeny = 0;
   if (screeny > Cell::CELLWIDTH * _map->Height()) screeny = Cell::CELLWIDTH * _map->Height();

   if (oldcellx != screenx / Cell::CELLWIDTH || oldcelly != screeny / Cell::CELLWIDTH) 
      _map->SetView(MapCoord(screenx / Cell::CELLWIDTH, screeny / Cell::CELLWIDTH));

   _miniMap->Update(actions, tElapsed);

}
