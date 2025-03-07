#ifndef MESH_H
#define MESH_H
#include "vector.h"
#include "triangle.h"
#define NO_MESH_VERTICES 8
#define NO_MESH_FACES (6*2)
extern vec3_t mesh_vertices[NO_MESH_VERTICES];
extern face_t mesh_faces[NO_MESH_FACES];
#endif
