#pragma once

#include <fstream>
#include <string>
#include <map>
#include "Resources.h"

enum ConfigType  {
   Int,
   Float,
   Bool,
   String
};

struct ConfigEntry  {
   ConfigType Type;
   void *     Value;

   ConfigEntry() {
      Type = Int;
      Value = NULL;
   }

   ConfigEntry(ConfigType type, void * val) {
      Type = type;
      Value = val;
   }
};

// Reads and writes to a configuration file
class ConfigFile  {
public:
   ConfigFile(const std::string & filename);
   ~ConfigFile();

   template <typename ValueType>
   ValueType GetValue(const std::string & name);

   template <typename ValueType>
   void SetValue(const std::string & name, const ValueType & val);

   void Save();
   void Load(const std::string & filename);

private:
   bool _isLoaded;
   std::map<std::string, ConfigEntry> _entries;
   std::string _filename;
};


template <typename ValueType>
ValueType ConfigFile::GetValue(const std::string & name)  {
   if (_isLoaded && (_entries.find(name) != _entries.end())) 
      return *((ValueType *) _entries[name].Value);

   return 0;
}

template <typename ValueType>
void ConfigFile::SetValue(const std::string & name, const ValueType & val)  {
   if (_isLoaded && (_entries.find(name) != _entries.end()))  {
      delete _entries[name].Value;
      _entries[name].Value = new ValueType(val);
   }
}

