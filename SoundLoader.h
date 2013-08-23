#pragma once

#include "SDLinclude//SDL_mixer.h"
#include "Exception.h"
#include "Sound.h"
#include <string>
#include <map>

typedef std::map<std::string, Sound *>::iterator SOUNDPTR;
class SoundLoader;

struct SOUNDHANDLE  {
   SOUNDPTR SoundPtr;

   SOUNDHANDLE();
   void Play(bool loop = false);
   void Stop();
   void Pause();
};

class SoundLoader  {
public:
   friend struct SOUNDHANDLE;

   static int Init(int channels);
   static void Close();
   static SOUNDHANDLE Load(const std::string & filename);
   static bool TryRelease(SOUNDHANDLE & sound);
   static void ReleaseAll();

   static inline Sound * GetSound(SOUNDHANDLE & s) {
      if (_sounds.size() > 0 && s.SoundPtr != _sounds.end()) 
         return s.SoundPtr->second; 
      return NULL;
   }

   static int  SoundVolume(int val);

   static bool PlayMusic(const std::string & filename, bool loop);
   static int  MusicVolume(int val);
   static void PauseMusic();
   static void StopMusic();

private:
   static Mix_Music * _music;
   static std::map<std::string, Sound *> _sounds;

};
