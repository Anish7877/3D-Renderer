#include "display.h"
#include "triangle.h"
#include "vector.h"
#include "mesh.h"
#include <algorithm>
#include <string_view>

std::vector<triangle_t> triangle_to_render{};
vec3_t camera_position{0.0f,0.0f,0.0f};
constexpr float fov_factor{1280.0f};
bool is_running{false};
int previous_frame_time{};
Render_Mode render_mode{};
Backface_Culling_Mode cull_method{};

bool sort_type(triangle_t t1,triangle_t t2)
{
    return (t1.avg_depth < t2.avg_depth);
}

void setup(std::string_view str)
{
    render_mode = Render_Mode::Wireframe;
    cull_method = Backface_Culling_Mode::On;
    // creation of color buffer
    color_buffer = new std::uint32_t[window_width*window_height];

    // creation of color buffer texture
    color_buffer_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,window_width,window_height);

    if(!color_buffer_texture)
    {
        std::cerr << "Failed to create Color buffer Texture" << '\n';
        color_buffer_texture = nullptr;
    }

    load_obj_file(static_cast<std::string>(str));
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
            if(event.key.keysym.sym == SDLK_1)
            {
                render_mode = Render_Mode::Wireframe;
            }
            if(event.key.keysym.sym == SDLK_2)
            {
                render_mode = Render_Mode::Filled_Triangle;
            }
            if(event.key.keysym.sym == SDLK_3)
            {
                render_mode = Render_Mode::Wireframe_with_filled_triangle;
            }
            if(event.key.keysym.sym == SDLK_c)
            {
                cull_method = Backface_Culling_Mode::On;
            }
            if(event.key.keysym.sym == SDLK_d)
            {
                cull_method = Backface_Culling_Mode::Off;
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

        vec3_t transformed_vertices[3]{};

        for(int j{0};j<3;++j)
        {
            vec3_t transformed_vertex = face_vertices[j];
            transformed_vertex = vec3_t::rotate_point_x(transformed_vertex,mesh.rotation.m_x);
            transformed_vertex = vec3_t::rotate_point_y(transformed_vertex,mesh.rotation.m_y);
            transformed_vertex = vec3_t::rotate_point_z(transformed_vertex,mesh.rotation.m_z);

            transformed_vertex.m_z -= 5.0f;
            transformed_vertices[j] = transformed_vertex;
        }
        if(cull_method == Backface_Culling_Mode::On)
        {
            vec3_t vector_a{transformed_vertices[0]};
            vec3_t vector_b{transformed_vertices[1]};
            vec3_t vector_c{transformed_vertices[2]};

            vec3_t vector_ab{vec3_t::sub(vector_b,vector_a)};
            vec3_t vector_ac{vec3_t::sub(vector_c,vector_a)};
            vec3_t::normalize(vector_ab);
            vec3_t::normalize(vector_ac);

            vec3_t normal{vec3_t::cross_product(vector_ab,vector_ac)};
            vec3_t::normalize(normal);
            vec3_t camera_ray{vec3_t::sub(camera_position,vector_a)};
            vec3_t::normalize(camera_ray);
            float dot_product{vec3_t::dot_product(camera_ray,normal)};

            if(dot_product < 0.0f)
            {
                continue;
            }
        }
        vec2_t projected_points[3]{};
        for(int k{0};k<3;++k)
        {
            vec2_t projected_point{project(transformed_vertices[k])};
            projected_point.setX(projected_point.getX() + static_cast<float>(window_width)/2);
            projected_point.setY(projected_point.getY() + static_cast<float>(window_height)/2);
            projected_points[k] = projected_point;
        }

        float avg_depth{(transformed_vertices[0].m_z+transformed_vertices[1].m_z+transformed_vertices[2].m_z)/3.0f};

        projected_triangle = triangle_t(projected_points,avg_depth);

        triangle_to_render.push_back(projected_triangle);
    }
    std::sort(triangle_to_render.begin(),triangle_to_render.end(),sort_type);
    for(int i{0};i < static_cast<int>(triangle_to_render.size());++i)
    {
        std::cout << triangle_to_render[i].avg_depth << '\n';
    }
}

void render()
{
    int num_triangles{static_cast<int>(triangle_to_render.size())};

    for(int i{0};i<num_triangles;++i)
    {
        triangle_t triangle{triangle_to_render[i]};
        if(render_mode == Render_Mode::Filled_Triangle || render_mode == Render_Mode::Wireframe_with_filled_triangle)
        {
            draw_filled_triangle
                (
                 triangle.getPoint0().getX(),triangle.getPoint0().getY(),
                 triangle.getPoint1().getX(),triangle.getPoint1().getY(),
                 triangle.getPoint2().getX(),triangle.getPoint2().getY(),
                 0xFF555555
                );
        }
        if(render_mode == Render_Mode::Wireframe || render_mode == Render_Mode::Wireframe_with_filled_triangle)
        {
            draw_triangle
                (
                 triangle.getPoint0().getX(),triangle.getPoint0().getY(),
                 triangle.getPoint1().getX(),triangle.getPoint1().getY(),
                 triangle.getPoint2().getX(),triangle.getPoint2().getY(),
                 0xFFFFFFFF
                );
        }
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

int main(int agrc, char*argv[])
{
    is_running = initialize_window();

    setup(argv[1]);

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
