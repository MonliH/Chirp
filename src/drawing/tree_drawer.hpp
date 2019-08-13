#pragma once

#include "../drawing/tree_drawer.hpp"

class tree_drawer{
public:
    tree_drawer() = delete;
    tree_drawer(const std::string& fname)
        :   m_fname{fname}
    { }
    virtual ~tree_drawer() = default;
    virtual void draw(const tree_interface& t) const = 0;
protected:
    const std::string& m_fname{};
};
