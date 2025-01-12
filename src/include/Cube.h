#pragma once
#include <glm/glm.hpp>
#include <array>
#include <utility>
#include <vector>
#include <unordered_map>
#define CUBE_SIDES 6

struct Cube {

    enum types {
        NONE = 0,
        DIRT,
        GRASS,
        STONE
    };

    enum sides {
        front = 0,
        back,
        top,
        bottom,
        right,
        left
    };

    Cube(const types& typeID);

    void setPosition(glm::vec3 pos);

    glm::vec3& getPosition();

    const types& getTypeID() const;

    
    static const std::array<float,120> vertexes;

    static const struct index_t { 
        sides side;
        const std::array<unsigned int,6> elements;
    } indices[CUBE_SIDES];

    //static const std::array<const std::array<unsigned int,36>,CUBE_SIDES> indices; 

    static struct buffer_t {
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO[CUBE_SIDES];
        const std::int8_t positionCoordsNum = 3;
        const std::int8_t textureCoordsNum = 2;
    } buffer;

    void popRenderSide(sides side);

    void pushRenderSide(sides side);

    std::unordered_map<sides,const unsigned int>& getCurrentRendrSides();

private:

    std::unordered_map<sides,const unsigned int> _currentRenderSides;

    glm::vec3 _position;
    const types _typeID;    
};
