//
// Created by MacBook on 25-6-16.
//

#ifndef SHADOW_H
#define SHADOW_H

#include "../shaders/shader_m.h"
#include "../scene/scene.h"

class Shadow {
  public:
    Shadow();
    void renderShadowMap(Scene scene, Shader& shadowShader, glm::vec3 lightPos);
};



#endif //SHADOW_H
