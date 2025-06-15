#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // ambient
    vec4 ambient = texture(texture_diffuse1, TexCoords) * 0.1f;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * (texture(texture_diffuse1, TexCoords)) * 0.7f ;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec4 specular = (texture(texture_diffuse1, TexCoords)) * spec * 0.2f;

    FragColor = (diffuse + ambient + specular) * texture(texture_diffuse1, TexCoords);
    // FragColor = texture(texture_diffuse1, TexCoords);
}