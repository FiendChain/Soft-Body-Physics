cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_COMPILER C:/MinGW/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/MinGW/bin/g++.exe)

project("Soft Body Physics")

set(SRC_FILES_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/libs)
set(PROJECT_BINARY_DIR bin)

set(SRC_FILES 
    ${SRC_FILES_DIR}/Body/Body.cpp
    ${SRC_FILES_DIR}/Body/BodyCasting.cpp
    ${SRC_FILES_DIR}/Body/BodyLoader.cpp
    ${SRC_FILES_DIR}/Body/Joint.cpp
    ${SRC_FILES_DIR}/Entities/DragableEntity.cpp
    ${SRC_FILES_DIR}/Entities/DragableParticle.cpp
    ${SRC_FILES_DIR}/Entities/DragablePoint.cpp
    ${SRC_FILES_DIR}/Entities/InteractableEntity.cpp
    ${SRC_FILES_DIR}/Entities/Particle.cpp
    ${SRC_FILES_DIR}/Entities/PhysicsEntity.cpp
    ${SRC_FILES_DIR}/Spring/Spring.cpp
    ${SRC_FILES_DIR}/StaticBody/StaticBody.cpp
    ${SRC_FILES_DIR}/StaticBody/StaticBodyCreation.cpp
    ${SRC_FILES_DIR}/StaticBody/StaticBodyLoader.cpp
    ${SRC_FILES_DIR}/StaticBody/StaticBodyRender.cpp
    ${SRC_FILES_DIR}/StaticBody/StaticJoint.cpp)

include_directories(${SRC_FILES_DIR})
include_directories(${LIB_DIR})

configure_file (
    ${SRC_FILES_DIR}/App/AppConfig.h.in
    ${PROJECT_BINARY_DIR}/AppConfig.h
)
include_directories (build/${PROJECT_BINARY_DIR})

# sfml libraries
set(SFML_DIR ${LIB_DIR}/SFML-2.5.0)
include_directories(${SFML_DIR}/include)
macro(add_sfml_library name)
    add_library(${name} STATIC IMPORTED)
    set_target_properties(${name} PROPERTIES
        IMPORTED_LOCATION "${SFML_DIR}/lib/lib${name}.a"
        INTERFACE_INCLUDE_DIRECTORIES "${SFML_DIR}/include/SFML"
        INTERFACE_COMPILE_DEFINITIONS SFML_STATIC
    )
endmacro()

add_sfml_library(sfml-graphics-s)
add_sfml_library(sfml-window-s)
add_sfml_library(sfml-system-s)
add_sfml_library(freetype)
add_sfml_library(jpeg)
set(SFML_LIBS 
    sfml-graphics-s sfml-window-s sfml-system-s
    winmm gdi32 opengl32 freetype jpeg)

# imgui
add_subdirectory(${LIB_DIR}/imgui)

# imgui-sfml
add_library(imgui-sfml 
    ${LIB_DIR}/imgui-sfml/imgui-SFML.cpp
    ${LIB_DIR}/imgui-sfml/imgui-SFML-addons.cpp)
target_link_libraries(imgui-sfml imgui ${SFML_LIBS})
install(TARGETS imgui-sfml DESTINATION bin)

# base application
add_library(soft_body ${SRC_FILES})
target_compile_definitions(soft_body PUBLIC SFML_STATIC)
target_compile_options(soft_body PUBLIC -Werror=return-type)
target_link_libraries(soft_body imgui imgui-sfml ${SFML_LIBS})

# main
add_executable(main 
    ${SRC_FILES_DIR}/main.cpp
    ${SRC_FILES_DIR}/App/App.cpp
    ${SRC_FILES_DIR}/App/AppInput.cpp
    ${SRC_FILES_DIR}/App/AppLoader.cpp)
target_link_libraries(main soft_body)

# body creator
add_executable(body_creator 
    ${SRC_FILES_DIR}/body_creator.cpp
    ${SRC_FILES_DIR}/BodyCreator/BodyCreator.cpp
    ${SRC_FILES_DIR}/BodyCreator/BodyCreatorRender.cpp)
target_link_libraries(body_creator soft_body)

install(TARGETS soft_body main body_creator DESTINATION bin)
install(FILES build/${PROJECT_BINARY_DIR}/AppConfig.h DESTINATION include)
