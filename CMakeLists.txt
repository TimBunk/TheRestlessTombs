#CMake entry point
cmake_minimum_required (VERSION 2.8.0)
project (TheRestlessTombs)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies
find_package(OpenGL REQUIRED)

add_subdirectory(external)

if(UNIX)
  # Set c++11 as main language
  set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O2")

  # Look up SDL2 and add the include directory to our include path
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2/")
  find_package(SDL2 REQUIRED)
  find_package(SDL2_mixer REQUIRED)
  find_package(SDL2_ttf REQUIRED)
  find_package(SDL2_image REQUIRED)
endif(UNIX)

# Create library from soil2 source
set (SOIL2_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external/SOIL2/src
)

add_subdirectory(
  external/SOIL2/src
)

include_directories(
  ${SOIL2_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/external/glew-2.1.0/include
  ${CMAKE_SOURCE_DIR}/external/SOIL2/src/SOIL2
  ${CMAKE_SOURCE_DIR}/external/SOIL2/src/include
  ${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/tb2d
)

link_directories(
  ${CMAKE_SOURCE_DIR}/external/glew-2.1.0
  ${CMAKE_SOURCE_DIR}/external/glm-0.9.8.4
  ${CMAKE_SOURCE_DIR}/external
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
  GLEW
  ${GLEW_LIBRARIES}
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

####################################################################
# box2d.a                                                          #
####################################################################
option(BOX2D_INSTALL "Install Box2D libs, includes, and CMake scripts" ON)
option(BOX2D_INSTALL_DOC "Install Box2D documentation" ON)
option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" ON)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
option(BOX2D_BUILD_EXAMPLES "Build Box2D examples" ON)

set(BOX2D_VERSION 2.3.2)
set(LIB_INSTALL_DIR lib${LIB_SUFFIX})

# The Box2D library.
add_subdirectory(external/Box2D)

include_directories(
  ${CMAKE_SOURCE_DIR}/external/Box2D
)
link_directories(
  ${CMAKE_SOURCE_DIR}/external/Box2D
)
add_definitions(
    -DBOX2D_BUILD_STATIC
)
set(BOX2D_LIB
    Box2D
)

# Include all of the tb2d source and header files in to the project
set(TB2DSOURCE
external/tb2d/texture.cpp
external/tb2d/texture.h
external/tb2d/shader.cpp
external/tb2d/shader.h
external/tb2d/entity.h
external/tb2d/entity.cpp
external/tb2d/scene.h
external/tb2d/scene.cpp
external/tb2d/camera.h
external/tb2d/camera.cpp
external/tb2d/debugRenderer.h
external/tb2d/debugRenderer.cpp
external/tb2d/text.h
external/tb2d/text.cpp
external/tb2d/resourceManager.h
external/tb2d/resourceManager.cpp
external/tb2d/input.h
external/tb2d/input.cpp
external/tb2d/window.h
external/tb2d/window.cpp
external/tb2d/hud.h
external/tb2d/hud.cpp
external/tb2d/button.h
external/tb2d/button.cpp
)

####################################################################
# TheRestlessTombs                                                 #
####################################################################
add_executable(trt
  ${TB2DSOURCE}
  TheRestlessTombs/main.cpp
  TheRestlessTombs/armoredOrc.cpp
  TheRestlessTombs/armoredOrc.h
  TheRestlessTombs/babyOrc.cpp
  TheRestlessTombs/babyOrc.h
  TheRestlessTombs/bomb.cpp
  TheRestlessTombs/bomb.h
  TheRestlessTombs/bomberOrc.cpp
  TheRestlessTombs/bomberOrc.h
  TheRestlessTombs/boss.cpp
  TheRestlessTombs/boss.h
  TheRestlessTombs/bossOrc.cpp
  TheRestlessTombs/bossOrc.h
  TheRestlessTombs/crate.cpp
  TheRestlessTombs/crate.h
  TheRestlessTombs/damagePotion.cpp
  TheRestlessTombs/damagePotion.h
  TheRestlessTombs/destructable.cpp
  TheRestlessTombs/destructable.h
  TheRestlessTombs/door.cpp
  TheRestlessTombs/door.h
  TheRestlessTombs/enemy.cpp
  TheRestlessTombs/enemy.h
  TheRestlessTombs/gold.cpp
  TheRestlessTombs/gold.h
  TheRestlessTombs/healthPotion.cpp
  TheRestlessTombs/healthPotion.h
  TheRestlessTombs/level1.cpp
  TheRestlessTombs/level1.h
  TheRestlessTombs/lootChest.cpp
  TheRestlessTombs/lootChest.h
  TheRestlessTombs/necromancerOrc.cpp
  TheRestlessTombs/necromancerOrc.h
  TheRestlessTombs/orc.cpp
  TheRestlessTombs/orc.h
  TheRestlessTombs/person.cpp
  TheRestlessTombs/person.h
  TheRestlessTombs/player.cpp
  TheRestlessTombs/player.h
  TheRestlessTombs/potion.cpp
  TheRestlessTombs/potion.h
  TheRestlessTombs/psychoOrc.cpp
  TheRestlessTombs/psychoOrc.h
  TheRestlessTombs/room.cpp
  TheRestlessTombs/room.h
  TheRestlessTombs/shop.cpp
  TheRestlessTombs/shop.h
  TheRestlessTombs/speedPotion.cpp
  TheRestlessTombs/speedPotion.h
  TheRestlessTombs/wall.cpp
  TheRestlessTombs/wall.h
  TheRestlessTombs/b2entity.cpp
  TheRestlessTombs/b2entity.h
  TheRestlessTombs/renderable.cpp
  TheRestlessTombs/renderable.h
  TheRestlessTombs/contactListener.h
  TheRestlessTombs/contactListener.cpp
  TheRestlessTombs/weapon.cpp
  TheRestlessTombs/weapon.h
  TheRestlessTombs/showCase.cpp
  TheRestlessTombs/showCase.h
  TheRestlessTombs/rayCastCallBack.h
  TheRestlessTombs/rayCastCallBack.cpp
  TheRestlessTombs/item.h
  TheRestlessTombs/item.cpp
  TheRestlessTombs/menu.h
  TheRestlessTombs/menu.cpp
  TheRestlessTombs/playerHud.h
  TheRestlessTombs/playerHud.cpp
)
target_link_libraries(trt
  ${BOX2D_LIB}
  ${ALL_GRAPHICS_LIBS}
  SDL2
	${SDL2_MIXER_LIBRARIES}
	${SDL2_TTF_LIBRARY}
  ${SDL2IMAGE_LIBRARY}
  SOIL2
)

ADD_DEPENDENCIES(trt
  SOIL2
)
# Copy shaders and textures to the build directory
file(
  COPY external/tb2d/shaders
  DESTINATION ${CMAKE_BINARY_DIR}
)
file(
  COPY external/tb2d/fonts
  DESTINATION ${CMAKE_BINARY_DIR}
)
file(
  COPY TheRestlessTombs/textures
  DESTINATION ${CMAKE_BINARY_DIR}
)
file(
  COPY TheRestlessTombs/shaders
  DESTINATION ${CMAKE_BINARY_DIR}
)
