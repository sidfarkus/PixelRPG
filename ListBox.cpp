#include "ListBox.h"

#include "Console.h"
extern Console console;

namespace GUI  {
   ListBox::ListBox(const std::string & imagefile, GUI::Font * font, int scrollWidth, int highlightHeight, int highlightBorder, int listBorder, 
                    int x, int y, unsigned int w, unsigned int h) : Control(x,y,w,h) {

      _img = ImageLoader::Load(imagefile.c_str());
      _font = font;
      _scrollWidth = scrollWidth;
      _highlightBorder = highlightBorder;
      _listBorder = listBorder;
      _highlightHeight = highlightHeight;
      _barbgCapsize = 7;
      _scrollVal = 0;
      _state = None;
      _drawScroll = false;
      _scrollHeight = height - _listBorder - _listBorder - _scrollWidth - _scrollWidth;
      _onSelect = NULL;
      
      if (font) 
         _itemHeight = font->Height();
      else
         _itemHeight = 0;
   }

   ListBox::~ListBox()  {
      ImageLoader::TryRelease(_img);

      for (std::vector<ListItem *>::iterator i = _items.begin(); i != _items.end(); i++)
         delete *i;
   }

   bool ListBox::Update(const ActionMap & actions, unsigned int tElapsed)  {
      const InputState & input = *actions.GetInputState();

      // Mouse over scrollbar
      if ((_drawScroll) && (input.mouseX >= Right() - _scrollWidth - _listBorder) && (input.mouseX <= Right() - _listBorder) &&
         (input.mouseY >= y + _listBorder) && (input.mouseY <= Bottom() - _listBorder))  {

         if (input.mbReleased & MOUSE_B1)  {
            _state = None;
         } else if (input.mbPressed & MOUSE_B1 || _state == ScrollGrab) {

            if (_state == ScrollGrab)  {

               _scrollVal = input.mouseY - y - _listBorder - _scrollWidth;

            } else if (input.mouseY < y + _listBorder + _scrollWidth || _state == UpScroll)  {

               _state = UpScroll;
               _scrollVal -= _scrollHeight / _itemHeight;

            } else if (input.mouseY > Bottom() - _scrollWidth - _listBorder || _state == DownScroll) {

               _state = DownScroll;
               _scrollVal += _scrollHeight / _itemHeight;

            } else if ((input.mouseY <= y + _listBorder + _scrollWidth + _scrollHeight) && 
                       (input.mouseY >= y + _listBorder + _scrollWidth))  {

              _scrollVal = input.mouseY - y - _listBorder - _scrollWidth;
              _state = ScrollGrab;

            } else  {
               _state = None;
            }
         }

         // Mouse over list area
      }  else if ((input.mouseX >= x + _listBorder) && (input.mouseX <= Right() - _scrollWidth - _listBorder) &&
                  (input.mouseY >= y + _listBorder) && (input.mouseY <= Bottom() - _listBorder))  {
         
         if (input.mbPressed & MOUSE_B1 && _items.size())  {
            _selectedIndex = (input.mouseY - y - _listBorder) / (_itemHeight) + (int) ((_scrollVal / (float) (_scrollHeight - _scrollWidth)) * _items.size());
            if (_onSelect) _onSelect(this);
            _state = ItemSelect;
         }

      } else {
         
         if (_state == ScrollGrab && !(input.mbReleased & MOUSE_B1))  {
            _scrollVal = input.mouseY - y - _listBorder - _scrollWidth;
         } else
            _state = None;
      }

      if (_scrollVal < 0) 
         _scrollVal = 0;
      else if (_scrollVal > _scrollHeight - _scrollWidth)
         _scrollVal = _scrollHeight - _scrollWidth;

      return Collide(input.mouseX, input.mouseY);
   }

   void ListBox::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      const Image * img = ImageLoader::GetImage(_img);
      if (!img) return;

      int iw = img->Width();
      int ih = img->Height();
      int centerw = width - _listBorder - _listBorder;
      int centerh = height - _listBorder - _listBorder;
      int xoff = _scrollWidth + _scrollWidth;

      // frame     
      // top
      renderer.Drawimage(_img, x, y, 0, 0, xoff, 0, _listBorder, _listBorder);
      renderer.Drawimage(_img, x + _listBorder, y, centerw, _listBorder, xoff + _listBorder, 0, iw - (_listBorder + _listBorder) - xoff, _listBorder, true);
      renderer.Drawimage(_img, x + _listBorder + centerw, y, 0, 0, iw - _listBorder, 0, _listBorder, _listBorder);

      // middle
      renderer.Drawimage(_img, x, y + _listBorder, _listBorder, centerh, xoff, _listBorder, _listBorder, ih - (_listBorder + _listBorder), true);
      renderer.Drawimage(_img, x + _listBorder, y + _listBorder, centerw, centerh, xoff + _listBorder, _listBorder, iw - (_listBorder + _listBorder) - xoff, ih - (_listBorder + _listBorder), true);
      renderer.Drawimage(_img, x + _listBorder + centerw, y + _listBorder, _listBorder, centerh, iw - _listBorder, _listBorder, _listBorder, ih - (_listBorder + _listBorder), true);

