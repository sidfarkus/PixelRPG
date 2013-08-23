#pragma once

#include "Control.h"
#include "ImageLoader.h"
#include "SoundLoader.h"
#include "Font.h"
#include <string>
#include <vector>

namespace GUI  {
   // Item in the list
   struct ListItem  {
      std::string Text;
      IMAGEHANDLE Icon;
      int IconTU, IconTV;
      int IconSize;
   };

   class ListBox : public Control, public IClickable {
   public:
      // Image layout is
      // <   upscroll   > <  downscroll   > < listframe ... >
      // <upscrollclick > <downscrollclick> < listframe ... >
      // <  scrollbar   > <  scrollclick  > < listframe ... >
      // <highlightframe> <     barbg     > < listframe ... >
      // < highlightsel > <     barbg     > < listframe ... >
      //
      // all the scrollbar components are scrollWidth wide
      // listframe must be the entire right side
      // highlight frame is rendered around the selected item
      ListBox(const std::string & imagefile, GUI::Font * font, int scrollWidth, int highlightHeight, int highlightBorder, 
              int listBorder, int x, int y, unsigned int w, unsigned int h);

      virtual ~ListBox();

      void AddItem(const std::string & text, IMAGEHANDLE icon = -1, int iconSize = 0, int indexX = 0, int indexY = 0);
      ListItem GetItem(int index) const;
      void MoveItem(int startIndex, int moveLocation);

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      inline unsigned int Count() const {return (unsigned int) _items.size();}
      inline int SelectedIndex() const {return _selectedIndex;}
      inline void OnSelect(void (*onSelect)(ListBox *)) {_onSelect = onSelect;}

      static const int ICON_PADDING = 5;

   private:
      enum ListboxState {
         None,
         UpScroll,
         DownScroll,
         ScrollGrab,
         ItemSelect
      };

      bool _drawScroll;
      int _itemHeight;
      int _scrollVal;
      int _scrollHeight;
      int _selectedIndex;
      int _scrollWidth;
      int _listBorder;
      int _barbgCapsize;
      int _highlightBorder;
      int _highlightHeight;
      ListboxState _state;
      GUI::Font * _font;
      IMAGEHANDLE _img;
      std::vector<ListItem *> _items;

      void (*_onSelect)(ListBox *);
   };
}
