#version 450
//输入
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoord;

//输出
layout (location = 0) out vec3 fragColor;
layout (location = 1) out vec2 fragTexCoord;

layout (binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

void main() {
    //模型，视图，投影矩阵
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    fragColor = inColor;
    //将纹理坐标传递给片段着色器
    fragTexCoord = inTexCoord;
}
