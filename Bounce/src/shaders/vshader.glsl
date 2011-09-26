#version 120
attribute vec2 InVertex;
attribute vec3 InColor;
uniform mat4 ModelView;
varying vec3 f_color;
void main(void) {
    gl_Position = ModelView * vec4(InVertex, 0.0, 1.0);
    f_color = InColor;
}
