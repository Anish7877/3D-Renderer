#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vector.h"
class face_t
{
    private :
        int m_a{};
        int m_b{};
        int m_c{};
    public :
        face_t()
        {}
        face_t(int a,int b,int c) : m_a{a},m_b{b},m_c{c}
        {}
        int getA() const
        {
            return m_a;
        }
        int getB() const
        {
            return m_b;
        }
        int getC() const
        {
            return m_c;
        }
        void setA(int a)
        {
            m_a = a;
        }
        void setB(int b)
        {
            m_b = b;
        }
        void setC(int c)
        {
            m_c = c;
        }
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
