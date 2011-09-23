find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(HGL_LIBS ${HGL_LIBS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY})
set(HGL_SRC ${HGL_SRC} 
    Util.cpp
    main.cpp 
)

add_executable(helloGL ${HGL_SRC})
target_link_libraries(helloGL ${HGL_LIBS})
