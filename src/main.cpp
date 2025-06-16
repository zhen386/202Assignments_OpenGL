//
// Created by zhen on 25-4-24.
//
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "shaders/shader_m.h"
#include "camera/camera.h"
#include <../src/scene/model.h>
#include <../src/scene/lightCube.h>
#include "../src/scene/scene.h"
#include <../src/scene/floor.h>

#include <iostream>

const char* vertexShader = "../src/shaders/assignment0/assignment0.vert";
const char* fragmentShader = "../src/shaders/assignment0/assignment0.frag";
const char* lightCubeVertexShader = "../src/shaders/assignment0/lightCube.vert";
const char* lightCubeFragmentShader = "../src/shaders/assignment0/lightCube.frag";
const char* shadowMapVertexShader = "../src/shaders/assignment0/shadow.vert";
const char* shadowMapFragmentShader = "../src/shaders/assignment0/shadow.frag";


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// unsigned int loadTexture(const char *path);
// void loadModel(std::string path);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

// 摄像机创建与设置
Camera camera(glm::vec3(0.0f, 1.f, 3.0f));

// 跟踪上一帧渲染所用的时间，用于统一不同设备的视角移动速度
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

// 鼠标第一次移动
bool firstMouse = true;

// 光源位置
glm::vec3 lightPos(1.2f, 1.5f, 1.5f);
float lightSpeed = 1.f;
float lightRadius = 1.5f;  // 光源圆周运动的半径


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "202Assignments", NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader sceneShader(vertexShader, fragmentShader);
    Shader lightCubeShader(lightCubeVertexShader, lightCubeFragmentShader);
    Shader shadowShader(shadowMapVertexShader, shadowMapFragmentShader);
    // Shader floorShader("../src/shaders/floor.vert", "../src/shaders/floor.frag");
    Model marry("../assets/mary/Marry.obj");
    Model floor("../assets/floor/floor.obj", false);

    Scene scene;

    scene.addModel(marry);
    scene.addModel(floor);

    LightCube lightCube;
    lightCube.set();

    // ImGui::CreateContext();
    // ImGui_ImplGlfw_InitForOpenGL(window, true);
    // ImGui_ImplOpenGL3_Init("#version 330 core"); // 匹配你的 OpenGL 版本
    // ImGui::StyleColorsDark(); // 设置界面风格

    // // 模型变换参数
    // glm::vec3 modelTranslation(0.0f, 0.0f, 0.0f);
    // glm::vec3 modelScale(1.0f, 1.0f, 1.0f);
    // glm::vec3 modelRotation(0.0f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sceneShader.use();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float lightAngle = currentFrame * lightSpeed;  // 基于时间的角度
        lightPos.x = cos(lightAngle) * lightRadius;    // X坐标随cos变化
        lightPos.z = sin(lightAngle) * lightRadius;    // Z坐标随sin变化
        lightPos.y = sin(lightAngle * 0.3f) * 0.5f * -lightRadius + 1.8f;
        sceneShader.setVec3("lightPos", lightPos);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        sceneShader.setMat4("projection", projection);
        sceneShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

        // glm::mat4 model = glm::mat4(1.0f);
        // // 先旋转（注意：glm 默认是弧度，若面板给的是角度，需转换）
        // glm::vec3 rotationRadians = glm::radians(modelRotation);
        // model = glm::rotate(model, rotationRadians.x, glm::vec3(1, 0, 0));
        // model = glm::rotate(model, rotationRadians.y, glm::vec3(0, 1, 0));
        // model = glm::rotate(model, rotationRadians.z, glm::vec3(0, 0, 1));
        // // 再平移、缩放
        // model = glm::translate(model, modelTranslation);
        // model = glm::scale(model, modelScale);

        sceneShader.setMat4("model", model);
        shadowShader.setMat4("model", model);
        sceneShader.setVec3("viewPos", camera.Position);

        // scene.render(sceneShader);


        // 绘制人物模型
        sceneShader.setBool("useTexture", true); // 设置使用纹理标志
        marry.Draw(sceneShader);

        // 绘制地板
        sceneShader.setBool("useTexture", false); // 设置不使用纹理标志
        floor.Draw(sceneShader);

        lightCube.render(lightCubeShader, projection, view, lightPos);
        // floor.render(floorShader, projection, view, model);

        // // 开始新的 ImGUI 帧
        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();
        //
        // // ********** 在这里创建你的参数面板 **********
        // ImGui::Begin("Model properties");
        // {
        //     ImGui::Text("Translation");
        //     ImGui::DragFloat3("##Trans", &modelTranslation[0], 0.1f, -10.0f, 10.0f); // 拖动调整平移，范围 -10~10，步长 0.1
        //
        //     ImGui::Text("Scale");
        //     ImGui::DragFloat3("##Scale", &modelScale[0], 0.1f, 0.1f, 10.0f); // 缩放，范围 0.1~10
        //
        //     ImGui::Text("Rotation");
        //     ImGui::DragFloat3("##Rot", &modelRotation[0], 1.0f, 0.0f, 360.0f); // 旋转（角度），范围 0~360，步长 1
        // }
        // ImGui::End();
        // // 渲染 ImGUI 内容
        // ImGui::Render();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
