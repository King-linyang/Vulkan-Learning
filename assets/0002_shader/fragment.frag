#version 450
//修饰符指定帧缓冲区的索引
layout (location = 0) out vec4 outColor;
layout(location = 0) in vec3 fragColor;

void main() {
    outColor = vec4(fragColor, 1.0);
}
