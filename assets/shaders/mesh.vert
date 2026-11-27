layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform vec4 color;

out vec4 v_color;

void main() {
    v_color = color;
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1.0);
}
