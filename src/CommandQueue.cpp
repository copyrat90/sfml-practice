#include "CommandQueue.hpp"

#include <cassert>

namespace gr
{

bool CommandQueue::isEmpty() const
{
    return _queue.empty();
}

void CommandQueue::push(const Command& command)
{
    _queue.push(command);
}

auto CommandQueue::pop() -> Command
{
    assert(!isEmpty());

    Command command = _queue.front();
    _queue.pop();
    return command;
}

} // namespace gr
