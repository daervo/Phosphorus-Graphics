/*
 * Christopher Di Bella
 * Keane Chan, Ervin Macrohon, Timothy Masters
 *
 * 2014, September 17
 *
 * sample.hpp
 * Interface for an audio sample
 *
 * Timer interface
 */
#ifndef PHOSPHORUS_TIMER_HPP11_INCLDUED
#define PHOSPHORUS_TIMER_HPP11_INCLDUED

#include <chrono>
#include <utility.hpp>

namespace phosphorus
{
    class timer
    {
    private:
        std::chrono::system_clock::time_point m_finish;
        std::chrono::system_clock::time_point m_pauseTime;
        bool m_paused;
    public:
        /**
         * @constructor       timer(const std::chrono::nanoseconds& finish_time = 1_sec)
         * @param finish_time The time distance between timer set up and when the timer expires in nanoseconds. Default value is 1 000 000 000 ns (1 second)
         * @description       Sets up the timer and finish time. Refer to C++11 Standard for user defined types if you wish to work with a different unit of time.
         */
        timer(const std::chrono::nanoseconds& finish_time = 1_sec);
        
        // destructor only implemented in case timer is inherited!
        virtual ~timer() { }
        
        /**
         * @name        void phosphorus::timer::sleep() const
         *
         * @description Sleeps until timer expired
         *
         * @pre         none
         * @post        none
         * @effects     device interrupt
         */
        void sleep() const;
        
        /**
         * @name             static void phosphorus::timer::sleep(size_t sleep_time) const
         * @param sleep_time The number of nanoseconds the timer is to be set for
         * @description      Sets a timer and then sleeps until timer expired. Use this if you do not have a need for an individual timer, or currently have no timer at your disposal.
         *                   Does not affect any individual timers.
         *
         * @pre              none
         * @post             none
         * @effects          modification of non-const variable, device interrupt
         */
        static void sleep(const std::chrono::nanoseconds& sleep_time);
        
        /**
         * @name         inline bool phosphorus::timer::expired() const
         * @return       true if current time > m_finish; false otherwise
         *
         * @description  Determines if the current time is beyond the specified finish time
         *
         * @pre          timer is not paused
         * @post         none
         * @effects      device interrupt
         */
        inline bool expired() const
        {
            return (m_finish < std::chrono::high_resolution_clock::now() && m_paused == false);
        }
        
        /**
         * @name              void phosphorus::timer::reset()
         * @param finish_time The new number of nanoseconds after this function is called before timer expiry
         *
         * @description       Updates the finish time of the timer
         *
         * @pre               none
         * @post              none
         * @effects           modifying a non-constant variable, device interrupt
         */
        void reset(const std::chrono::nanoseconds& finish_time);
        
        /**
         * @name        inline size_t phosphorus::timer::time_remaining() const
         * @return      number of nanoseconds between current time and finish time
         *
         * @description Provides the amount of time remaining before expiry in nanoseconds
         *
         * @pre         Timer is not paused
         * @post        none
         * @effects     device interrupt
         */
        inline size_t time_remaining() const
        {
            auto now = std::chrono::high_resolution_clock::now();
            if (m_paused)
            {
                return ((m_finish - now) + (now - m_pauseTime)).count();
            }
            else
            {
                return (m_finish - std::chrono::high_resolution_clock::now()).count();
            }
        }
        
        /**
         * @name        inline size_t phosphorus::timer::time_remaining_us() const
         * @return      number of microseconds between current time and finish time
         *
         * @description Provides the amount of time remaining before expiry in microseconds. WARNING: PRECISION LOST WITH RESPECT TO time_remaining()
         *
         * @pre         Timer is not paused
         * @post        none
         * @effects     device interrupt
         */
        inline size_t time_remaining_us() const
        {
            return time_remaining() / 1000;
        }
        
        /**
         * @name        inline size_t phosphorus::timer::time_remaining() const
         * @return      number of milliseconds between current time and finish time
         *
         * @description Provides the amount of time remaining before expiry in milliseconds. WARNING: PRECISION LOST WITH RESPECT TO time_remaining()
         *
         * @pre         Timer is not paused
         * @post        none
         * @effects     device interrupt
         */
        inline size_t time_remaining_ms() const
        {
            return time_remaining() / 10e+6;
        }
        
        /**
         * @name        inline size_t phosphorus::timer::time_remaining() const
         * @return      number of seconds between current time and finish time
         *
         * @description Provides the amount of time remaining before expiry in seconds. WARNING: PRECISION LOST WITH RESPECT TO time_remaining()
         *
         * @pre         Timer is not paused
         * @post        none
         * @effects     device interrupt
         */
        inline size_t time_remaining_sec() const
        {
            return time_remaining() / 10e+9;
        }
        
        /**
         * @name        inline bool phosphorus::timer::pause()
         * @return      true if the timer is paused; false otherwise
         *
         * @description Pauses the timer
         *
         * @pre         Timer is not already paused or expired
         * @post        Timer is no longer active
         * @effects     device interrupt, modifying a non-const variable
         */
        inline void pause()
        {
            if (expired() == false && m_paused == false)
            {
                m_paused = true;
                m_pauseTime = std::chrono::high_resolution_clock::now();
            }
        }
        
        /**
         * @name        inline bool phosphorus::timer::unpause()
         * @return      true if the timer is unpaused; false otherwise
         *
         * @description Allows the timer to resume
         *
         * @pre         Timer is paused
         * @post        Timer is now active
         * @effects     device interrupt, modifying a non-const variable
         */
        inline void unpause()
        {
            if (m_paused == true)
            {
                m_paused = false;
                m_finish += (std::chrono::high_resolution_clock::now() - m_pauseTime);
            }
        }
        
        /**
         * @name        inline bool phosphorus::timer::is_paused() const
         * @return      true if the timer is paused; false otherwise
         *
         * @description Determines if the timer is paused
         *
         * @pre         none
         * @post        none
         * @effects     none
         */
        inline bool is_paused() const { return m_paused; }
    };
}

#endif // PHOSPHORUS_TIMER_HPP11_INCLDUED
