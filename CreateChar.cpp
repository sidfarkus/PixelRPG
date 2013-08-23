#include "CreateChar.h"
#include "Resources.h"

#pragma warning(disable : 4482)

CreateChar::CreateChar()  {
   _bg = ImageLoader::Load((GUI_PATH + "createchar.png").c_str());
   _font = new GUI::Font((FONTS_PATH + "testfont.fnt").c_str());

   _create = new GUI::Button(
      (GUI_PATH + "buttonnorm.png").c_str(), 
      (GUI_PATH + "buttonhover.png").c_str(), 
      (GUI_PATH + "buttonpress.png").c_str(), 
      _font, 10, 10, 8, 8, 588, 540, 80, 16, "Create");
   _create->SetClickSound(SOUNDS_PATH + "click.wav");
   _create->OnClick(&CreateChar::CreateClick);

   _cancel = new GUI::Button(
      (GUI_PATH + "buttonnorm.png").c_str(), 
      (GUI_PATH + "buttonhover.png").c_str(), 
      (GUI_PATH + "buttonpress.png").c_str(), 
      _font, 10, 10, 8, 8, 690, 540, 80, 16, "Cancel");
   _cancel->SetClickSound(SOUNDS_PATH + "click.wav");
   _cancel->OnClick(&CreateChar::CancelClick);

   _traits = new GUI::ListBox(GUI_PATH + "listbox.png", _font, 16, 32, 3, 4, 100, 120, 195, 380);
   _stats = new GUI::Frame((GUI_PATH + "frame.png").c_str(), 3, 3, 3, 3, 300, 310, 190, 184);
   _name = new GUI::TextBox((GUI_PATH + "textbox.png").c_str(), _font, 3, 18, 300, 290, 196, 16);

   GUI::Control * tempLabel = new GUI::Label("Strength", _font, 0, 0);
   _statslayout = new GUI::Layout(300, 310, 190, 184, 3, GUI::Layouts::Grid);
   _statslayout->AddChild(tempLabel);
   _statslayout->AddSpacer(GUI::HorizontalSpacer, _statslayout->Width() - tempLabel->Width() - 40);
   _statslayout->AddChild(new GUI::UpDown(GUI_PATH + "updown.png", _font, 16, 0, 10, 455, 320, 32, 16));

   tempLabel = new GUI::Label("Agility", _font, 0, 0);
   _statslayout->AddChild(tempLabel);
   _statslayout->AddSpacer(GUI::HorizontalSpacer, _statslayout->Width() - tempLabel->Width() - 40);
   _statslayout->AddChild(new GUI::UpDown(GUI_PATH + "updown.png", _font, 16, 0, 10, 455, 320, 32, 16));

   tempLabel = new GUI::Label("Precision", _font, 0, 0);
   _statslayout->AddChild(tempLabel);
   _statslayout->AddSpacer(GUI::HorizontalSpacer, _statslayout->Width() - tempLabel->Width() - 40);
   _statslayout->AddChild(new GUI::UpDown(GUI_PATH + "updown.png", _font, 16, 0, 10, 455, 320, 32, 16));

   tempLabel = new GUI::Label("Focus", _font, 0, 0);
   _statslayout->AddChild(tempLabel);
   _statslayout->AddSpacer(GUI::HorizontalSpacer, _statslayout->Width() - tempLabel->Width() - 40);
   _statslayout->AddChild(new GUI::UpDown(GUI_PATH + "updown.png", _font, 16, 0, 10, 455, 320, 32, 16));

   tempLabel = new GUI::Label("Charisma", _font, 0, 0);
   _statslayout->AddChild(tempLabel);
   _statslayout->AddSpacer(GUI::HorizontalSpacer, _statslayout->Width() - tempLabel->Width() - 40);
   _statslayout->AddChild(new GUI::UpDown(GUI_PATH + "updown.png", _font, 16, 0, 10, 455, 320, 32, 16));

   _listIcons = ImageLoader::Load((GUI_PATH + "smallicons.png").c_str());
   _traits->AddItem("Master Assassin", _listIcons, 16, 2, 0);
   _traits->AddItem("Heart of Fire", _listIcons, 16, 3, 0);
   _traits->AddItem("Hard to Kill", _listIcons, 16, 0, 0);
   _traits->AddItem("Out for Justice", _listIcons, 16, 2, 0);
   _traits->AddItem("Against the Dark", _listIcons, 16, 3, 0);
   _traits->AddItem("Under Siege", _listIcons, 16, 1, 0);
   
}

CreateChar::~CreateChar()  {
   ImageLoader::TryRelease(_bg);
   ImageLoader::TryRelease(_listIcons);

   delete _font;
   delete _create;
   delete _cancel;
   delete _traits;
   delete _statslayout;
   delete _stats;
   delete _name;

   _font = NULL;
   _create = NULL;
   _cancel = NULL;
   _traits = NULL;
   _statslayout = NULL;
   _stats = NULL;
   _name = NULL;
}

void CreateChar::OnPush()  {
}

void CreateChar::OnPop()  {
}

void CreateChar::Update(const ActionMap & actions, unsigned int tElapsed)  {
   _create->Update(actions, tElapsed);
   _cancel->Update(actions, tElapsed);

   _stats->Update(actions, tElapsed);
   _statslayout->Update(actions, tElapsed);
   _traits->Update(actions, tElapsed);
   _name->Update(actions, tElapsed);
}

void CreateChar::Draw(RenderDevice::Renderer& render, unsigned int tElapsed)  {
   render.Drawimage(_bg, 0, 0, 800, 600);  
   _create->Draw(render, tElapsed);
   _cancel->Draw(render, tElapsed);

   _stats->Draw(render, tElapsed);
   _traits->Draw(render, tElapsed);
   _statslayout->Draw(render, tElapsed);
   _name->Draw(render, tElapsed);
}

void CreateChar::CreateClick(GUI::Control * sender)  {
   GameStates::Swap("Map View");
}

void CreateChar::CancelClick(GUI::Control * sender)  {
   GameStates::Swap("Main Menu");
}
