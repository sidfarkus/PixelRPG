#include "SoundLoader.h"
#include "Console.h"

extern Console console;

std::map<std::string, Sound *> SoundLoader::_sounds = std::map<std::string, Sound *>();
Mix_Music * SoundLoader::_music = NULL;

SOUNDHANDLE::SOUNDHANDLE()  {
   SoundPtr = SoundLoader::_sounds.end();
}

void SOUNDHANDLE::Play(bool loop)  {
   if (SoundPtr != SoundLoader::_sounds.end() && SoundPtr->second)
      SoundPtr->second->Play(loop);
}

void SOUNDHANDLE::Stop() {
   if (SoundPtr != SoundLoader::_sounds.end() && SoundPtr->second)
      SoundPtr->second->Pause();
}

void SOUNDHANDLE::Pause()  {
   if (SoundPtr != SoundLoader::_sounds.end() && SoundPtr->second)
      SoundPtr->second->Stop();
}

int SoundLoader::Init(int channels)  {
   if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)  {
      console.AddLine("Failed to initialize SDL Audio subsystem!");
      return -1;
   }

   if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048) < 0)  {
      console.AddLine("Failed to initialize audio mixer!");
      return -2;
   }

   channels = (channels < 2) ? 2 : (channels > 32) ? 32 : channels;
   Mix_AllocateChannels(channels);
   _music = NULL;
   return 0;
}

void SoundLoader::Close()  {

   if (_music)  {
      Mix_FreeMusic(_music);
      _music = NULL;
   }

   Mix_CloseAudio();
   ReleaseAll();
}

SOUNDHANDLE SoundLoader::Load(const std::string & filename)  {
   if (filename == "") return SOUNDHANDLE();

   SOUNDHANDLE temp;
   temp.SoundPtr = _sounds.find(filename);

   if (temp.SoundPtr != _sounds.end())  {

      temp.SoundPtr->second->_refs++;
      return temp;

   } else {
      
      // Load
      Sound * newsound = new Sound(filename);
      if (newsound->IsLoaded())  {

         console.AddLine("Sound <" + filename + "> loaded successfully.");
         temp.SoundPtr = _sounds.insert(_sounds.end(), std::pair<std::string, Sound *>(filename, newsound));
         return temp;

      }  else  {
         console.AddLine(std::string("Sound <") + filename + "> could not be loaded!");
         return SOUNDHANDLE();
      }
   }
   
   return SOUNDHANDLE();
}

bool SoundLoader::TryRelease(SOUNDHANDLE & sound)  {
   if (sound.SoundPtr != _sounds.end() && sound.SoundPtr->second && (sound.SoundPtr->second->_refs == 0))  {
      _sounds.erase(sound.SoundPtr);
      sound.SoundPtr = _sounds.end();
      return true;
   }

   return false;
}

void SoundLoader::ReleaseAll()  {
   _sounds.clear();
}

int SoundLoader::SoundVolume(int val)  {
   return Mix_Volume(-1, val);
}

bool SoundLoader::PlayMusic(const std::string & filename, bool loop)  {
   try  {
      if (Mix_PlayingMusic())
         Mix_HaltMusic();
         
      if (_music)  {
         Mix_FreeMusic(_music);
         _music = NULL;
      }

      _music = Mix_LoadMUS(filename.c_str());
      
      if (_music)  {
         if (loop)
            Mix_PlayMusic(_music, -1);
         else
            Mix_PlayMusic(_music, 1);
         return true;
      }
   } catch (int a) {

      _music = NULL;
      return false;

   }

   return false;
}

int SoundLoader::MusicVolume(int val)  {
   Mix_VolumeMusic(val);
   return Mix_VolumeMusic(-1);
}

void SoundLoader::PauseMusic()  {
   if (Mix_PausedMusic()) 
      Mix_ResumeMusic();
   else
      Mix_PauseMusic();
}

void SoundLoader::StopMusic()  {
   Mix_HaltMusic();
}
