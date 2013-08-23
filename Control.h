#pragma once

#include <vector>
#include "Renderer.h"
#include "ActionMap.h"
#include "Exception.h"
#include "Event.h"

namespace GUI  {

   typedef unsigned char ALIGN;

   // Alignment modes
   enum Align : unsigned char {
      Center = 1,
      Top    = Center << 1,
      Left   = Top << 1,
      Right  = Left << 1,
      Bottom = Right << 1
   };

   // Control
   // Provides base implementation for all gui objects
   class Control  {
   public:
      virtual ~Control();
      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed) = 0;

      virtual Control * Clone();

      // Alignment functions:
      //  AlignTo functions align this control to a position inside the specified area
      //  AlignNear aligns to a position on one of the four sides of the specified area
      void AlignToRect(ALIGN alignment, int padding, SDL_Rect & rect);
      void AlignToRect(ALIGN alignment, int padding, int xpos, int ypos, unsigned int w, unsigned int h);
      void AlignToControl(ALIGN alignment, int padding, const Control & control);
      void AlignNear(int xpos, int ypos, unsigned int w, unsigned int h, int distance, Align position);
      void AlignNear(const Control & control, int distance, Align position);

      inline void Move(int xpos, int ypos) {x = xpos; y = ypos;}
      inline void Resize(unsigned int wide, unsigned int tall) {width = wide; height = tall;}
      inline void Resize(float scale) {if (scale < 0) return; width = (unsigned int) ((float)width * scale); height = (unsigned int) ((float) height * scale);}

      inline unsigned int Width() const {return width;}
      inline void SetWidth(unsigned int wide) {width = wide;}
      inline unsigned int Height() const {return height;}
      inline void SetHeight(unsigned int tall) {height = tall;}
      inline int X() const {return x;}
      inline void SetX(int newx) {x = newx;}
      inline int Y() const {return y;}
      inline void SetY(int newy) {y = newy;}

      inline int Bottom() {return y + height;}
      inline int Right() {return x + width;}

      inline bool Enabled() const {return enabled;}
      inline void SetEnabled(bool en) {enabled = en;}
      inline bool Visible() const {return visible;}
      inline void SetVisible(bool vis) {visible = vis;}
      inline bool Dirty() const {return dirty;}
      inline bool SetDirty(bool dir) {dirty = dir;}

   protected:
      Control();
      Control(int xpos, int ypos, unsigned int wide, unsigned int tall);
      virtual bool Collide(int mx, int my);

      bool enabled;
      bool visible;
      bool dirty;

      int x;
      int y;
      unsigned int width;
      unsigned int height;

   };

   // Indicates this control is a container
   class IContainer  {
   public:
      virtual ~IContainer();
      void AddChild(Control * control);
      void UpdateChildren(const ActionMap & actions, unsigned int tElapsed);
      void DrawChildren(RenderDevice::Renderer& renderer, unsigned int tElapsed);
      
      inline Control * GetChild(unsigned int index) { if (index >= _children.size()) return NULL; return _children.at(index);}
      inline int GetNumChildren() const {return (int) _children.size();}

   protected:
      IContainer() {}
      std::vector<Control *> _children;

   private:
   };

   // Provides click and hovering callbacks
   class IClickable  {
   public:
      virtual ~IClickable() {}
      inline void OnClick(void (*onClick) (Control*)) {_onClick = onClick;}
      inline void OnHover(void (*onHover) (Control*)) {_onHover = onHover;}

   protected:
      IClickable() {_onClick = 0; _onHover = 0;}
      void (*_onClick) (Control*);
      void (*_onHover) (Control*);
   };

   // Provides mousedown/mouseup callbacks
   class IDraggable  {
   public:
      virtual ~IDraggable() {}
      inline void OnMouseDown(void (*onMouseDown) (Control*)) {_onMouseDown = onMouseDown;}
      inline void OnMouseUp(void (*onMouseUp) (Control *)) {_onMouseUp = onMouseUp;}
      inline bool IsDragging() {return _isDragging;}

   protected:
      IDraggable() {_onMouseDown = 0; _onMouseUp = 0; _isDragging = false;}
      void (*_onMouseDown) (Control *);
      void (*_onMouseUp) (Control *);
      bool _isDragging;
   };

}