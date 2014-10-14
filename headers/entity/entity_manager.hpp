/*
 * Christopher Di Bella
 * Keane Chan, Ervin Macrohon, Timothy Masters
 *
 * 2014, September 16
 *
 * phosphorus.hpp
 * Interface for the engine core
 */
#ifndef PHOSPHORUS_HID_HPP11_INCLUDED
#define PHOSPHORUS_HID_HPP11_INCLUDED

#include <map>
#include <unordered_set>
#include <vector>

namespace phosphorus
{
    class entity;
    
    class entity_manager
    {
    private:
        typedef std::map<size_t, entity*> entity_map;
                
        size_t m_index;
        std::set<size_t> m_removedIndicies;
        
        entity_map m_database;
        
        entity_manager(const entity_manager&)            = delete;
        entity_manager(entity_manager&&)                 = delete;
        entity_manager& operator=(const entity_manager&) = delete;
        entity_manager& operator=(entity_manager&&)      = delete
    public:
        entity_manager();
        ~entity_manager();
        
        std::pair<size_t, entity_map::iterator> insert_entity(entity* entity);
        
        void remove_entity(entity* entity);
        void remove_entity(size_t id);
        void remove_selected(const std::vector<size_t>& ids);
        void remove_unselected(const std::unordered_set<size_t>& ids);
        
        void update();
        void cleanup();
        void draw();
    };
}

#endif // PHOSPHORUS_HID_HPP11_INCLUDED

//I'll push my entity, but there's not much to it atm. I'm thinking your physical object might be a subclass of my entity (since there might not be a need for some things to be 'physical'). My entity is an abstract class though, so you'll probably want to implement the bits that I haven't, if only so your code compiles :)
