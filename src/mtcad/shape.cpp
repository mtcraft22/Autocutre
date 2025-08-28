#include "mtcad/Node.hpp"
#include <fstream>
#include <mtcad/Shape.hpp>
#include <ostream>
#include <string>


std::ostream& mt_cad::operator<<(std::ostream& file,mt_cad::Shape& circle){
    file << ("Shape: " +std::to_string(circle.get_material())) << std::endl;
    file << "Points: "<< std::endl;
    for (auto node : circle.get_points() ) {
        float x,y;
        Restictions canmove = node.get_canmove();
        node.get_coords(x, y);
        file << x << " " << y << " " << canmove << std::endl;
    }

    file << "end shape" << std::endl;
    return  file;
}