#pragma once

#include <iostream>

enum class Jeans_colors
{
    white,
    black,
    blue,
    grey
};
enum class Jeans_sizes
{
    small,
    medium,
    large,
    xlarge
};

class Jeans
{
private:
    Jeans_colors color;
    Jeans_sizes size;
public:
    Jeans();
    Jeans(Jeans_colors color, Jeans_sizes size);
    Jeans_colors get_color() const;
    Jeans_sizes get_size() const;
    bool operator==(const Jeans &j) const;
    
    friend std::istream &operator>>(std::istream &is, Jeans &j);
};

std::ostream &operator<<(std::ostream &os, const Jeans &j);

