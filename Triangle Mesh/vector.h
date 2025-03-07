#ifndef VECTOR_H
#define VECTOR_H
class vec2_t
{
    private :
        float m_x;
        float m_y;
    public :
        vec2_t()
        {}
        vec2_t(float x,float y) : m_x{x},m_y{y}
        {}
        void setX(float x);
        void setY(float y);
        float getX() const;
        float getY() const;
};
class vec3_t
{
    public:
        float m_x;
        float m_y;
        float m_z;
        static vec3_t rotate_point_x(const vec3_t&,float);
        static vec3_t rotate_point_y(const vec3_t&,float);
        static vec3_t rotate_point_z(const vec3_t&,float);
};
#endif
