#version 450
//修饰符指定帧缓冲区的索引
layout (location = 0) in vec3 fragColor;
layout (location = 1) in vec2 fragTexCoord;

//输出颜色
layout (location = 0) out vec4 outColor;

//采样器
layout (binding = 1) uniform sampler2D texSampler;

void main() {
    outColor = texture(texSampler, fragTexCoord);
}
