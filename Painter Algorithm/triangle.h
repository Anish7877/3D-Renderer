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
        float avg_depth{};
        triangle_t() = default;
        triangle_t(const vec2_t* projected_points,float avg_depth) : avg_depth{avg_depth}
        {
            for(int i{0};i<3;++i)
            {
                points[i] = projected_points[i];
            }
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
