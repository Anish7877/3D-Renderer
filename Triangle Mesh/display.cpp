#include "display.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstdlib>

SDL_Window* window{nullptr};
int window_width{};
int window_height{};
/* SDL Renderer */
SDL_Renderer* renderer{nullptr};

/* Color Buffer */
std::uint32_t* color_buffer{nullptr};

/* SDL Texture */
SDL_Texture* color_buffer_texture{nullptr};

bool initialize_window()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error Initializing SDL\n";
        return false;
    }

    // get current resolution
    SDL_DisplayMode display_mode{};
    SDL_GetCurrentDisplayMode(0,&display_mode);

    window_width = display_mode.w;
    window_height = display_mode.h;

    /* Create SDL Window */
    window = SDL_CreateWindow(NULL,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,window_width,window_height,SDL_WINDOW_BORDERLESS);
    if(!window)
    {
        std::cerr << "Error Creating Window\n";
        SDL_DestroyWindow(window);
        window = nullptr;
        return false;
    }

    /* Create SDL Renderer */
    renderer = SDL_CreateRenderer(window,-1,0);
    if(!renderer)
    {
        std::cerr << "Error Creating Renderer\n";
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
        return false;
    }

    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
    return true;
}

void clear_color_buffer(const std::uint32_t& color)
{
    for(int i{0};i<window_height;++i)
    {
        for(int j{0};j<window_width;++j)
        {
            color_buffer[(window_width*i)+j] = color;
        }
    }
}

void draw_grid()
{
    for(int i{0};i<window_height;i+=10)
    {
        for(int j{0};j<window_width;j+=10)
        {
            if(i%10 == 0 || j%10 == 0)
            {
                color_buffer[(window_width*i)+j] = 0xFF949192;
            }
        }
    }
}

void draw_pixel(const int x,const int y,const std::uint32_t& color)
{
    if(x>=0 && x<window_width && y>=0 && y<window_height)
    {
        color_buffer[(window_width*y)+x] = color;
    }
}

void draw_rect(const int x,const int y,const int width,const int height,const std::uint32_t& color)
{
    for(int i{0};i<width;++i)
    {
        for(int j{0};j<height;++j)
        {
            int current_width = i+x;
            int current_height = j+y;
            draw_pixel(current_width,current_height,color);
        }
    }
}

void draw_line(const int& x0,const int& y0,const int& x1,const int& y1)
{
    int delta_x{x1-x0};
    int delta_y{y1-y0};

    int side_length{abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y)};

    float x_inc{delta_x/static_cast<float>(side_length)};
    float y_inc{delta_y/static_cast<float>(side_length)};

    float current_x{static_cast<float>(x0)};
    float current_y{static_cast<float>(y0)};

    for(int i{0};i<side_length;++i)
    {
        draw_pixel(round(current_x),round(current_y),0xFFFFF0FF);
        current_x += x_inc;
        current_y += y_inc;
    }
}
void draw_triangle(const int& x0,const int& y0,const int& x1,const int& y1,const int& x2,const int& y2)
{
    draw_line(x0,y0,x1,y1);
    draw_line(x1,y1,x2,y2);
    draw_line(x2,y2,x0,y0);
}

void render_color_buffer()
{
    SDL_UpdateTexture(color_buffer_texture,NULL,color_buffer,static_cast<int>(window_width*sizeof(std::uint32_t)));

    SDL_RenderCopy(renderer,color_buffer_texture,NULL,NULL);
}

void destroy_window()
{
    delete []color_buffer;
    color_buffer = nullptr;
    SDL_DestroyTexture(color_buffer_texture);
    color_buffer_texture = nullptr;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}
