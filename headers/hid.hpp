/*
 * Christopher Di Bella
 * Keane Chan, Ervin Macrohon, Timothy Masters
 *
 * 2014, September 16
 *
 * hid.hpp
 * Interface for human interface devices
 */
#ifndef PHOSPHORUS_HID_HPP11_INCLUDED
#define PHOSPHORUS_HID_HPP11_INCLUDED

#include "GLFW/glfw3.h"
#include <array>
#include <utility>
#include <deque>

namespace phosphorus
{
    enum state        { up, release, press, down };
    enum mouse_button { left, middle, right, four, five, six, seven, eight };
    enum hid_consts   { sequence_size = 64, sequence_save_size = 5, keys = 360 };
    
    class human_interface_device
    {
    private:
        static GLFWwindow* window;
        static std::array<state, mouse_button::eight>                 mouse_pressed;
        static std::array<state, hid_consts::keys>                    key_pressed;
        static std::pair<double, double>                              cursor_position;
        static std::array<int, hid_consts::sequence_size>             key_sequence, mouse_sequence;
        static std::deque<std::array<int, hid_consts::sequence_size>> saved_key_sequence, saved_mouse_sequence;
        static char                                                   key_count, mouse_count;

        human_interface_device(const human_interface_device&)              = delete;
        human_interface_device& operator=(const human_interface_device&)   = delete;
        
        static void keyboard_callback(GLFWwindow*, int key, int, int action, int);
        static void mouse_button_callback(GLFWwindow*, int key, int, int action);
        static void mouse_cursor_callback(GLFWwindow*, double x, double y);
    public:
        human_interface_device(GLFWwindow* w, int input_type, bool truth) noexcept;
        
        human_interface_device(human_interface_device&&);
        human_interface_device&& operator=(const human_interface_device&&);
        
        /*
         * $name:                poll
         * $return:              void
         * $param input_enabled: determines whether or not input is scanned for
         * $param time:          the distance between when the input sequences terminate. default at 1.0
         *                       set to 0.0 or less to disable sequences
         *
         * $description:         scans for input and calls the callback functions.
         *                       you must call this function once per cycle.
         *                       input sequences saved in this function
         *
         * $pre-condition:       none
         * $post-condition:      none
         * $side-effects:        device interrupt, accessing a non-constant variable
         */
        void poll(bool input_enabled = true, double time = 1.0);
        
        std::array<int, hid_consts::sequence_size> get_key_sequence(const unsigned char x)
        {
            if (x >= sequence_save_size)
                throw;
            return saved_key_sequence[x];
        }
        
        std::array<int, hid_consts::sequence_size> get_mouse_sequence(const unsigned char x)
        {
            if (x >= sequence_save_size)
                throw;
            return saved_mouse_sequence[x];
        }
        
        /*
         * $name:           on_key_press
         * $return:         true if action is executed, false otherwise
         * $param key:      the key in question (ranges from 0 - 255)
         * $param action:   a lambda that will be executed if the pre-condition is met
         *
         * $description:    if a key is pressed, then an action will be executed
         *
         * $pre-condition:  key has not been pressed before (i.e. keyboard_pressed[key] == false)
         * $post-condition: none
         * $side-effects:   device interrupt, accessing a non-constant variable
         */
        template <typename T>
        inline bool on_key_press(const int key, const T& action);
        
        /*
         * $name:           on_key_release
         * $return:         true if action is executed, false otherwise
         * $param key:      the key in question (ranges from 0 - 255)
         * $param action:   a lambda that will be executed if the pre-condition is met
         *
         * $description:    if a key is pressed, then an action will be executed
         *
         * $pre-condition:  key has been pressed before (i.e. keyboard_pressed[key] == true)
         * $post-condition: none
         * $side-effects:   device interrupt, accessing a non-constant variable
         */
        template <typename T>
        inline bool on_key_release(const int key, const T& action);
        
