#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out vec4 fragPosLightSpace;  // 新增：光源空间的片段位置

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;  // 光源的投影和视图矩阵组合

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    // Normal = aNormal;
    TexCoords = aTexCoord;

    // 计算光源空间的片段位置
    fragPosLightSpace = lightSpaceMatrix * model * vec4(aPos, 1.0);
}