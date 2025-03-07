#include "display.h"
#include "triangle.h"
#include "vector.h"
#include "mesh.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdint>

std::vector<triangle_t> triangle_to_render;
vec3_t camera_position{0.0f,0.0f,-5.0f};
constexpr float fov_factor{1280.0f};
bool is_running{false};
int previous_frame_time{};

void setup()
{
    // creation of color buffer
    color_buffer = new std::uint32_t[window_width*window_height];

    // creation of color buffer texture
    color_buffer_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,window_width,window_height);

    load_obj_file("../assets/f22.obj");
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
        point.m_x*fov_factor/point.m_z,
        point.m_y*fov_factor/point.m_z
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
    mesh.rotation.m_x = mesh.rotation.m_x+0.01f;
    mesh.rotation.m_y = mesh.rotation.m_y+0.01f;
    mesh.rotation.m_z = mesh.rotation.m_z+0.01f;

    triangle_t projected_triangle{};

    int num_faces{static_cast<int>(mesh.faces.size())};
    for(int i{0};i<num_faces;++i)
    {
        face_t mesh_face{mesh.faces[i]};

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.m_a-1];
        face_vertices[1] = mesh.vertices[mesh_face.m_b-1];
        face_vertices[2] = mesh.vertices[mesh_face.m_c-1];

        for(int j{0};j<3;++j)
        {
            vec3_t transformed_vertex{vec3_t::rotate_point_x(face_vertices[j],mesh.rotation.m_x)};

            transformed_vertex.m_z = camera_position.m_z - transformed_vertex.m_z;

            vec2_t projected_point{project(transformed_vertex)};
            projected_point.setX(projected_point.getX() + (static_cast<float>(window_width)/2));
            projected_point.setY(projected_point.getY() + (static_cast<float>(window_height)/2));
            projected_triangle = triangle_t(projected_point,j);
        }
        triangle_to_render.push_back(projected_triangle);
    }
}

void render()
{
    draw_grid();

    int num_triangles{static_cast<int>(triangle_to_render.size())};

    for(int i{0};i<num_triangles;++i)
    {
        triangle_t triangle{triangle_to_render[i]};
        draw_triangle
            (
             triangle.getPoint0().getX(),triangle.getPoint0().getY(),
             triangle.getPoint1().getX(),triangle.getPoint1().getY(),
             triangle.getPoint2().getX(),triangle.getPoint2().getY()
            );
    }
    triangle_to_render.clear();
    render_color_buffer();
    clear_color_buffer(0xFF000000);
    SDL_RenderPresent(renderer);
}

void free_resources()
{
    mesh.vertices.clear();
    mesh.faces.clear();
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
    free_resources();
    return 0;
}
