#pragma once

#include "Command.hpp"

#include <queue>

namespace gr
{

class CommandQueue
{
private:
    std::queue<Command> _queue;

public:
    bool isEmpty() const;

    void push(const Command&);
    auto pop() -> Command;
};

} // namespace gr
