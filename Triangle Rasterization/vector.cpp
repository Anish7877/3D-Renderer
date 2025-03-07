#include "vector.h"
#include <cmath>

// vec2_t Definitions

void vec2_t::setX(float x)
{
    m_x = x;
}
void vec2_t::setY(float y)
{
    m_y = y;
}
float vec2_t::getX() const
{
    return m_x;
}
float vec2_t::getY() const
{
    return m_y;
}
float vec2_t::length(vec2_t v)
{
    return sqrt(static_cast<double>(v.m_x*v.m_x+v.m_y*v.m_y));
}
vec2_t vec2_t::add(vec2_t v1, vec2_t v2)
{
    return vec2_t(v1.m_x+v2.m_x,v1.m_y+v2.m_y);
}
vec2_t vec2_t::sub(vec2_t v1, vec2_t v2)
{
    return vec2_t(v1.m_x-v2.m_x,v1.m_y-v2.m_y);
}
vec2_t vec2_t::multiply_scalar(vec2_t v, float scalar)
{
    return vec2_t(v.m_x*scalar,v.m_y*scalar);
}
vec2_t vec2_t::divide_scalar(vec2_t v, float scalar)
{
    return vec2_t(v.m_x/scalar,v.m_y/scalar);
}
float vec2_t::dot_product(vec2_t v1, vec2_t v2)
{
    return v1.m_x*v2.m_x+v1.m_y*v2.m_y;
}
void vec2_t::normalize(vec2_t &v)
{
    float len{length(v)};
    v.m_x = v.m_x/len;
    v.m_y = v.m_y/len;
    return;
}

//vec3_t Definitions

vec3_t vec3_t::rotate_point_x(const vec3_t& point,float angle)
{
    vec3_t rotated_point
    {
        point.m_x,
        point.m_y*static_cast<float>(cos(angle)) - point.m_z*static_cast<float>(sin(angle)),
        point.m_z*static_cast<float>(cos(angle)) + point.m_y*static_cast<float>(sin(angle))
    };
    return rotated_point;
}
vec3_t vec3_t::rotate_point_y(const vec3_t& point,float angle)
{
    vec3_t rotated_point
    {
        point.m_x*static_cast<float>(cos(angle)) - point.m_z*static_cast<float>(sin(angle)),
        point.m_y,
        point.m_z*static_cast<float>(cos(angle)) + point.m_x*static_cast<float>(sin(angle))
    };
    return rotated_point;
}
vec3_t vec3_t::rotate_point_z(const vec3_t& point,float angle)
{
    vec3_t rotated_point
    {
        point.m_x*static_cast<float>(cos(angle)) - point.m_y*static_cast<float>(sin(angle)),
        point.m_y*static_cast<float>(cos(angle)) + point.m_x*static_cast<float>(sin(angle)),
        point.m_z
    };
    return rotated_point;
}
float vec3_t::length(vec3_t v)
{
    return sqrt(static_cast<double>(v.m_x*v.m_x+v.m_y*v.m_y+v.m_z*v.m_z));
}
vec3_t vec3_t::add(vec3_t v1, vec3_t v2)
{
    return vec3_t(v1.m_x+v2.m_x,v1.m_y+v2.m_y,v1.m_z+v2.m_z);
}
vec3_t vec3_t::sub(vec3_t v1, vec3_t v2)
{
    return vec3_t(v1.m_x-v2.m_x,v1.m_y-v2.m_y,v1.m_z-v2.m_z);
}
vec3_t vec3_t::multiply_scalar(vec3_t v, float scalar)
{
    return vec3_t(v.m_x*scalar,v.m_y*scalar,v.m_z*scalar);
}
vec3_t vec3_t::divide_scalar(vec3_t v, float scalar)
{
    return vec3_t(v.m_x/scalar,v.m_y/scalar,v.m_z/scalar);
}
float vec3_t::dot_product(vec3_t v1, vec3_t v2)
{
    return v1.m_x*v2.m_x+v1.m_y*v2.m_y+v1.m_z*v2.m_z;
}
vec3_t vec3_t::cross_product(vec3_t v1, vec3_t v2)
{
    return vec3_t
        (
         v1.m_y*v2.m_z - v1.m_z*v2.m_y,
         v1.m_z*v2.m_x - v1.m_x*v2.m_z,
         v1.m_x*v2.m_y - v1.m_y*v2.m_x
        );
}
void vec3_t::normalize(vec3_t &v)
{
    float len{length(v)};
    v.m_x = v.m_x/len;
    v.m_y = v.m_y/len;
    v.m_z = v.m_z/len;
    return;
}
