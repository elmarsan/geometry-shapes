#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <cassert>
#include <iostream>
#include <unordered_map>
#include <map>
#include <cmath>
#include <memory>

#include "shader.h"
#include "camera.h"
#include "math.h"
#include "shape.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

int screenWidth = 1200;
int screenHeight = 800;

Camera camera{vec3{0, 1.0f, 5.0f}};

bool firstMouse = true;
float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;

// timing
float deltaTime = 0;
float lastFrame = 0;

// lightning
vec3 objectColor{1.0f, 0.5f, 0.31f};

vec3 lightPos{1.2, 1.85f, -1.0f};
vec3 lightColor{2.0f, 1.0f, 1.0f};
vec3 lightAmbient{0.2f};
vec3 lightDiffuse{0.5f};
vec3 lightSpecular{1.0f};

////////////////////////////// COLORS ////////////////////////////////
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};

/* struct Light : public Material */
/* { */
/*     vec3 ambient = vec3{0.2f}; */
/*     vec3 diffuse = vec3{0.5f}; */
/*     vec3 specular = vec3{1.0f}; */
/* }; */

struct ObjectColor
{
    /* vec3 color; */
    Material material;
    /* Light light; */
};

ObjectColor coral{
    /* vec3{1.0f, 0.5f, 0.31f}, */
    Material{
        vec3{1.0f, 0.5f, 0.31f},
        vec3{1.0f, 0.5f, 0.31f},
        vec3{0.5f},
        32.0f,
    },
};

ObjectColor emerald{
    /* vec3{80, 200, 120}, */
    Material{
        vec3{0.0215f, 0.1745f, 0.0215f},
        vec3{0.07568f, 0.61424f, 0.07568f},
        vec3{0.633f, 0.727811f, 0.633f},
        76.0f,
    },
};

mat4 shapeModel{1.0f};
/////////////////////////////////////////////////////////////////////

