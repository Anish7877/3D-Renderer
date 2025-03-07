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
        void setX(float x)
        {
            m_x = x;
        }
        void setY(float y)
        {
            m_y = y;
        }
        float getX() const
        {
            return m_x;
        }
        float getY() const
        {
            return m_y;
        }
};
class vec3_t
{
    private : 
        float m_x;
        float m_y;
        float m_z;
    public:
        vec3_t()
        {}
        vec3_t(float x,float y,float z) : m_x{x},m_y{y},m_z{z}
        {}
        void setX(float);
        void setY(float);
        void setZ(float);
        float getX() const;
        float getY() const;
        float getZ() const;
        static vec3_t rotate_point_x(const vec3_t&,float);
        static vec3_t rotate_point_y(const vec3_t&,float);
        static vec3_t rotate_point_z(const vec3_t&,float);
};
#endif
