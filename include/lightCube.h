//
// Created by MacBook on 25-6-9.
//

#ifndef LIGHTCUBE_H
#define LIGHTCUBE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"


class LightCube {
  public:
	unsigned int lightCubeVAO, lightCubeVBO;
    void set() {
    	float lightCubeVertices[] = {
    		// 位置
    		-0.2f, -0.2f, -0.2f,
			 0.2f, -0.2f, -0.2f,
			 0.2f,  0.2f, -0.2f,
			 0.2f,  0.2f, -0.2f,
			-0.2f,  0.2f, -0.2f,
			-0.2f, -0.2f, -0.2f,

			-0.2f, -0.2f,  0.2f,
			 0.2f, -0.2f,  0.2f,
			 0.2f,  0.2f,  0.2f,
			 0.2f,  0.2f,  0.2f,
			-0.2f,  0.2f,  0.2f,
			-0.2f, -0.2f,  0.2f,

			-0.2f,  0.2f,  0.2f,
			-0.2f,  0.2f, -0.2f,
			-0.2f, -0.2f, -0.2f,
			-0.2f, -0.2f, -0.2f,
			-0.2f, -0.2f,  0.2f,
			-0.2f,  0.2f,  0.2f,

			 0.2f,  0.2f,  0.2f,
			 0.2f,  0.2f, -0.2f,
			 0.2f, -0.2f, -0.2f,
			 0.2f, -0.2f, -0.2f,
			 0.2f, -0.2f,  0.2f,
			 0.2f,  0.2f,  0.2f,

			-0.2f, -0.2f, -0.2f,
			 0.2f, -0.2f, -0.2f,
			 0.2f, -0.2f,  0.2f,
			 0.2f, -0.2f,  0.2f,
			-0.2f, -0.2f,  0.2f,
			-0.2f, -0.2f, -0.2f,

			-0.2f,  0.2f, -0.2f,
			 0.2f,  0.2f, -0.2f,
			 0.2f,  0.2f,  0.2f,
			 0.2f,  0.2f,  0.2f,
			-0.2f,  0.2f,  0.2f,
			-0.2f,  0.2f, -0.2f
		};
    	// 创建光源立方体的VAO和VBO
    	glGenVertexArrays(1, &lightCubeVAO);
    	glGenBuffers(1, &lightCubeVBO);

    	glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(lightCubeVertices), lightCubeVertices, GL_STATIC_DRAW);

    	glBindVertexArray(lightCubeVAO);
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    	glEnableVertexAttribArray(0);
    }

    void render(Shader lightCubeShader, glm::mat4 projection, glm::mat4 view, glm::vec3 lightPos) {

    	// 绘制光源立方体
    	lightCubeShader.use();
    	lightCubeShader.setMat4("projection", projection);
    	lightCubeShader.setMat4("view", view);

    	// 创建光源立方体的模型矩阵，将其放置在光源位置
    	glm::mat4 lightModel = glm::mat4(1.0f);
    	lightModel = glm::translate(lightModel, lightPos); // 移到光源位置
    	lightModel = glm::scale(lightModel, glm::vec3(0.1f)); // 缩小立方体
    	lightCubeShader.setMat4("model", lightModel);

    	// 设置光源颜色
    	lightCubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f); // 白色光源

    	// 绘制立方体
    	glBindVertexArray(lightCubeVAO);
    	glDrawArrays(GL_TRIANGLES, 0, 36);
    	glBindVertexArray(0);
    }
};
#endif //LIGHTCUBE_H
