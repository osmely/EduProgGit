//
//  BasicDraw.cpp
//  NewProject
//
//  Created by Osmely Fernandez on 31/8/16.
//
//

#include <stdio.h>
#include "BasicDraw.h"



static int MAX_INT(int a, int b){
    return a >= b ? a : b;
}

static int MIN_INT(int a, int b){
    return a <= b ? a : b;
}

double random(double min, double max){
    int r = (rand() << 15) | rand();
    return ((r & 0xFFFFFFF) / double(0xFFFFFFF + 1)) * (max - min) + min;
}


namespace AGGScript {
    namespace BasicDraw {



        void fill_ellipse(agg::rasterizer& ras,
                          double x,  double y,
                          double rx, double ry, int step)
        {
            int i;
            step = MAX_INT(MIN_INT(step, 360), 3);
            ras.move_to_d(x + rx, y);
            for(i = 1; i < 360; i+=step){
                double a = double(i) * 3.1415926 / 180.0;
                ras.line_to_d(x + cos(a) * rx, y + sin(a) * ry);
            }
        }

        void fill_line(agg::rasterizer& ras,
                       double x1, double y1,
                       double x2, double y2,
                       double width)
        {

            double dx = x2 - x1;
            double dy = y2 - y1;
            double d = sqrt(dx*dx + dy*dy);

            dx = width * (y2 - y1) / d;
            dy = width * (x2 - x1) / d;

            ras.move_to_d(x1 - dx,  y1 + dy);
            ras.line_to_d(x2 - dx,  y2 + dy);
            ras.line_to_d(x2 + dx,  y2 - dy);
            ras.line_to_d(x1 + dx,  y1 - dy);

        }

        void fillRect(agg::rasterizer& ras,
                      double x, double y,
                      double w, double h){

            fill_line(ras, x, y + h/2, x + w, y + h/2, h/2);
        }

        void draw_rect(agg::rasterizer& ras,
                       double x, double y,
                       double w, double h)
        {


            double linew = 10;

            ras.filling_rule(agg::fill_non_zero);

            fill_line(ras, x, y, x + w, y, linew);
            fill_line(ras, x + w, y - linew, x + w,  y + h + linew, linew);
            fill_line(ras, x + w, y + h, x,  y + h, linew);
            fill_line(ras, x,  y + h + linew, x, y - linew, linew);

        }


        void draw_ellipse(agg::rasterizer& ras,
                          double x,  double y,
                          double rx, double ry)
        {
            int i;
            ras.move_to_d(x + rx, y);

            double lastx = x + rx;
            double lasty = y;

            for(i = 0; i <= 360; i+=30)
            {
                double a = double(i) * 3.1415926 / 180.0;

                double nx = x + cos(a) * rx;
                double ny = y + sin(a) * ry;
                fill_line(ras, lastx, lasty, nx, ny, 20);

                lastx = nx;
                lasty = ny;
            }
        }



    }
}

