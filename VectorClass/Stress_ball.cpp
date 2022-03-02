

// Ivan Martinez UIN: 529006731
#include "Stress_ball.h"

using std::string;


// enum Stress_ball_colors color;
// enum Stress_ball_sizes size;



Stress_ball::Stress_ball(){
    color = Stress_ball_colors(rand() % 4);
    size = Stress_ball_sizes(rand() % 3);
}

Stress_ball::Stress_ball(Stress_ball_colors color, Stress_ball_sizes size){
    Stress_ball::color = color;
    Stress_ball::size = size;
}

Stress_ball_colors Stress_ball::get_color() const{
    return color;
}

Stress_ball_sizes Stress_ball::get_size() const{
    return size;
}

bool Stress_ball::operator==(const Stress_ball &sb) const{
    Stress_ball other = sb;
    if((this->get_color() == other.get_color()) && (this->get_size() == other.get_size())){
        return true;
    }
    else{
        return false;
    }
    
}


std::istream &operator>>(std::istream &o, Stress_ball& sb){
    string color;
    string size;
    Stress_ball_colors color_enum;
    Stress_ball_sizes size_enum;
    
    o >> color >> size;
    if(color == "red"){
        color_enum = Stress_ball_colors::red;
    }
    else if(color == "green"){
       color_enum = Stress_ball_colors::green;
    }
    else if(color == "blue"){
      color_enum = Stress_ball_colors::blue;
    }
    else if(color == "yellow"){
       color_enum = Stress_ball_colors::yellow;
    }

    if(size == "small"){
        size_enum = Stress_ball_sizes::small;
    }
    else if(size == "medium"){
       size_enum = Stress_ball_sizes::medium;
    }
    else if(size == "large"){
        size_enum = Stress_ball_sizes::large;
    }
    sb = Stress_ball(Stress_ball_colors(color_enum), Stress_ball_sizes(size_enum));
    return o;
    
}

std::ostream & operator <<(std::ostream &o, const Stress_ball &sb){
    Stress_ball internal = sb;
    string color;
    string size;
    switch (internal.get_color())
    {
    case Stress_ball_colors::red:
        color = "red";
        break;
    case Stress_ball_colors::green:
        color = "green";
        break;
    case Stress_ball_colors::blue:
        color = "blue";
        break;
    case Stress_ball_colors::yellow:
        color = "yellow";
        break;
    }
    switch (internal.get_size())
    {
    case Stress_ball_sizes::large:
        size = "large";
        break;
    case Stress_ball_sizes::medium:
        size = "medium";
        break;
    case Stress_ball_sizes::small:
        size = "small";
        break;
    }

    o << "(" << color << ", " << size << ")";
    return o;
}

