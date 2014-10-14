#ifndef PHOSPHORUS_ENTITY_HPP11_INCLUDED
#define PHOSPHORUS_ENTITY_HPP11_INCLUDED

#include <string>
#include "timer.hpp"

namespace phosphorus
{
    class entity
    {
    private:
        GLvector3 m_coordinates;
        size_t m_id;
        timer  m_lifetime;
        
        entity_type m_type;
        
        bool m_expired;
        bool m_visible;
        bool m_solid;
    public:
        entity(const bool visible, const bool solid, const size_t lifetime);
        virtual ~entity() { }
        
        void set_coordinates(const double x, const double y, const double z);
        void set_x(const double x);
        void set_y(const double y);
        void set_z(const double z);
        
        size_t id() const { return m_id; }
        
        virtual void update() = 0;
        virtual void draw()   = 0;
        virtual void animate() = 0;
        
        bool expired() const { return m_expired; }
        void set_expired(const bool expired)   { m_expired = expired; }
        
        bool visible() const { return m_visible; }
        void set_visibility(const bool visible) { m_visible = visible; }
        
        bool solid() const { return m_solid; }
        void set_solid(const bool solid) { m_solid = solid; }
        
        entity_type type() const { return m_type; }
    };
}

#endif // PHOSPHORUS_ENTITY_HPP11_INCLUDED
