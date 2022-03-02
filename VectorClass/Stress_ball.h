#pragma once

#include <iostream>

enum class Stress_ball_colors{
    red,
    blue,
    green,
    yellow,
};

enum class Stress_ball_sizes{
    small,
    medium,
    large,
};

class Stress_ball {
    public:
        Stress_ball();
        Stress_ball(Stress_ball_colors color, Stress_ball_sizes size);
        Stress_ball_colors get_color() const;
        Stress_ball_sizes get_size() const;
        bool operator==(const Stress_ball &sb) const;
    private:
        Stress_ball_colors color;
        Stress_ball_sizes size;

    friend std::istream& operator>>(std::istream &o, Stress_ball & sb);
};

std::ostream & operator <<(std::ostream &o, const Stress_ball &sb);
