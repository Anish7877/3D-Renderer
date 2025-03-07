#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <SDL2/SDL.h>
#include<cstdint>
#define FPS 60
#define FPS_TARGET_LIMIT (1000/FPS)

enum class Backface_Culling_Mode
{
    On,
    Off
};

enum class Render_Mode
{
    Wireframe,
    Filled_Triangle,
    Wireframe_with_filled_triangle
};

extern SDL_Window* window;
extern int window_width;
extern int window_height;
/* SDL Renderer */
extern SDL_Renderer* renderer;

/* Color Buffer */
extern std::uint32_t* color_buffer;

/* SDL Texture */
extern SDL_Texture* color_buffer_texture;
bool initialize_window();
void draw_grid();
void draw_pixel(const int,const int,const std::uint32_t&);
void draw_rect(const int,const int,const int,const int,const std::uint32_t&);
void clear_color_buffer(const std::uint32_t&);
void render_color_buffer();
void destroy_window();
void draw_line(const int&,const int&,const int&,const int&,const std::uint32_t&);
void draw_triangle(const int&,const int&,const int&,const int&,const int&,const int&,const std::uint32_t&);
void draw_flat_bottom_triangle(const int&,const int&,const int&,const int&,const int&,const int&,const std::uint32_t&);
void draw_flat_top_triangle(const int&,const int&,const int&,const int&,const int&,const int&,const std::uint32_t&);
void draw_filled_triangle(int,int,int,int,int,int,const std::uint32_t&);
#endif
