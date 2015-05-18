/*
   Feather INI Parser - 1.26
   You are free to use this for whatever you wish.

   If you find a bug, please debug the cause and look into a solution.
   Post your compiler, version and the cause or fix in the issues section.

   Written by Turbine.

   Website:
   http://code.google.com/p/feather-ini-parser/downloads

   Help:
   http://code.google.com/p/feather-ini-parser/wiki/Tutorials
*/

#ifndef INIPARSER_H
#define INIPARSER_H

#include <map>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

///
template<class T, class U>
   static T Convert(U value)
{
   std::stringstream sout;
   T result;

   sout << value;
   sout >> result;

   return result;
}

///
template<class T = std::string, class U = std::string, class V = std::string>
   class INI
{
public:
   typedef char char_t;
   typedef T section_t;
   typedef U key_t;
   typedef V value_t;

   ///Type definitions
   typedef typename std::map<key_t, value_t> keys_t;
   typedef typename std::map<section_t, keys_t*> sections_t;

   typedef typename keys_t::iterator keysit_t;
   typedef typename sections_t::iterator sectionsit_t;

   typedef typename std::pair<key_t, value_t> keyspair_t;
   typedef typename std::pair<section_t, keys_t*> sectionspair_t;

   ///Settings & Tweaks
   static const int BUFFER_SIZE = 128;

   ///Data members
   keys_t* current;
   sections_t sections;

   ///Constuctor/Destructor
   INI(std::string filename, bool parse = true);
   ~INI();

   ///Accessing structure
   keys_t& operator[](section_t section);

   bool Create(const section_t section);
   bool Select(const section_t section);

   //Set
   bool Set(const key_t key, const value_t value);
   template<class W, class X>
      bool Set(const W key, const X value)
         { return Set(Convert<key_t>(key), Convert<value_t>(value)); }

   //Get
   value_t Get(const key_t key, value_t def = value_t());  //Get value, if none exists
   std::string Get(const key_t key, const char_t* def = "");  //Can handle const char* without casting
   template<class W, class X>
      X Get(const W key,  X def = X())
         { return Convert<X>(Get(Convert<value_t>(key), Convert<value_t>(def))); }

   ///Functions
   void Nake(const char_t*);  //Strip the line of any non-interpretable characters
   bool Parse();
   void Clear();

   ///Output
   void Save(std::string filename = "");

private:
   std::string filename;

   ///Output
   std::string makeSection(const section_t& section);
   std::string makeKeyValue(const key_t& key, const value_t& value);
};

///
template<class T, class U, class V>
   INI<T, U, V>::INI(std::string filename, bool parse): filename(filename), current(NULL)
{
   if (parse)
      Parse();
}

///
template<class T, class U, class V>
   INI<T, U, V>::~INI()
{
   Clear();
}

///
template<class T, class U, class V>
   typename INI<T, U, V>::keys_t& INI<T, U, V>::operator[](section_t section)
{
   return *sections[section];
}

///
template<class T, class U, class V>
   void INI<T, U, V>::Clear()
{
   for(sectionsit_t i = sections.begin(); i != sections.end(); i++)
      delete i->second;

   current = NULL;
}

///
template<class T, class U, class V>
   bool INI<T, U, V>::Create(const section_t section)
{
   if (Select(section))
      return false;

   current = new keys_t;
   sections[section] = current;

   return true;
}

///
template<class T, class U, class V>
   bool INI<T, U, V>::Select(const section_t section)
{
   sectionsit_t sectionsit = sections.find(section);
   if (sectionsit == sections.end())
      return false;

   current = sectionsit->second;

   return true;
}

///
template<class T, class U, class V>
   bool INI<T, U, V>::Set(const key_t key, const value_t value)
{
   if (current == NULL)
      return false;

   (*current)[key] = value;

   return true;
}

///
template<class T, class U, class V>
   typename INI<T, U, V>::value_t INI<T, U, V>::Get(const key_t key, const value_t def)
{
   keysit_t keys = current->find(key);
   if (current == NULL || keys == current->end())
      return def;

   return keys->second;
}

///
template<class T, class U, class V>
   std::string INI<T, U, V>::Get(const key_t key, const char_t* def)
{
   return Get(key, (std::string)def);
}

///
template<class T, class U, class V>
   void INI<T, U, V>::Nake(const char_t*)
{

}

///
template<class T, class U, class V>
   bool INI<T, U, V>::Parse()
{
   current = NULL;
   std::ifstream file(filename.c_str());
   if (!file.is_open())
      return false;

   char_t line[BUFFER_SIZE];

   while(!file.eof())
   {
      file.getline(line, BUFFER_SIZE);

      Nake(line);

      if (line[0] != NULL)
      {
         if (!((strlen(line) >= 2) && line[0] == '/' && line[1] == '/'))  //Ignore comment
         {
            if (line[0] == '[')  //Section
            {
               std::stringstream out;
               section_t section;

               size_t length = strlen(line) - 2;  //Without section brackets
               while(isspace(line[length + 1]))  //Leave out any additional new line characters
                  --length;

               char_t* ssection = (char_t*)calloc(sizeof(char_t), length + 1);

               strncpy(ssection, line + 1, length);  //Count after first bracket

               current = new keys_t;

               out << ssection;
               out >> section;

               sections[section] = current;
            }
            else  //Key
            {
               std::stringstream out1, out2;
               key_t key;
               value_t value;

               char_t* skey;
               char_t* svalue;
               skey = strtok(line, "=");
               svalue = strtok(NULL, "=");

               out1 << skey;
               out1 >> key;

               out2 << svalue;
               out2 >> value;

               (*current)[key] = value;
            }
         }
      }
   }

   file.close();

   return true;
}

///
template<class T, class U, class V>
   std::string INI<T, U, V>::makeSection(const section_t& section)
{
   std::stringstream line;
   line << '[' << section << ']' << std::endl;

   return line.str();
}

///
template<class T, class U, class V>
   std::string INI<T, U, V>::makeKeyValue(const key_t& key, const value_t& value)
{
   std::stringstream line;
   line << key << '=' << value << std::endl;

   return line.str();
}

///
template<class T, class U, class V>
   void INI<T, U, V>::Save(std::string filename)
{
   std::ofstream file(((filename == "")? this->filename: filename).c_str(), std::ofstream::trunc);

   //Loop through sections
   for(INI::sectionsit_t i = sections.begin(); i != sections.end(); i++)
   {
      if (i->second->size() == 0)  //No keys/values in section, skip to next
         continue;

      //Write section
      const std::string temp = makeSection(i->first);
      const char_t* line = temp.c_str();
      file.write(line, strlen(line));

      for(INI::keysit_t j = i->second->begin(); j != i->second->end(); j++)
      {
         //Write key and value
         const std::string temp = makeKeyValue(j->first, j->second);
         const char* line = temp.c_str();
         file.write(line, strlen(line));
      }
   }

   file.close();
}

#endif