        /*
         * $name:           on_key_down
         * $return:         true if action is executed, false otherwise
         * $param key:      the key in question (ranges from 0 - 255)
         * $param action:   a lambda that will be executed if the pre-condition is met
         *
         * $description:    if a key is held down, then an action will be executed
         *
         * $pre-condition:  key has been pressed; note that in order for key_down condition to be satisfied, key_press pre-condition
         *                  must also be satisfied at least once
         * $post-condition: none
         * $side-effects:   device interrupt, accessing a non-constant variable
         */
        template <typename T>
        inline bool on_key_down(const int key, const T& action);
        
        /*
         * $name:           on_key_up
         * $return:         true if action is executed, false otherwise
         * $param key:      the key in question (ranges from 0 - 255)
         * $param action:   a lambda that will be executed if the pre-condition is met
         *
         * $description:    if a key is not pressed, then an action will be executed
         *
         * $pre-condition:  key is not pressed; note that in order for key_up condition to be satisfied, key_release pre-condition
         *                  may not need to be satisfied, but usually is
         * $post-condition: none
         * $side-effects:   device interrupt, accessing a non-constant variable
         */
        template <typename T>
        inline bool on_key_up(const int key, const T& action);
        
        /*
         * $name:           on_mouse_press
         * $return:         true if action is executed, false otherwise
         * $param key:      the key in question (supports ten buttons)
         * $param action:   a lambda that will be executed if the pre-condition is met
         *
         * $description:    if a button is pressed, then an action will be executed
         *
         * $pre-condition:  button has not been pressed before (i.e. mouse_pressed[key] == false)
         * $post-condition: none
         * $side-effects:   device interrupt, accessing a non-constant variable
         */
        template <typename T>
        inline bool on_mouse_press(const mouse_button button, const T& action);
        
        /*
         * $name:           on_mouse_release
         * $return:         true if action is executed, false otherwise
         * $param key:      the key in question (supports ten buttons)
         * $param action:   a lambda that will be executed if the pre-condition is met
         *
         * $description:    if a button is pressed, then an action will be executed
         *
         * $pre-condition:  button has been pressed before (i.e. mouse_pressed[key] == true)
         * $post-condition: none
         * $side-effects:   device interrupt, accessing a non-constant variable
         */
        template <typename T>
        inline bool on_mouse_release(const mouse_button button, const T& action);
        
        /*
         * $name:           on_mouse_down
         * $return:         true if action is executed, false otherwise
         * $param key:      the mouse button in question (supports ten buttons)
         * $param action:   a lambda that will be executed if the pre-condition is met
         *
         * $description:    if a mouse button is held down, then an action will be executed
         *
         * $pre-condition:  mouse button has been pressed; note that in order for mouse_down condition to be satisfied, mouse_press pre-condition
         *                  must also be satisfied at least once
         * $post-condition: none
         * $side-effects:   device interrupt, accessing a non-constant variable
         */
        template <typename T>
        inline bool on_mouse_down(const mouse_button button, const T& action);
        
        /*
         * $name:           on_mouse_up
         * $return:         true if action is executed, false otherwise
         * $param key:      the mouse button in question (supports ten buttons)
         * $param action:   a lambda that will be executed if the pre-condition is met
         *
         * $description:    if a mouse button is not pressed, then an action will be executed
         *
         * $pre-condition:  mouse button is not pressed; note that in order for mouse_up condition to be satisfied, mouse_release pre-condition
         *                  may not need to be satisfied, but usually is
         * $post-condition: none
         * $side-effects:   device interrupt, accessing a non-constant variable
         */
        template <typename T>
        inline bool on_mouse_up(const mouse_button button, const T& action);
        
        inline bool is_key_down(const int key);
        inline bool is_key_down(const mouse_button key);
        inline bool is_key_is_up(const int key);
        inline bool is_key_is_up(const mouse_button key);
        
        template <typename T>
        inline bool is_cursor_at_coordinates(const T& coords);
        
        inline const std::pair<double, double>& get_cursor_position();
        
        template <typename T, typename U>
        inline bool on_cursor_at_coordinates(const T& coords, const U& action);
    };
}
#include "hid.tem"
#endif // PHOSPHORUS_HID_HPP11_INCLUDED
