//
//  GraphicContext.h
//  NewProject
//
//  Created by Osmely Fernandez on 30/8/16.
//
//

#ifndef GraphicContext_h
#define GraphicContext_h

#include "agg.h"
#include "BasicDraw.h"


class AGGGraphicContext {

public:

    AGGGraphicContext():
    buffer(nullptr),
    render(nullptr),
    _backColor(agg::rgba8(255, 255, 255)),
    _internal_buf(nullptr),
    _proc(false)
    {

    }

    bool beginContext(int w, int h, const agg::rgba8 &color = agg::rgba8(255, 255, 255)){
        if(_proc)
            return false;
        _proc = true;

        setBackgroudColor(color);

        _internal_buf = new unsigned char[w * h * 3];
        buffer = new agg::rendering_buffer(_internal_buf, w, h, w * 3);
        render = new agg::renderer<agg::span_rgb24>(*buffer);

        rasterizer.gamma(1.3);
        rasterizer.filling_rule(agg::fill_even_odd);
        render->clear(_backColor);

        _proc = false;
        return true;
    }

    void clearContext(){
        if(_internal_buf != nullptr){
            delete [] _internal_buf;
            _internal_buf = nullptr;
        }

        if(buffer != nullptr){
            delete buffer;
            buffer = nullptr;
        }

        if(render != nullptr){
            delete render;
            render = nullptr;
        }
    }

    void setBackgroudColor(const agg::rgba8 &color){
        _backColor = color;
    }

    void fill_ellipse(double x,  double y,
                      double rx, double ry, const agg::rgba8 &color){
        AGGScript::BasicDraw::fill_ellipse(rasterizer, x, y, rx, ry, 1);
        rasterizer.render(*render, color);
    }

    void fill_line(double x1, double y1,
                   double x2, double y2,
                   double width, const agg::rgba8 &color){
        AGGScript::BasicDraw::fill_line(rasterizer, x1, y1, x2, y2, width);
        rasterizer.render(*render, color);
    }

    void fillRect(double x, double y,
                  double w, double h, const agg::rgba8 &color){
        AGGScript::BasicDraw::fillRect(rasterizer, x, y, w, h);
        rasterizer.render(*render, color);
    }

    void draw_rect(double x, double y,
                   double w, double h, const agg::rgba8 &color){
        AGGScript::BasicDraw::draw_rect(rasterizer, x, y, w, h);
        rasterizer.render(*render, color);
    }

    void draw_ellipse(double x,  double y,
                      double rx, double ry, const agg::rgba8 &color){
        AGGScript::BasicDraw::draw_ellipse(rasterizer, x, y, rx, ry);
        rasterizer.render(*render, color);
    }


    agg::rendering_buffer *buffer;
    agg::rasterizer rasterizer;
    agg::renderer<agg::span_rgb24> *render;

private:
    agg::rgba8 _backColor;
    unsigned char* _internal_buf;
    bool _proc;

};


#endif /* GraphicContext_h */
