#include "OptionsMenu.h"
#include "Config.h"

#pragma warning(disable : 4482)

extern Console console;

extern ConfigFile Preferences;

OptionsMenuState::OptionsMenuState()  {
   // init fonts
   font = new GUI::Font((FONTS_PATH + "testfont.fnt").c_str());
   titlefont = new GUI::Font((FONTS_PATH + "testfont.fnt").c_str());

   frame = new GUI::Frame((GUI_PATH + "window.png").c_str(), 23, 24, 25, 24, 250, 180, 300, 250);
   frame->AlignToRect(GUI::Align::Center, 0, 0, 0, 800, 600);

   // declare controls to load into a layout
   GUI::CheckBox::CaptionAlign = GUI::Align::Right;

   GUI::CheckBox * box1 = new GUI::CheckBox((GUI_PATH + "checkbox.png").c_str(), font, "Windowed", 24, 0, 0, 50, 24);
   box1->SetChecked(Preferences.GetValue<bool>("WINDOWED"));
   box1->OnClick(&windowedClick);

   GUI::CheckBox * box2 = new GUI::CheckBox((GUI_PATH + "checkbox.png").c_str(), font, "Sound On/Off", 24, 0, 0, 50, 24);
   box2->SetChecked(Preferences.GetValue<bool>("SOUND"));
   box2->OnClick(&soundClick);

   GUI::Slider * volume = new GUI::Slider((GUI_PATH + "slider.png").c_str(), 7, 0, 128, 2, 0, 0, 150, 16);
   volume->SetValue(Preferences.GetValue<int>("SOUNDVOL"));
   volume->ValueChanged(&OptionsMenuState::SoundVolChanged);
   SoundLoader::SoundVolume(volume->GetValue());
   GUI::Label * vollabel = new GUI::Label("Sound Volume", font, 0, 0);
   
   GUI::Slider * musvolume = new GUI::Slider((GUI_PATH + "slider.png").c_str(), 7, 0, 128, 2, 0, 0, 150, 16);
   musvolume->SetValue(Preferences.GetValue<int>("MUSICVOL"));
   musvolume->ValueChanged(&OptionsMenuState::MusicVolChanged);
   SoundLoader::MusicVolume(musvolume->GetValue());
   GUI::Label * muslabel = new GUI::Label("Music Volume", font, 0, 0);


   saveButton = new GUI::Button(
      (GUI_PATH + "buttonnorm.png").c_str(), 
      (GUI_PATH + "buttonhover.png").c_str(), 
      (GUI_PATH + "buttonpress.png").c_str(), 
      font, 10, 10, 8, 8, frame->Right() - 200, frame->Bottom() - 60, 70, 16, "Save");
   saveButton->OnClick(&OptionsMenuState::SaveClick);
   saveButton->SetClickSound(SOUNDS_PATH + "click.wav");

   cancelButton = new GUI::Button(
      (GUI_PATH + "buttonnorm.png").c_str(), 
      (GUI_PATH + "buttonhover.png").c_str(), 
      (GUI_PATH + "buttonpress.png").c_str(), 
      font, 10, 10, 8, 8, frame->Right() - 112, frame->Bottom() - 60, 70, 16, "Cancel");
   cancelButton->OnClick(&OptionsMenuState::CancelClick);
   cancelButton->SetClickSound(SOUNDS_PATH + "click.wav");

   controlLayout = new GUI::Layout(frame->X() + 20, frame->Y() + 35, frame->Width() - 50, frame->Height() - 50, 20, GUI::Layouts::Grid, GUI::Align::Top | GUI::Align::Left);
   controlLayout->AddChild(box1);
   controlLayout->AddChild(box2);  
   controlLayout->AddChild(vollabel);
   controlLayout->AddChild(volume);
   controlLayout->AddChild(muslabel);
   controlLayout->AddChild(musvolume);
}

OptionsMenuState::~OptionsMenuState()  {
   delete frame;
   delete saveButton;
   delete cancelButton;
   delete controlLayout;

   frame = NULL;
   saveButton = NULL;
   cancelButton = NULL;
   controlLayout = NULL;
}

void OptionsMenuState::OnPush()  {
}

void OptionsMenuState::OnPop()  {
}

void OptionsMenuState::Draw(RenderDevice::Renderer& render, unsigned int tElapsed)  {
   frame->Draw(render, tElapsed);

   titlefont->Draw(render, "Options", frame->X() + 40, frame->Y() + 20);
   render.Hline(frame->X() + 30, frame->Right() - 40, frame->Y() + 40, Color::Yellow);

   saveButton->Draw(render, tElapsed);
   cancelButton->Draw(render, tElapsed);
   controlLayout->Draw(render, tElapsed);

}

void OptionsMenuState::Update(const ActionMap & actions, unsigned int tElapsed)  {
   if (actions.GetInputState()->KeyDown(SDLKey::SDLK_ESCAPE))
      GameStates::QueuePop();

   saveButton->Update(actions, tElapsed);
   cancelButton->Update(actions, tElapsed);
   controlLayout->Update(actions, tElapsed);

}

void OptionsMenuState::SaveClick(GUI::Control * sender)  {
   Preferences.Save();
   console.AddLine("Preferences saved.");
   GameStates::QueuePop();
}

void OptionsMenuState::CancelClick(GUI::Control * sender)  {
   GameStates::QueuePop();
}

void OptionsMenuState::SoundVolChanged(GUI::Slider * sender)  {
   Preferences.SetValue<int>("SOUNDVOL", sender->GetValue());
   SoundLoader::SoundVolume(sender->GetValue());
}

void OptionsMenuState::MusicVolChanged(GUI::Slider * sender)  {
   Preferences.SetValue<int>("MUSICVOL", sender->GetValue());
   SoundLoader::MusicVolume(sender->GetValue());
}

void OptionsMenuState::windowedClick(GUI::Control * sender)  {
   GUI::CheckBox * c = (GUI::CheckBox *) sender;
   Preferences.SetValue<bool>("WINDOWED", c->Checked());
}

void OptionsMenuState::soundClick(GUI::Control * sender)  {
   GUI::CheckBox * c = (GUI::CheckBox *) sender;
   Preferences.SetValue<bool>("SOUND", c->Checked());
}
