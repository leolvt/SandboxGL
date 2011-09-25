find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(BOUNCE_LIBS 
    ${BOUNCE_LIBS} 
    ${OPENGL_LIBRARIES} 
    ${GLFW_LIBRARIES} 
    ${GLEW_LIBRARY}
    )

set(BOUNCE_SRC ${BOUNCE_SRC} 
    main.cpp 
)

add_executable(Bounce ${BOUNCE_SRC})
target_link_libraries(Bounce ${BOUNCE_LIBS})

install(TARGETS Bounce DESTINATION bin)
