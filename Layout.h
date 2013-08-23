#pragma once

#include "Control.h"

namespace GUI  {

   enum SpacerType  {
      HorizontalSpacer,
      VerticalSpacer,
      FixedSpacer
   };

   // Available layout options
   enum Layouts {
      None,
      Grid,
      HorizontalLine,
      VerticalLine
   };

   // Holds a configuration of controls and controls positioning
   class Layout : public Control, public IContainer {
   public:
      Layout(int x, int y, unsigned int wide, unsigned int tall, int padding, Layouts layout = None, ALIGN align = Top | Left);
      virtual ~Layout();

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      void AddSpacer(SpacerType type, int wide = 0, int tall = 0);

      inline void RefreshLayout() {_layoutChanged = true;}
      inline void SetLayout(Layouts layout) {_layout = layout; _layoutChanged = true;}
      inline void SetAlignment(ALIGN align) {_align = align; _layoutChanged = true;}
      inline void SetPadding(int pad) {_padding = pad; _layoutChanged = true;}
      inline int  GetPadding() const {return _padding;}

      // overrides
      inline void AddChild(Control * control) {_layoutChanged = true; IContainer::AddChild(control);}
      inline void Move(int xpos, int ypos) {x = xpos; y = ypos; _layoutChanged = true;}
      inline void Resize(unsigned int wide, unsigned int tall) {width = wide; height = tall; _layoutChanged = true;}
      inline void Resize(float scale) {if (scale < 0) return; width = (unsigned int)((float) width * scale); height = unsigned int((float) height * scale); _layoutChanged = true;}

      inline void SetWidth(unsigned int wide) {width = wide; _layoutChanged = true;}
      inline void SetHeight(unsigned int tall) {height = tall; _layoutChanged = true;}
      inline void SetX(int newx) {x = newx; _layoutChanged = true;}
      inline void SetY(int newy) {y = newy; _layoutChanged = true;}

   protected:
      // Moves a child control to a new relative X and Y using the current alignment
      //  newX is the left side x in Left alignment, and the distance from the right in Right alignment
      //  newY is the top side y in Top alignment, and the distance from the bottom in Bottom alignment
      //  In Center alignment newX and newY defines the center point
      void _moveChildRelative(Control * control, int newX, int newY);

      bool _layoutChanged;
      int _padding;
      ALIGN _align;
      Layouts _layout;

   private:

      class layoutSpacer : public Control  {
      public:
         layoutSpacer(unsigned int wide, unsigned int tall);
         virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);
      };
   };

}
