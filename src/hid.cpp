/*
 * Christopher Di Bella
 * Keane Chan, Ervin Macrohon, Timothy Masters
 *
 * 2014, September 16
 *
 * hid.cpp
 * Implementation for human interface devices
 */

#include "../headers/hid.hpp"
#include <cassert>
#include <iostream>
#include <ctime>

namespace
{
    bool instantiated = false;
    
    time_t then, now;
}

namespace phosphorus
{
    GLFWwindow*                                            human_interface_device::window;
    std::array<state, hid_consts::keys>                    human_interface_device::key_pressed;
    std::array<state, mouse_button::eight>                 human_interface_device::mouse_pressed;
    std::pair<double, double>                              human_interface_device::cursor_position;
    std::array<int, sequence_size>                         human_interface_device::key_sequence,       human_interface_device::mouse_sequence;
    char                                                   human_interface_device::key_count,          human_interface_device::mouse_count;
    std::deque<std::array<int, hid_consts::sequence_size>> human_interface_device::saved_key_sequence(hid_consts::sequence_save_size),
                                                           human_interface_device::saved_mouse_sequence(hid_consts::sequence_save_size);

    human_interface_device::human_interface_device(GLFWwindow* w, int input_type, bool truth) noexcept
    {
        // make sure that there is one and only one instantiation
        assert(::instantiated == false);
        ::instantiated = true;
        
        key_count      = 0;
        mouse_count    = 0;
        window = w;
        
        glfwSetInputMode(window, input_type, truth);
        glfwSetKeyCallback(window, keyboard_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetCursorPosCallback(window, mouse_cursor_callback);
        
        time(&::then);
    }
    
    void human_interface_device::keyboard_callback(GLFWwindow*, int key, int, int action, int)
    {
        key += 1;
        if (action == GLFW_PRESS && key_pressed[key] != state::down)
        {
            key_pressed[key] = state::press;
            key_sequence[key_count] = key;
            
            ++key_count;
        }
        else if (action == GLFW_RELEASE && key_pressed[key] != state::up)
        {
            key_pressed[key] = state::release;
        }
    }
    
    void human_interface_device::mouse_button_callback(GLFWwindow*, int key, int action, int)
    {
        if (action == GLFW_PRESS && mouse_pressed[key] != state::down)
        {
            mouse_pressed[key] = state::press;
            mouse_sequence[mouse_count] = key;
            ++mouse_count;
        }
        else if (action == GLFW_RELEASE && mouse_pressed[key] != state::up)
        {
            mouse_pressed[key] = state::release;
        }
    }
    
    void human_interface_device::mouse_cursor_callback(GLFWwindow*, double x, double y)
    {
        cursor_position.first = x;
        cursor_position.second = y;
    }
    
    void human_interface_device::poll(bool input_enabled, double t)
    {
        // are we allowed to scan for input?
        if (input_enabled)
        {
            glfwWaitEvents();
            
            // are we allowed to do input sequencing?
            if (t > 0.0)
            {
                time(&::now);
                
                // has enough time passed?
                if (difftime(now, then) >= t)
                {
                    saved_key_sequence.push_back(key_sequence);
                    saved_mouse_sequence.push_back(mouse_sequence);

                    std::fill(key_sequence.begin(),   key_sequence.begin()   + key_count,   0);
                    std::fill(mouse_sequence.begin(), mouse_sequence.begin() + mouse_count, 0);

                    key_count   = 0;
                    mouse_count = 0;
                    
                    saved_key_sequence.pop_front();
                    saved_mouse_sequence.pop_front();
                    
                    time(&::then);
                }
            }
        }
    }
}
