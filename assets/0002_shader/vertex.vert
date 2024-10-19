#version 450
//输入
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec3 inColor;

//输出
layout (location = 0) out vec3 fragColor;


void main() {
    //位置、颜色通过外部传入
    gl_Position = vec4(inPosition, 0.0, 1.0);
    fragColor = inColor;
}