// T(x,y,z) * R * T(-x,-y,-z)
mat4 rotateAround(const float rad, const vec3& point, const vec3& axis)
{
    auto t1 = translate(mat4{1.0f}, point * -1);
    auto r = rotate(t1, rad, axis);
    auto t2 = translate(r, point);
    return t2 * r * t1;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    auto* window = glfwCreateWindow(screenWidth, screenHeight, "Geometry shapes", nullptr, nullptr);
    assert(window != nullptr && "Failed to create GLFW Window");

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) && "Failed to initialize GLAD");
    glEnable(GL_DEPTH_TEST);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    Shader shapeShader{"shape.vert", "shape.frag"};
    Shader lightShader{"light_source.vert", "light_source.frag"};
    Shader lightDirShader{"light_direction.vert", "light_direction.frag"};

    vec3 shapePos{0, 0, -1.0f};

    float lineVertices[] = {
        /* 10, 10, 0, 0, 0, 0 */
        lightPos.x, lightPos.y, lightPos.z, shapePos.x, shapePos.y, shapePos.z,
    };

    GLuint lightDirVAO, lightDirVBO;
    glGenVertexArrays(1, &lightDirVAO);
    glGenBuffers(1, &lightDirVBO);
    glBindVertexArray(lightDirVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lightDirVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    ////////// ImGui options //////////
    std::string color = "Coral";
    std::unordered_map<std::string, ObjectColor> colorMap{
        {"Coral", coral},
        {"Emerald", emerald},
    };

    std::string shape = "Cube";
    std::string lightShape = "Cube";
    std::map<std::string, Shape> shapeMap{
        {"Cube", Shape{ShapeType::CUBE}},
        {"Pyramid", {ShapeType::PYRAMID}},
        {"Cuboid", {ShapeType::CUBOID}},
    };

    bool rotateLight = true;
    bool showLightDirection = true;
    //////////////////////////////////

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Options", nullptr, ImGuiWindowFlags_MenuBar);
        {
            // Camera options
            ImGui::BeginGroup();
            {
                ImGui::Text("Camera");
                ImGui::SliderFloat("Zoom", &camera.Zoom, 1, ZOOM, "%f.1", 0);
                if (ImGui::SliderFloat("Pitch", &camera.Pitch, 1, PITCH, "%f.1", 0))
                {
                    camera.Update();
                }
                if (ImGui::SliderFloat("Yaw", &camera.Yaw, -YAW, YAW, "%f.1", 0))
                {
                    camera.Update();
                }
            }
            ImGui::EndGroup();

            // Shape options
            ImGui::BeginGroup();
            {
                ImGui::Text("Geometry shape");
                if (ImGui::TreeNode("Color"))
                {
                    for (const auto& [key, val] : colorMap)
                    {
                        if (ImGui::Selectable(key.c_str(), key == color))
                        {
                            color = key;
                        }
                    }
                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("Type"))
                {
                    for (const auto& [key, val] : shapeMap)
                    {
                        if (ImGui::Selectable(key.c_str(), key == shape))
                        {
                            shape = key;
                        }
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::EndGroup();

            // Light options
            ImGui::BeginGroup();
            {
                ImGui::Text("Lightning");
                ImGui::Checkbox("Rotate", &rotateLight);
                ImGui::Checkbox("Direction", &showLightDirection);
            }
            ImGui::EndGroup();
        }

        ImGui::End();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // camera/view transformation
        mat4 view = camera.GetViewMatrix();
        mat4 projection = perspective(radians(camera.Zoom), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);

        ////// Light //////
        mat4 lightModel{1.0f};

        lightModel = translate(lightModel, lightPos);
        /* if (rotateLight) */
        /* { */
        /*     lightModel = rotateAround(glfwGetTime() / 3, shapePos, vec3{1.0f, 2, 0}) * */
        /*                  translate(lightModel, vec3{2.0f, 0, 2.0f}); */
        /* } */

        lightShader.use();
        lightShader.setVec3("lightColor", lightColor);

        lightShader.setMat4("model", lightModel);
        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);

        shapeMap.at(lightShape).Draw(lightShader);

        ///////////////////////

        ////// Geometry shape //////
        auto objColor = colorMap.at(color);

        /* shapeModel = translate(shapeModel, vec3{-0.9f, 0.5f, -2.0f}); */
        /* shapeModel = scale(shapeModel, vec3{1.0f}); */

        shapeShader.use();
        shapeShader.setVec3("objectColor", objectColor);
        shapeShader.setVec3("viewPos", camera.Position);

        shapeShader.setVec3("light.position", lightPos);
        shapeShader.setVec3("light.color", lightColor);
        shapeShader.setVec3("light.ambient", lightAmbient);
        shapeShader.setVec3("light.diffuse", lightDiffuse);
        shapeShader.setVec3("light.specular", lightSpecular);

        shapeShader.setVec3("material.ambient", objColor.material.ambient);
        shapeShader.setVec3("material.diffuse", objColor.material.diffuse);
        shapeShader.setVec3("material.specular", objColor.material.specular);
        shapeShader.setFloat("material.shininess", objColor.material.shininess);

        shapeShader.setMat4("model", shapeModel);
        shapeShader.setMat4("view", view);
        shapeShader.setMat4("projection", projection);

        shapeMap.at(shape).Draw(shapeShader);
        ///////////////////////

        ////// Light direction //////
        if (showLightDirection)
        {
            lightDirShader.use();

            lightDirShader.setMat4("model", mat4{1.0f});
            lightDirShader.setMat4("view", view);
            lightDirShader.setMat4("projection", projection);

            glLineWidth(2.0f);
            glBindVertexArray(lightDirVAO);
            glDrawArrays(GL_LINES, 0, 2);
        }
        ////////////////////////////

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, screenWidth, screenHeight);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.Move(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.Move(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.Move(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.Move(RIGHT, deltaTime);

    const auto rotationSpeed = 80.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        shapeModel = rotate(shapeModel, radians(rotationSpeed), vec3{0, 0, 1});
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        shapeModel = rotate(shapeModel, radians(-1 * rotationSpeed), vec3{0, 0, 1});
    }
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    /* float xpos = static_cast<float>(xposIn); */
    /* float ypos = static_cast<float>(yposIn); */

    /* if (firstMouse) */
    /* { */
    /*     lastX = xpos; */
    /*     lastY = ypos; */
    /*     firstMouse = false; */
    /* } */

    /* float xoffset = xpos - lastX; */
    /* float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to top */
    /* lastX = xpos; */
    /* lastY = ypos; */

    /* const float sensitivity = 0.27f;  // change this value to your liking */
    /* xoffset *= sensitivity; */
    /* yoffset *= sensitivity; */

    /* camera.SetEulerAngles(xoffset, yoffset); */
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    const auto rotationSpeed = 5.0f;

    shapeModel = rotate(shapeModel, radians(yoffset * rotationSpeed), vec3{1, 0, 0});
}
