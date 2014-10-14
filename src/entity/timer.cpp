/*
 * Christopher Di Bella
 * Keane Chan, Ervin Macrohon, Timothy Masters
 *
 * 2014, September 17
 *
 * sample.hpp
 * Interface for an audio sample
 *
 * Timer implementation
 */
 
#include <entity/timer.hpp>

using std::chrono::nanoseconds;
using std::chrono::high_resolution_clock;

namespace phosphorus
{
    timer::timer(const std::chrono::nanoseconds& finish_time) : m_finish(high_resolution_clock::now() + nanoseconds(finish_time)) { }
    
    void timer::sleep() const
    {
        while (expired() == false);
    }
    
    void timer::sleep(const std::chrono::nanoseconds& finish_time)
    {
        auto expiry = high_resolution_clock::now() + nanoseconds(finish_time);
        while (high_resolution_clock::now() < expiry);
    }
    
    void timer::reset(const std::chrono::nanoseconds& finish_time)
    {
        m_finish = high_resolution_clock::now() + nanoseconds(finish_time);
    }
}
