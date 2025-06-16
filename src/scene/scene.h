//
// Created by MacBook on 25-6-15.
//

#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <memory>
#include "model.h"
#include "../shaders/shader_m.h"

class Scene {
public:
    Scene();
    void render(Shader& shader) {

        for (auto& model : models) {
            shader.use();
            // 设置通用的 uniforms，如投影矩阵、视图矩阵等
            // shader->setMat4("projection", projection);
            // shader->setMat4("view", view);

            // 可以根据模型的类型或其他条件设置特定的 uniforms
            if (model.hasTexture) {
                shader.setBool("useTexture", true);
            } else {
                shader.setBool("useTexture", false);
            }
            model.Draw(shader);
        }

        // 后续可添加软阴影渲染的逻辑
        // 例如，渲染深度图
        // glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        // glClear(GL_DEPTH_BUFFER_BIT);
        // ...
    }
    void addModel(Model model)
    {
        models.emplace_back(model);
    }

private:
    std::vector<Model> models;
    // 后续可添加用于软阴影渲染的相关成员变量，如帧缓冲对象、深度纹理等
    // unsigned int depthMapFBO;
};
#endif //SCENE_H
