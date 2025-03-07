#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vector.h"
class face_t
{
    public :
        int m_a{};
        int m_b{};
        int m_c{};
};
class triangle_t
{
    private :
        vec2_t points[3];
    public :
        triangle_t()
        {}
        triangle_t(const vec2_t& a,int i)
        {
            points[i] = a;
        }
        vec2_t getPoint0()
        {
            return points[0];
        }
        vec2_t getPoint1()
        {
            return points[1];
        }
        vec2_t getPoint2()
        {
            return points[2];
        }
};
#endif
