#pragma once

#include <array>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace gr
{

template <typename Resource, typename Id, int IdMaxCount>
    requires std::is_enum_v<Id>
class ResourceHolder
{
    using UptrResource = std::unique_ptr<Resource>;

private:
    std::array<UptrResource, IdMaxCount> _resourceArray;

public:
    void loadFromFile(Id id, const std::string& filename)
    {
        assert(0 <= (int)id && (int)id < IdMaxCount && "Resource Id out of bound");
        UptrResource& resource = _resourceArray[(int)id];
        assert(!resource && "Multiple load of same resource");
        auto res = std::make_unique<Resource>();
        if (!res->loadFromFile(filename))
            throw std::runtime_error("Failed to load '" + filename + "'");
        resource = std::move(res);
    }

    template <typename Param>
    void loadFromFile(Id id, const std::string& filename, const Param& param2)
    {
        assert(0 <= (int)id && (int)id < IdMaxCount && "Resource Id out of bound");
        UptrResource& resource = _resourceArray[(int)id];
        assert(!resource && "Multiple load of same resource (param2)");
        auto res = std::make_unique<Resource>();
        if (!res->loadFromFile(filename, param2))
            throw std::runtime_error("Failed to load '" + filename + "' with param2");
        resource = std::move(res);
    }

    auto get(Id id) -> Resource&
    {
        assert(0 <= (int)id && (int)id < IdMaxCount && "Resource Id out of bound");
        UptrResource& res = _resourceArray[(int)id];
        assert(res && "Tried to get resource which is not loaded");
        return *res;
    }

    auto get(Id id) const -> const Resource&
    {
        assert(0 <= (int)id && (int)id < IdMaxCount && "Resource Id out of bound");
        UptrResource& res = _resourceArray[(int)id];
        assert(res && "Tried to get resource which is not loaded");
        return *res;
    }
};

} // namespace gr
