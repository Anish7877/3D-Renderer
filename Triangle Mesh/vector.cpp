#include "vector.h"
#include <cmath>

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
