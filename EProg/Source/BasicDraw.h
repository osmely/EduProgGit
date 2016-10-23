//
//  BasicDraw.hpp
//  NewProject
//
//  Created by Osmely Fernandez on 31/8/16.
//
//

#ifndef BasicDraw_h
#define BasicDraw_h

#include "agg.h"
#include <math.h>
#include <stdlib.h>


namespace AGGScript {
    namespace BasicDraw {

        void fill_ellipse(agg::rasterizer& ras,
                          double x,  double y,
                          double rx, double ry, int step = 1);

        void fill_line(agg::rasterizer& ras,
                       double x1, double y1,
                       double x2, double y2,
                       double width);

        void fillRect(agg::rasterizer& ras,
                      double x, double y,
                      double w, double h);

        void draw_rect(agg::rasterizer& ras,
                       double x, double y,
                       double w, double h);

        void draw_ellipse(agg::rasterizer& ras,
                          double x,  double y,
                          double rx, double ry);

    }
}

#endif /* BasicDraw_h */
