#include "MainMenu.h"
#include "Config.h"
#include "Console.h"

#pragma warning(disable : 4482)

extern Console console;
extern ConfigFile Preferences;

MainMenuState::MainMenuState()  {
   GUI::Button * playbutton;
   GUI::Button * loadbutton;
   GUI::Button * optionsbutton;
   GUI::Button * exitbutton;

   mainfont = new GUI::Font((FONTS_PATH + "testfont.fnt").c_str());

   playbutton = new GUI::Button(
      (GUI_PATH + "buttonnorm.png").c_str(), 
      (GUI_PATH + "buttonhover.png").c_str(), 
      (GUI_PATH + "buttonpress.png").c_str(), 
      mainfont, 10, 10, 8, 8, 0, 0, 104, 16, "New Game");
   playbutton->SetClickSound(SOUNDS_PATH + "click.wav");
   playbutton->OnClick(&MainMenuState::PlayClick);

   loadbutton = new GUI::Button(
      (GUI_PATH + "buttonnorm.png").c_str(), 
      (GUI_PATH + "buttonhover.png").c_str(), 
      (GUI_PATH + "buttonpress.png").c_str(), 
      mainfont, 10, 10, 8, 8, 0, 50, 104, 16, "Load Game");
   loadbutton->SetClickSound(SOUNDS_PATH + "click.wav");
   loadbutton->OnClick(&MainMenuState::LoadClick);

   optionsbutton = new GUI::Button(
      (GUI_PATH + "buttonnorm.png").c_str(), 
      (GUI_PATH + "buttonhover.png").c_str(), 
      (GUI_PATH + "buttonpress.png").c_str(), 
      mainfont, 10, 10, 8, 8, 0, 100, 104, 16, "Options");
   optionsbutton->SetClickSound(SOUNDS_PATH + "click.wav");
   optionsbutton->OnClick(&MainMenuState::OptionsClick);

   exitbutton = new GUI::Button(
      (GUI_PATH + "buttonnorm.png").c_str(), 
      (GUI_PATH + "buttonhover.png").c_str(), 
      (GUI_PATH + "buttonpress.png").c_str(), 
      mainfont, 10, 10, 8, 8, 0, 150, 104, 16, "Exit");
   exitbutton->SetClickSound(SOUNDS_PATH + "click.wav");
   exitbutton->OnClick(&MainMenuState::ExitClick);

   menu = new GUI::Layout(130, 325, 150, 200, 10, GUI::Layouts::VerticalLine);
   menu->AddChild(playbutton);
   menu->AddChild(loadbutton);
   menu->AddChild(optionsbutton);
   menu->AddChild(exitbutton);

   mainFrame = new GUI::Frame((GUI_PATH + "window.png").c_str(), 23, 24, 25, 24, 100, 300, 130, 200);
   bgImage = ImageLoader::Load((GUI_PATH + "MenuBGtrans.png").c_str());
   bgSky = ImageLoader::Load((GUI_PATH + "skybg.png").c_str());

   curx = 0;
}

MainMenuState::~MainMenuState() {
   // any cleanup of resources 
   ImageLoader::TryRelease(bgImage);
   ImageLoader::TryRelease(bgSky);

   // all controls should cleanup as destructors are called
   delete menu;
   delete mainfont;
   delete mainFrame;
   menu = NULL;
   mainfont = NULL;
   mainFrame = NULL;
}

void MainMenuState::OnPush()  {
}

void MainMenuState::OnPop()  {
}

void MainMenuState::Update(const ActionMap & actions, unsigned int tElapsed)  {
   if (menu) menu->Update(actions, tElapsed);

   mx = actions.GetInputState()->mouseX; my = actions.GetInputState()->mouseY;
   if (actions.GetInputState()->KeyDown(SDLKey::SDLK_ESCAPE))
      GameStates::QueuePop();
}

void MainMenuState::Draw(RenderDevice::Renderer& render, unsigned int tElapsed) {
   curx += tElapsed / 300.0f;
   if (curx >= 800.0f) curx = curx - 900;

   render.Drawimage(bgSky, (int) curx - 900, 0, 900, 370);
   render.Drawimage(bgSky, (int) curx, 0, 900, 370); 
   render.Drawimage(bgImage, 0, 0, 800, 600);
   mainFrame->Draw(render, tElapsed);
   menu->Draw(render, tElapsed);
}

void MainMenuState::PlayClick(GUI::Control * sender)  {
   GameStates::Swap("Create Character");
}

void MainMenuState::OptionsClick(GUI::Control * sender)  {
   GameStates::Push("Options Menu");
}

void MainMenuState::ExitClick(GUI::Control * sender)  {
   GameStates::QueuePop();
}

void MainMenuState::LoadClick(GUI::Control * sender)  {
}
