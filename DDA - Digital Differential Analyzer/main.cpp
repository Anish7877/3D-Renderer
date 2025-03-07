#include "display.h"
#include "triangle.h"
#include "vector.h"
#include "mesh.h"
#include <SDL2/SDL_timer.h>
#include <cstdint>

triangle_t triangle_to_render[NO_MESH_FACES];
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
    std::uint32_t time_to_wait{FPS_TARGET_LIMIT - (SDL_GetTicks() - previous_frame_time)};
    if(time_to_wait>=0 && time_to_wait<=FPS_TARGET_LIMIT)
    {
        SDL_Delay(time_to_wait);
    }
    previous_frame_time = SDL_GetTicks();
    cube_rotation.setX(cube_rotation.getX()+0.01f);
    cube_rotation.setY(cube_rotation.getY()+0.01f);
    cube_rotation.setZ(cube_rotation.getZ()+0.01f);

    triangle_t projected_triangle{};
    for(int i{0};i<NO_MESH_FACES;++i)
    {
        face_t mesh_face{mesh_faces[i]};

        vec3_t face_vertices[3];
        face_vertices[0] = mesh_vertices[mesh_face.getA()-1];
        face_vertices[1] = mesh_vertices[mesh_face.getB()-1];
        face_vertices[2] = mesh_vertices[mesh_face.getC()-1];

        for(int j{0};j<3;++j)
        {
            vec3_t transformed_vertex{vec3_t::rotate_point_y(face_vertices[j],cube_rotation.getY())};

            transformed_vertex.setZ(camera_position.getZ() - transformed_vertex.getZ());

            vec2_t projected_point{project(transformed_vertex)};
            projected_point.setX(projected_point.getX() + (static_cast<float>(window_width)/2));
            projected_point.setY(projected_point.getY() + (static_cast<float>(window_height)/2));
            projected_triangle = triangle_t(projected_point,j);
        }
        triangle_to_render[i] = projected_triangle;
    }
}

void render()
{
    for(int i{0};i<NO_MESH_FACES;++i)
    {
        triangle_t triangle{triangle_to_render[i]};
        draw_triangle
            (
             triangle.getPoint0().getX(),
             triangle.getPoint0().getY(),
             triangle.getPoint1().getX(),
             triangle.getPoint1().getY(),
             triangle.getPoint2().getX(),
             triangle.getPoint2().getY()
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
