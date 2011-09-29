find_package(GLFW REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(FromScratch_LIBS 
    ${FromScratch_LIBS} 
    ${OPENGL_LIBRARIES} 
    ${GLFW_LIBRARIES} 
    ${GLUT_LIBRARIES} 
    ${GLEW_LIBRARY}
    )

set(FromScratch_SRC 
    ${FromScratch_SRC} 
    main.cpp 
    )

add_executable(FromScratch ${FromScratch_SRC})
target_link_libraries(FromScratch ${FromScratch_LIBS})

install(TARGETS FromScratch DESTINATION bin)
