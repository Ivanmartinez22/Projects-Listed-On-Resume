/**
 * In this file, implement the methods from Jeans.h
 * The implementation is identical to Stress_ball 
 */ 
#include "Jeans.h"


using std::string;
Jeans::Jeans(){
    color = Jeans_colors(rand() % 4);
    size = Jeans_sizes(rand() % 4);
}

Jeans::Jeans(Jeans_colors color, Jeans_sizes size){
    Jeans::color = color;
    Jeans::size = size;
}

Jeans_colors Jeans::get_color() const{
    return color;
}

Jeans_sizes Jeans::get_size() const{
    return size;
}

bool Jeans::operator==(const Jeans &sb) const{
    Jeans other = sb;
    if((this->get_color() == other.get_color()) && (this->get_size() == other.get_size())){
        return true;
    }
    else{
        return false;
    }
    
}


std::istream &operator>>(std::istream &o, Jeans& j){
    string color;
    string size;
    Jeans_colors color_enum;
    Jeans_sizes size_enum;
    
    o >> color >> size;
    if(color == "white"){
        color_enum = Jeans_colors::white;
    }
    else if(color == "black"){
       color_enum = Jeans_colors::black;
    }
    else if(color == "blue"){
      color_enum = Jeans_colors::blue;
    }
    else if(color == "grey"){
       color_enum = Jeans_colors::grey;
    }

    if(size == "small"){
        size_enum = Jeans_sizes::small;
    }
    else if(size == "medium"){
       size_enum = Jeans_sizes::medium;
    }
    else if(size == "large"){
        size_enum = Jeans_sizes::large;
    }
    else if(size == "xlarge"){
        size_enum = Jeans_sizes::xlarge;
    }
    j = Jeans(Jeans_colors(color_enum), Jeans_sizes(size_enum));
    return o;
    
}


std::ostream & operator <<(std::ostream &o, const Jeans &j){
    Jeans internal = j;
    string color;
    string size;
    switch (internal.get_color())
    {
    case Jeans_colors::white:
        color = "white";
        break;
    case Jeans_colors::black:
        color = "black";
        break;
    case Jeans_colors::blue:
        color = "blue";
        break;
    case Jeans_colors::grey:
        color = "grey";
        break;
    }
    switch (internal.get_size())
    {
    case Jeans_sizes::xlarge:
        size = "xlarge";
        break;
    case Jeans_sizes::large:
        size = "large";
        break;
    case Jeans_sizes::medium:
        size = "medium";
        break;
    case Jeans_sizes::small:
        size = "small";
        break;
    
    }


    o << "(" << color << ", " << size << ")";
    return o;
}