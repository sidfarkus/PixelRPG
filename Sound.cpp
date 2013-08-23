#include "Sound.h"

Sound::Sound(const std::string & filename)  {
   _chunk = Mix_LoadWAV(filename.c_str());

   if (!_chunk)
      _isLoaded = false;
   else
      _isLoaded = true;

   _refs = 1;
   _curchannel = -1;
   _isPaused = false;
   _filename = filename;
}

Sound::Sound(const Sound & sound)  {
   _refs = sound._refs;
   _curchannel = -1;
   _filename = sound._filename;
   _isPaused = false;
   _chunk = Mix_LoadWAV(sound._filename.c_str());
   
   if (!_chunk)
      _isLoaded = false;
   else
      _isLoaded = true;

}

Sound::~Sound()  {
   if (_chunk)  {
      try  {
         if (_curchannel != -1 && Mix_Playing(_curchannel)) Stop();
         Mix_FreeChunk(_chunk);
         _chunk = NULL;
      } catch (int a)  {
         if (_chunk)
            Mix_FreeChunk(_chunk);
      }
   }
}

bool Sound::Play(bool loop)  {
   try  {
      if (_isLoaded)  {
         if (loop)
            _curchannel = Mix_PlayChannel(-1, _chunk, -1);
         else
            _curchannel = Mix_PlayChannel(-1, _chunk, 0);
      }
   }  catch (int a)  {
      return false;
   }

   return false;
}

void Sound::Stop()  {
   if (_curchannel > -1)  {
      Mix_HaltChannel(_curchannel);
      _curchannel = -1;
   }
}

void Sound::Pause()  {
   _isPaused = !_isPaused;
   if (_isPaused)  {
      Mix_Pause(_curchannel);
   } else
      Mix_Resume(_curchannel);
}
