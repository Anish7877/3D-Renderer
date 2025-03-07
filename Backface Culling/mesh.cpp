#include "mesh.h"
#include "triangle.h"
#include "vector.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

mesh_t mesh{};
vec3_t cube_vertices[NO_CUBE_VERTICES]
{
    {-1.0f,-1.0f,-1.0f},
    {-1.0f,1.0f,-1.0f},
    {1.0f,1.0f,-1.0f},
    {1.0f,-1.0f,-1.0f},
    {1.0f,1.0f,1.0f},
    {1.0f,-1.0f,1.0f},
    {-1.0f,1.0f,1.0f},
    {-1.0f,-1.0f,1.0f}
};
face_t cube_faces[NO_CUBE_FACES]
{
    //front
    {1,2,3},
    {1,3,4},
    //right
    {4,3,5},
    {4,5,6},
    //back
    {6,5,7},
    {6,7,8},
    //left
    {8,7,2},
    {8,2,1},
    //top
    {2,5,7},
    {2,5,3},
    //bottom
    {6,8,1},
    {6,1,4}
};

void load_cube_mesh()
{
    for(int i{0};i<NO_CUBE_VERTICES;++i)
    {
        vec3_t cube_vertex{cube_vertices[i]};
        mesh.vertices.push_back(cube_vertex);
    }
    for(int i{0};i<NO_CUBE_FACES;++i)
    {
        face_t cube_face{cube_faces[i]};
        mesh.faces.push_back(cube_face);
    }
}
void load_obj_file(const std::string& filename)
{
    std::ifstream obj_file{filename};
    if (!obj_file.is_open())
    {
        std::cerr << "File Not Found" << '\n';
        return;
    }

    std::string line;
    while (std::getline(obj_file, line))
    {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v")
        {
            vec3_t vertex;
            if (iss >> vertex.m_x >> vertex.m_y >> vertex.m_z)
            {
                mesh.vertices.push_back(vertex);
            }
        }
        else if (prefix == "f")
        {
            face_t face;
            std::string vertex_data;
            int vertex_indices[3];

            for (int i = 0; i < 3; i++)
            {
                if (iss >> vertex_data)
                {
                    size_t slash_pos = vertex_data.find('/');
                    if (slash_pos != std::string::npos)
                    {
                        vertex_data = vertex_data.substr(0, slash_pos);
                    }
                    vertex_indices[i] = std::stoi(vertex_data);
                }
            }

            face = {vertex_indices[0], vertex_indices[1], vertex_indices[2]};
            mesh.faces.push_back(face);
        }
    }
}
