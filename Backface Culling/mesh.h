#ifndef MESH_H
#define MESH_H
#include"vector.h"
#include"triangle.h"
#include<string>
#include<vector>
#define NO_CUBE_VERTICES 8
#define NO_CUBE_FACES (6*2)
extern vec3_t mesh_vertices[NO_CUBE_VERTICES];
extern face_t mesh_faces[NO_CUBE_FACES];
struct mesh_t
{
    std::vector<vec3_t> vertices;
    std::vector<face_t> faces;
    vec3_t rotation;
};
extern mesh_t mesh;
void load_cube_mesh();
void load_obj_file(const std::string&);
#endif
