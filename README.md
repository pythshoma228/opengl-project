# OpenGL + SFML
This is my study project that using Modern OpenGL


This project includes SFML, GLEW, GLM and stb_image

Also you can view this project as example of usage Modern OpenGL

I will add some more things to this project in the future


## How to build
To build the project, first clone it into your folder:
```
git clone https://github.com/pythshoma228/opengl-project.git
```
install vcpkg using git and build it yourself to have all dependecies:
```
cd opengl-project

git clone https://github.com/microsoft/vcpkg

cd vcpkg

bootstrap-vcpkg.bat (for Windows)

bootstrap-vcpkg.sh (for Linux)
```

Then use cmake command and don't forget to write your build path and generator:
```
cmake -S . -B YOUR_BUILD_FOLDER_PATH -G"YOUR_GENERATOR" -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
```

Also it's able to specify to put files in debug or release directory

Just add at the end of cmake command
```
-DCMAKE_BUILD_TYPE=Debug/Release
```

And build:
```
cmake --build YOUR_BUILD_FOLDER_PATH
```

### Link to libraries I used

SFML https://github.com/SFML/SFML


GLEW https://github.com/nigels-com/glew


GLM https://github.com/g-truc/glm


stb_image https://github.com/nothings/stb
