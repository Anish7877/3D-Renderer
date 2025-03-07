#include "display.h"
#include "vector.h"
#include <SDL2/SDL_timer.h>

const int no_points = 9*9*9;
vec3_t cube_points[no_points];
vec2_t projected_points[no_points];
vec3_t camera_position{0.0f,0.0f,-5.0f};
vec3_t cube_rotation{0.0f,0.0f,0.0f};
const float fov_factor{640.0f};
bool is_running{false};
int previous_frame_time{};

void setup()
{
    // creation of color buffer
    color_buffer = new std::uint32_t[window_width*window_height];

    // creation of color buffer texture
    color_buffer_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,window_width,window_height);

    // start loading array of points
    int point_count{0};
    for(float i{-1};i<=1;i+=0.25f)
    {
        for(float j{-1};j<=1;j+=0.25f)
        {
            for(float k{-1};k<=1;k+=0.25f)
            {
                vec3_t newVec{i,j,k};
                cube_points[point_count++] = newVec;
            }
        }
    }
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                is_running = false;
            }
            break;
    }
}

vec2_t project(const vec3_t& point)
{
    vec2_t projected_point{
        point.getX()*fov_factor/point.getZ(),
        point.getY()*fov_factor/point.getZ()
    };
    return projected_point;
}

void update()
{
    cube_rotation.setX(cube_rotation.getX()+0.001f);
    cube_rotation.setY(cube_rotation.getY()+0.001f);
    cube_rotation.setZ(cube_rotation.getZ()+0.001f);
    for(int i{0};i<no_points;++i)
    {
        vec3_t point = cube_points[i];

        vec3_t transformed_point{vec3_t::rotate_point_x(point,cube_rotation.getX())};
        transformed_point = vec3_t::rotate_point_y(transformed_point, cube_rotation.getY());
        transformed_point = vec3_t::rotate_point_z(transformed_point, cube_rotation.getZ());

        transformed_point.setZ(transformed_point.getZ() - camera_position.getZ());

        vec2_t projected_point{project(transformed_point)};

        projected_points[i] = projected_point;
    }
}

void render()
{
    draw_grid();

    // render projected points
    for(int i{0};i<no_points;++i)
    {
        vec2_t projected_point{projected_points[i]};
        draw_rect(
            projected_point.getX() + static_cast<float>(window_width)/2,
            projected_point.getY() + static_cast<float>(window_height)/2,
            4,
            4,
            0xFFFF0000
            );
    }
    render_color_buffer();
    clear_color_buffer(0xFF000000);
    SDL_RenderPresent(renderer);
}

int main()
{
    is_running = initialize_window();

    setup();

    while(is_running)
    {
        process_input();
        update();
        render();
    }
    destroy_window();
    return 0;
}
