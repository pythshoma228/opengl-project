#include <iostream>
#include <memory>
#include <cmath>
#include <string>


#include <SFML/Window.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include "Shaders.h"

int main() {

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;
 
    sf::Window window(sf::VideoMode(800, 600), "Test", sf::Style::Default, settings);
    glEnable(GL_DEPTH_TEST);

    glewExperimental = GL_TRUE;
    
    if(GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW" << "\n";
        return EXIT_FAILURE;
    }
    
    std::cout << glGetString(GL_VERSION) << "\n";

    ShaderProgramSource source = parseShader("../res/shaders/basic.shader");
    
    std::cout << source.VertexSource << "\n";
    std::cout << source.FragmentSource;
    unsigned int shader = CreateShader(source.VertexSource,source.FragmentSource);



    float positions[] = {
//      x        y      z    R     G    B     S    T
        0.5f,   0.5f, -0.5f, 0.0f,0.0f,1.0f, 1.0f,1.0f, // 0
        0.5f,  -0.5f, -0.5f, 1.0f,1.0f,0.0f, 1.0f,0.0f, // 1
        -0.5f, -0.5f, -0.5f, 1.0f,1.0f,0.0f, 0.0f,0.0f, // 2
        -0.5f,  0.5f, -0.5f, 0.0f,0.0f,1.0f, 0.0f,1.0f, // 3

        0.5f,   0.5f, 0.5f, 1.0f,0.0f,0.0f, 1.0f,1.0f,   // 4
        0.5f,  -0.5f, 0.5f, 0.0f,1.0f,0.0f, 1.0f,0.0f,   // 5
        -0.5f, -0.5f, 0.5f, 0.0f,0.0f,1.0f, 0.0f,0.0f,   // 6
        -0.5f,  0.5f, 0.5f, 1.0f,1.0f,0.0f, 0.0f,1.0f,    // 7

        0.5f,  0.5f, -0.5f, 0.0f,0.0f,1.0f, 1.0f,1.0f, // 8
        0.5f, -0.5f, -0.5f, 1.0f,1.0f,0.0f, 1.0f,0.0f, // 9
        0.5f, -0.5f,  0.5f, 1.0f,1.0f,0.0f, 0.0f,0.0f, // 10
        0.5f,  0.5f,  0.5f, 0.0f,0.0f,1.0f, 0.0f,1.0f, // 11

        -0.5f,  0.5f, -0.5f,  1.0f,0.0f,0.0f, 1.0f,1.0f,   // 12
        -0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f, 1.0f,0.0f,   // 13
        -0.5f, -0.5f, 0.5f,   0.0f,0.0f,1.0f, 0.0f,0.0f,   // 14
        -0.5f,  0.5f, 0.5f,   1.0f,1.0f,0.0f, 0.0f,1.0f,    // 15

        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f, 1.0f,1.0f, // 16
        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f, 1.0f,0.0f, // 17
        -0.5f, 0.5f,  0.5f,  1.0f,1.0f,0.0f, 0.0f,0.0f, // 18
        -0.5f, 0.5f, -0.5f,  0.0f,0.0f,1.0f, 0.0f,1.0f, // 19

        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 20
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // 21
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 22
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // 23


    };

    unsigned int indices[] = {
        0,1,3,
        1,2,3,

        4,5,6,
        4,6,7,

        8,9,11,
        9,10,11,

        12,13,15,
        13,14,15,

        16,17,19,
        17,18,19,

        20,21,23,
        21,22,23
    };

    unsigned int buffer, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &buffer);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //stride показывает на сколько байт нужно перемещаться для получения следующей вершины x+y+z -> 12.0f
    //size количество пространственных осей xyz -> 3
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  
    
    //unbind current buffers for further render states 
    //glBindBuffer(GL_ARRAY_BUFFER, 0);     
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    //glBindVertexArray(0);
    //int vertexColorLocation = glGetUniformLocation(shader, "newColor");

    
    unsigned int textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);  
    int width,height,nrChannels;
    unsigned char* datatexture = stbi_load("../res/textures/dirt.jpg",&width,&height,&nrChannels,0);

    if (datatexture)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, datatexture);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 1" << std::endl;
    }
    stbi_image_free(datatexture);

    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "texture1"),0);


    GLfloat theta = 1.0f;

    sf::Clock clock;
    
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        
        window.setActive(true);

        glClearColor(1.0f,1.0f,1.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textureID);
        glUseProgram(shader);

        //glm::vec4 vec(0.0f,0.0f,1.0f,1.0f);
        glm::mat4 trans(1.0f);
        trans = glm::rotate(
            trans,
            static_cast<float>(glm::radians(theta)),
            glm::vec3(1.0,1.0,1.0)
        );
        trans = glm::scale(trans,glm::vec3(0.8,0.8,0.8));
        //vec = trans * vec;
        glUniformMatrix4fv(glGetUniformLocation(shader,"rotation"),1,GL_FALSE,glm::value_ptr(trans));


        


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        window.setActive(false);
        theta += 1.0f;
        
        window.display();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &buffer);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader);
    glDeleteTextures(1,&textureID);

    window.close();
    return 0;
}