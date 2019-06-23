cmake_minimum_required(VERSION 3.12)
project(OpenGlSetup)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Modules/")
message(CMAKE_MODULE_PATH : ${PROJECT_SOURCE_DIR}/Modules/)

set(SOURCE_FILES main.cpp ShaderProgram.cpp ShaderProgram.h Mesh.cpp Mesh.h MeshFactory.cpp MeshFactory.h Application.cpp Application.h Camera.cpp Camera.h OnKeyRotationCamera.cpp OnKeyRotationCamera.h Terrain.cpp Terrain.h Parser.cpp Parser.h generateHeight.cpp generateHeight.h Pocisk.cpp Pocisk.h Texture.cpp Texture.h lodepng.cpp lodepng.h Water.cpp Water.h Snowman.cpp Snowman.h FirstPersonCamera.cpp FirstPersonCamera.h ThirdPersonCamera.cpp ThirdPersonCamera.h)
add_executable(OpenGlSetup ${SOURCE_FILES})

find_package(glfw3 REQUIRED)
IF (NOT glfw3_FOUND)
    message(WARNING glfw3-NOT-FOUND : ${glfw3_INCLUDE_DIR})
ENDIF()

find_package(GLEW REQUIRED)
IF (NOT GLEW_FOUND)
    message(WARNING GLEW-NOT-FOUND : ${GLEW_INCLUDE_DIR})
ENDIF()

find_package(GLM REQUIRED)
IF (NOT GLM_FOUND)
    message(WARNING GLM-NOT-FOUND : ${GLM_INCLUDE_DIR})
ENDIF()

find_package(ASSIMP REQUIRED)
IF (NOT ASSIMP_FOUND)
    message(WARNING ASSIMP-NOT-FOUND : ${ASSIMP_INCLUDE_DIRS})
ENDIF()

find_package(GLM REQUIRED)
IF (NOT GLM_FOUND)
    message(WARNING GLM-NOT-FOUND : ${GLM_INCLUDE_DIR})
ENDIF()

find_package(OpenGL REQUIRED)
IF (NOT OPENGL_FOUND)
    message(WARNING OPENGL-NOT-FOUND: ${OPENGL_INCLUDE_DIR})
else()
    message(OPENGL-FOUND: ${OPENGL_INCLUDE_DIR})
    message(GLM-FOUND : ${GLM_INCLUDE_DIRS})
    message(glfw3-FOUND : ${glfw_INCLUDE_DIRS})
    message(GLEW-FOUND : ${GLEW_INCLUDE_DIRS})
    message(ASSIMP-FOIUND : ${ASSIMP_INCLUDE_DIRS})
ENDIF()

include_directories(${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARIES})
target_link_libraries(OpenGlSetup ${OPENGL_LIBRARY} ${GLEW_LIBRARY} glfw)