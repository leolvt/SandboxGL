find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(Legacy_LIBS 
    ${Legacy_LIBS} 
    ${OPENGL_LIBRARIES} 
    ${GLUT_LIBRARIES} 
    ${GLEW_LIBRARY}
    )

set(Legacy_SRC 
    ${Legacy_SRC} 
    main.cpp 
    )

add_executable(Legacy ${Legacy_SRC})
target_link_libraries(Legacy ${Legacy_LIBS})

install(TARGETS Legacy DESTINATION bin)
