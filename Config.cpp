#include "Config.h"
#include "ConfigFiles.h"

ConfigFile::ConfigFile(const std::string & filename)  {
   _isLoaded = false;
   Load(filename);
}

ConfigFile::~ConfigFile()  {
   // delete all void pointers
   for (std::map<std::string, ConfigEntry>::iterator i = _entries.begin();
      i != _entries.end(); i++)  {
      delete i->second.Value;
   }
}

void ConfigFile::Save()  {
   if (!_isLoaded) return;

   std::ofstream outfile(_filename.c_str());

   if (!outfile)  {
      return;
   }

   for (std::map<std::string, ConfigEntry>::iterator i = _entries.begin();
      i != _entries.end(); i++)  {

      outfile << i->first << " ";
      
      switch(i->second.Type)  {
         case Int:
            outfile << *((int *) i->second.Value);
            break;
         case Float:
            outfile << *((float *) i->second.Value);
            break;
         case Bool:

            if (*((bool *) i->second.Value))
               outfile << "true";
            else
               outfile << "false";

            break;
         case String:
            outfile << *((std::string *) i->second.Value);
            break;
      }

      outfile << std::endl;
   }

   outfile.close();
   
}

void ConfigFile::Load(const std::string & filename)  {

   // if this has a file loaded release it first
   if (_isLoaded)  {
      for (std::map<std::string, ConfigEntry>::iterator i = _entries.begin();
         i != _entries.end(); i++)  {
         delete i->second.Value;
      }
   }

   std::ifstream infile(filename.c_str());
   std::string name = "", val = "";
   
   if (!infile)  {
      _isLoaded = false;
      return;
   }

   // read in all the settings
   while (!infile.eof())  {
      infile >> name;
      infile.ignore();
      std::getline(infile, val);
      //val.erase(--val.end());      // erase newline

      // figure out the type of data
      if (atoi(val.c_str()) != 0)  {

         // INTEGER
         _entries[name] = ConfigEntry(Int, (void *) new int(atoi(val.c_str())) );

      }  else if (atof(val.c_str()) != 0.0f)  {
         
         // FLOAT
         _entries[name] = ConfigEntry(Float, (void *) new float(atof(val.c_str())) );

      }  else if (val.find(std::string("true")) == 0 ||
                  val.find(std::string("false")) == 0)  {

         // BOOL
         if (val.find(std::string("true")) == 0) 
            _entries[name] = ConfigEntry(Bool, (void *) new bool(true));
         else
            _entries[name] = ConfigEntry(Bool, (void *) new bool(false));

      }  else  {
         
         // STRING
         _entries[name] = ConfigEntry(String, (void *) new std::string(val));

      }
   }

   infile.close();

   _filename = filename;
   _isLoaded = true;
}