      // bottom
      renderer.Drawimage(_img, x, y + _listBorder + centerh, 0, 0, xoff, ih - _listBorder, _listBorder, _listBorder);
      renderer.Drawimage(_img, x + _listBorder, y + _listBorder + centerh, centerw, _listBorder, xoff + _listBorder, ih - _listBorder, iw - (_listBorder + _listBorder) - xoff, _listBorder, true);
      renderer.Drawimage(_img, x + _listBorder + centerw, y + _listBorder + centerh, 0, 0, iw - _listBorder, ih - _listBorder, _listBorder, _listBorder);

      if (_drawScroll) {
         // scrollbar bg
         renderer.Drawimage(_img, Right() - _scrollWidth - _listBorder, y + _scrollWidth, _scrollWidth, height - _scrollWidth - _scrollWidth, _scrollWidth, _scrollWidth + _scrollWidth + _scrollWidth, _scrollWidth, _highlightHeight, true);

         // scrollbar buttons
         if (_state == UpScroll)  {
            renderer.Drawimage(_img, Right() - _scrollWidth - _listBorder, y + _listBorder, _scrollWidth, _scrollWidth, 0, _scrollWidth, _scrollWidth, _scrollWidth);
            renderer.Drawimage(_img, Right() - _scrollWidth - _listBorder, Bottom() - _scrollWidth - _listBorder, _scrollWidth, _scrollWidth, _scrollWidth, 0, _scrollWidth, _scrollWidth);
         } else if (_state == DownScroll)  {
            renderer.Drawimage(_img, Right() - _scrollWidth - _listBorder, y + _listBorder, _scrollWidth, _scrollWidth, 0, 0, _scrollWidth, _scrollWidth);
            renderer.Drawimage(_img, Right() - _scrollWidth - _listBorder, Bottom() - _scrollWidth - _listBorder, _scrollWidth, _scrollWidth, _scrollWidth, _scrollWidth, _scrollWidth, _scrollWidth);
         } else {
            renderer.Drawimage(_img, Right() - _scrollWidth - _listBorder, y + _listBorder, _scrollWidth, _scrollWidth, 0, 0, _scrollWidth, _scrollWidth);
            renderer.Drawimage(_img, Right() - _scrollWidth - _listBorder, Bottom() - _scrollWidth - _listBorder, _scrollWidth, _scrollWidth, _scrollWidth, 0, _scrollWidth, _scrollWidth);
         }

         // scroll bar
         if (_state == ScrollGrab)  {
            renderer.Drawimage(_img, Right() - _scrollWidth - _listBorder, y + _listBorder + _scrollWidth + _scrollVal, _scrollWidth, _scrollWidth, _scrollWidth, _scrollWidth + _scrollWidth, _scrollWidth, _scrollWidth);
         }  else  {
            renderer.Drawimage(_img, Right() - _scrollWidth - _listBorder, y + _listBorder + _scrollWidth + _scrollVal, _scrollWidth, _scrollWidth, 0, _scrollWidth + _scrollWidth, _scrollWidth, _scrollWidth);
         }
      }

      // items
      if (_items.size() && _font)  {
         renderer.Setclip(x + _listBorder, y + _listBorder, width - _listBorder - _listBorder - _scrollWidth, height - _listBorder - _listBorder);

         int startItem = (int) ((_scrollVal / (float) (_scrollHeight - _scrollWidth)) * _items.size());
         int endItem = startItem + (height / _itemHeight);
         if (endItem >= _items.size()) endItem = _items.size() - 1;

         ListItem * item = NULL;

         for (int i = startItem; i <= endItem; i++)  {
            item = _items.at(i);
            if (!item) continue;

            if (_selectedIndex == i)
               renderer.Fillrect(x + _listBorder, y + _listBorder + (i - startItem) * _itemHeight, width - _listBorder - _listBorder - ((_drawScroll) ? _scrollWidth : 0), _itemHeight, Color::DarkBrown);
            
            if (item->Icon != -1)  {

               renderer.Drawimage(item->Icon, x + _listBorder, y + _listBorder + (i - startItem) * _itemHeight, item->IconSize, item->IconSize, item->IconTU, item->IconTV, item->IconSize, item->IconSize);
               _font->Draw(renderer, item->Text, x + _listBorder + item->IconSize + ICON_PADDING, y + _listBorder + (i - startItem) * _itemHeight);

            }  else  {

               _font->Draw(renderer, item->Text, x + _listBorder, y + _listBorder + (i - startItem) * _itemHeight);

            }

            
         }

         renderer.Resetclip();
      }
   }

   void ListBox::AddItem(const std::string & text, IMAGEHANDLE icon, int iconSize, int indexX, int indexY)  {
      ListItem * temp = new ListItem();
      temp->Text = text;
      temp->Icon = icon;
      temp->IconTU = indexX * iconSize;
      temp->IconTV = indexY * iconSize;

      if (icon != -1)  {
         if (iconSize > 0)  {
            temp->IconSize = iconSize;
         }  else  {
            const Image * img = ImageLoader::GetImage(icon);
            temp->IconSize = (img) ? img->Height() : 0;
         }
      }

      if (iconSize > _itemHeight) {
         _itemHeight = iconSize;
      }

      if (_itemHeight * _items.size() >= Height())  {
         _drawScroll = true;
      }

      _items.push_back(temp);
   }
   
   ListItem ListBox::GetItem(int index) const  {
      if (index < 0 || index >= (int) _items.size())
         return ListItem();

      return *(_items.at(index));
   }

   void ListBox::MoveItem(int startIndex, int moveLocation)  {
   }
}
