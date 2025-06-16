//
// Created by MacBook on 25-6-1.
//

#ifndef FLOOR_H
#define FLOOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shaders/shader_m.h"

class Floor {
  public:
	unsigned int floorVAO, floorVBO;
    void set() {
    	float floorVertices[] = {
    		// 位置
    		-10.f, -0.f, -10.f,
			 10.f, -0.f, -10.f,
			-10.f, -0.f,  10.f,

    		 10.f, -0.f, -10.f,
   	        -10.f, -0.f,  10.f,
			 10.f, -0.f,  10.f,
		};
    	// 创建光源立方体的VAO和VBO
    	glGenVertexArrays(1, &floorVAO);
    	glGenBuffers(1, &floorVBO);

    	glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

    	glBindVertexArray(floorVAO);
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    	glEnableVertexAttribArray(0);
    }

    void render(Shader floorShader, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {

    	// 绘制光源立方体
    	floorShader.use();
    	floorShader.setMat4("projection", projection);
    	floorShader.setMat4("view", view);
        floorShader.setMat4("model", model);

    	// 绘制立方体
    	glBindVertexArray(floorVAO);
    	glDrawArrays(GL_TRIANGLES, 0, 6);
    	glBindVertexArray(0);
    }
};
#endif //FLOOR_H
