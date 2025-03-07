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
        vec2_t(const vec2_t& v) : m_x{v.m_x},m_y{v.m_y}
        {}
        void setX(float x);
        void setY(float y);
        float getX() const;
        float getY() const;
        static float length(vec2_t v);
        static vec2_t add(vec2_t v1,vec2_t v2);
        static vec2_t sub(vec2_t v1,vec2_t v2);
        static vec2_t multiply_scalar(vec2_t v,float scalar);
        static vec2_t divide_scalar(vec2_t v,float scalar);
        static float dot_product(vec2_t v1,vec2_t v2);
        static void normalize(vec2_t& v);
        ~vec2_t()
        {}
};
class vec3_t
{
    public:
        float m_x;
        float m_y;
        float m_z;
        vec3_t()
        {}
        vec3_t(float x,float y,float z) : m_x{x},m_y{y},m_z{z}
        {}
        static vec3_t rotate_point_x(const vec3_t&,float);
        static vec3_t rotate_point_y(const vec3_t&,float);
        static vec3_t rotate_point_z(const vec3_t&,float);

        static float length(vec3_t v);
        static vec3_t add(vec3_t v1,vec3_t v2);
        static vec3_t sub(vec3_t v1,vec3_t v2);
        static vec3_t multiply_scalar(vec3_t v,float scalar);
        static vec3_t divide_scalar(vec3_t v,float scalar);
        static float dot_product(vec3_t v1,vec3_t v2);
        static vec3_t cross_product(vec3_t v1,vec3_t v2);
        static void normalize(vec3_t& v);

        ~vec3_t()
        {}

};
#endif
