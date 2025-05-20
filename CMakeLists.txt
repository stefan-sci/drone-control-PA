cmake_minimum_required(VERSION 3.10)
project(DroneMonitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# macOS M1 specific settings
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    set(CMAKE_BUILD_TYPE Debug)
    set(HOMEBREW_PATH "/opt/homebrew")
    
    list(APPEND CMAKE_PREFIX_PATH "${HOMEBREW_PATH}")
    
    # Explicitly set library paths for M1 Mac
    set(ASSIMP_ROOT_DIR ${HOMEBREW_PATH})
    set(ASSIMP_INCLUDE_DIRS "${HOMEBREW_PATH}/include")
    set(ASSIMP_LIBRARIES "${HOMEBREW_PATH}/lib/libassimp.dylib")
    
    # Add Homebrew's pkg-config path
    set(ENV{PKG_CONFIG_PATH} "${HOMEBREW_PATH}/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
endif()

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
if(NOT APPLE)
    find_package(assimp REQUIRED)
endif()

# Add glad
add_library(glad STATIC
    external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# Add ImGui source files
set(IMGUI_DIR external/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Project source files
set(SOURCES
    src/main.cpp
    src/model.cpp
    src/drone.cpp
    src/shader.cpp
    src/hud.cpp
    src/stb_image.cpp
    ${IMGUI_SOURCES}
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    external/stb
    ${OPENGL_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
)

if(APPLE)
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${HOMEBREW_PATH}/include
    )
    target_link_directories(${PROJECT_NAME} PRIVATE
        ${HOMEBREW_PATH}/lib
    )
endif()

# Platform-specific settings
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework OpenGL"
        "-framework CoreFoundation"
    )
elseif(UNIX)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${X11_LIBRARIES}
        dl
        pthread
    )
endif()

# Common libraries for all platforms
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glad
    glfw
    glm::glm
    ${ASSIMP_LIBRARIES}
)

# Copy resources
file(COPY ${CMAKE_SOURCE_DIR}/models DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}) 