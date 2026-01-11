#pragma once

#include <vector>
#include <functional>

namespace nbase_kit
{
    template <typename... Args>
    class Event
    {
        
    //---------------------------------------------------------- Fields
    private:
        std::vector< std::function<void(Args...)>> handlers_;

    //---------------------------------------------------------- Methods
    public:
        void Subscribe(std::function<void(Args...)> handler)
        { 
            handlers_.push_back(handler);
        }

        void Notify(Args... args)
        {
            for (auto& handler : handlers_)
                handler(args...);
        }

        void Clear() 
        { 
            handlers_.clear();
        }
    };
}