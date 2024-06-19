#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <cassert>
#include <unordered_map>

#include "material.h"
#include "shader.h"
#include "camera.h"
#include "math.h"
#include "shape.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
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

mat4 shapeModel{1.0f};
/////////////////////////////////////////////////////////////////////

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

    Shader pongShader{"shaders/lightning_pong.vs", "shaders/lightning_pong.fs"};
    Shader gouraudShader{"shaders/lightning_gouraud.vs", "shaders/lightning_gouraud.fs"};

    Shader lightShader{"shaders/mvp.vs", "shaders/color.fs"};
    Shader lightDirShader{"shaders/mvp.vs", "shaders/color.fs"};

    vec3 shapePos{0, 0, -1.0f};

    float lineVertices[] = {
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
    std::string lightningModel = "Pong";
    std::vector<std::string> lightningModels{"Pong", "Gouraud"};

    std::string material = "Coral";
    std::unordered_map<std::string, Material> materialMap{
        {"Coral", coral},
        {"Emerald", emerald},
        {"Gold", gold},
    };

    std::string shape = "Cube";
    std::string lightShape = "Cube";
    std::unordered_map<std::string, Shape> shapeMap{
        {"Cube", Shape{ShapeType::CUBE}},
        {"Pyramid", {ShapeType::PYRAMID}},
        {"Cuboid", {ShapeType::CUBOID}},
    };

    bool rotateLight = false;
    bool showLightDirection = true;
    //////////////////////////////////

    auto updateLightPos = [&](const vec3& v = lightPos)
    {
        lightPos = v;
        lineVertices[0] = lightPos.x;
        lineVertices[1] = lightPos.y;
        lineVertices[2] = lightPos.z;
        glBindBuffer(GL_ARRAY_BUFFER, lightDirVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);
    };

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
                if (ImGui::SliderFloat("Pitch", &camera.Pitch, -PITCH, PITCH, "%f.1", 0))
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
                    for (const auto& [key, val] : materialMap)
                    {
                        if (ImGui::Selectable(key.c_str(), key == material))
                        {
                            material = key;
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
                if (ImGui::TreeNode("Model"))
                {
                    for (const auto& model : lightningModels)
                    {
                        if (ImGui::Selectable(model.c_str(), lightningModel == model))
                        {
                            lightningModel = model;
                        }
                    }
                    ImGui::TreePop();
                }

                ImGui::Checkbox("Rotate", &rotateLight);
                ImGui::Checkbox("Direction", &showLightDirection);

                ImGui::SeparatorText("Light position");

                if (ImGui::SliderFloat("X-axis", &lightPos.x, -5.0f, 5.0f, "%f.1", 0))
                {
                    updateLightPos();
                }
                if (ImGui::SliderFloat("Y-axis", &lightPos.y, -5.0f, 5.0f, "%f.1", 0))
                {
                    updateLightPos();
                }
                if (ImGui::SliderFloat("Z-axis", &lightPos.z, -5.0f, 5.0f, "%f.1", 0))
                {
                    updateLightPos();
                }
            }
            ImGui::EndGroup();
        }

        ImGui::End();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 view = camera.GetViewMatrix();
        mat4 projection = perspective(radians(camera.Zoom), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);

        ////// Light //////
        mat4 lightModel{1.0f};

        if (rotateLight)
        {
            updateLightPos(vec3{static_cast<float>(sin(glfwGetTime() * 2.0f) * 2),
                                static_cast<float>(sin(glfwGetTime() * 0.7f) * 2),
                                static_cast<float>(sin(glfwGetTime() * 1.3f) * 2)});
        }
        lightModel = translate(lightModel, lightPos);
        lightModel = scale(lightModel, vec3{0.3f});
        lightModel = rotate(lightModel, radians(55.0f), vec3{0.5f, 0, 0});

        lightShader.use();
        lightShader.setVec3("Color", lightColor);

        lightShader.setMat4("model", lightModel);
        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);

        shapeMap.at(lightShape).Draw(lightShader);
        ///////////////////////

        ////// Geometry shape //////
        auto objMaterial = materialMap.at(material);

        auto shapeShader = &pongShader;

        if (lightningModel == "Gouraud")
        {
            shapeShader = &gouraudShader;
        }

        shapeShader->use();

        shapeShader->setVec3("objectColor", objMaterial.color);
        shapeShader->setVec3("viewPos", camera.Position);

        shapeShader->setVec3("light.position", lightPos);
        shapeShader->setVec3("light.color", lightColor);
        shapeShader->setVec3("light.ambient", lightAmbient);
        shapeShader->setVec3("light.diffuse", lightDiffuse);
        shapeShader->setVec3("light.specular", lightSpecular);

        shapeShader->setVec3("material.ambient", objMaterial.ambient);
        shapeShader->setVec3("material.diffuse", objMaterial.diffuse);
        shapeShader->setVec3("material.specular", objMaterial.specular);
        shapeShader->setFloat("material.shininess", objMaterial.shininess);

        shapeShader->setMat4("model", shapeModel);
        shapeShader->setMat4("view", view);
        shapeShader->setMat4("projection", projection);

        auto normalMatrix = mat3{shapeModel}.transpose().inverse();
        shapeShader->setMat3("normal", normalMatrix);

        shapeMap.at(shape).Draw(pongShader);
        ///////////////////////

        ////// Light direction //////
        if (showLightDirection)
        {
            lightDirShader.use();

            lightDirShader.setMat4("model", mat4{1.0f});
            lightDirShader.setMat4("view", view);
            lightDirShader.setMat4("projection", projection);
            lightDirShader.setVec3("Color", vec3{0, 1.0f, 0});

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

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    const auto rotationSpeed = 5.0f;

    shapeModel = rotate(shapeModel, radians(yoffset * rotationSpeed), vec3{1, 0, 0});
}
