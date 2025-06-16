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
uniform bool useTexture;

void main()
{

    if (useTexture) {
        // ambient
        vec3 ambient = texture(texture_diffuse1, TexCoords).rgb * 0.1f;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = (texture(texture_diffuse1, TexCoords)).rgb * 0.7f * diff;

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
        vec3 specular = (texture(texture_diffuse1, TexCoords)).rgb * spec * 0.2f;
        FragColor = vec4(diffuse + ambient + specular, 1.f);
    } else {
        // ambient
        vec3 ambient = vec3(0.1f, 0.1f, 0.1f);

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = vec3(0.7f, 0.7f, 0.7f) * diff;

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
        vec3 specular = vec3(0.2f, 0.2f, 0.2f) * spec;
        FragColor = vec4(diffuse + ambient + specular, 1.f);
    }


    // FragColor = texture(texture_diffuse1, TexCoords);
}