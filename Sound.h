#pragma once

#include "SDLinclude//SDL.h"
#include "SDLinclude//SDL_mixer.h"
#include <string>

class SoundLoader;

class Sound  {
public:
   Sound(const std::string & filename);
   Sound(const Sound & sound);
   ~Sound();

   bool Play(bool loop = false);
   void Stop();
   void Pause();

   inline bool IsLoaded() const {return _isLoaded;}
   inline bool IsPaused() const {return _isPaused;}

   friend class SoundLoader;

private:
   std::string _filename;
   bool _isLoaded, _isPaused;
   Mix_Chunk * _chunk;
   int _refs, _curchannel;
};

