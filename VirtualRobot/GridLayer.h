//GridLayer.h
//*****************************************************************************
//Draws the map grid
//*****************************************************************************

#ifndef GRID_LAYER_H_DEFINED
#define GRID_LAYER_H_DEFINED

#include "Layer.h"

namespace Beeber
{

class GridLayer : public Layer
{
   public:
      GridLayer();
      virtual ~GridLayer();

      virtual void OnDraw();

   private:
      void         DrawGrid();
      void         DrawHorizontalAt(double y);
      void         DrawHorizontals();
      void         DrawHorizontalTicLabel(XYPoint p);
      void         DrawLabel(DevicePoint p, string label);
      void         DrawVerticalAt(double x);
      void         DrawVerticals();
      void         DrawVerticalTicLabel(XYPoint p);
      bool         HasScaleChangedSinceLastRender();
      XYPoint      InitialCenter(){return (_initialCenter);}
      void         InitialCenter(XYPoint p){_initialCenter = p;}
      double       LastKnownScale(){return (_lastKnownScale);}
      void         LastKnownScale(double lastKnownScale){_lastKnownScale = lastKnownScale;}
      double       SpacingOfTicMarksInXYUnits();
      void         UpdateDataNeededByRenderingAlgorithm();

   private:
      XYPoint      _initialCenter;
      double       _lastKnownScale;
};

};

#endif
