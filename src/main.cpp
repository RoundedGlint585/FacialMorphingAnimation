
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "../include/Shader.h"
#include "../include/ObjParser.h"
#include "../include/Mesh.h"
#include "../include/Camera.h"


constexpr uint32_t width = 800;
constexpr uint32_t height = 600;

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(width, height, "Morphing animation", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);

    glewInit();
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    Shader morphingShader("shaders/MorphingWithLightVertex.glsl", "shaders/MorphingWithLightFragment.glsl");


    auto restPose = objParser::parseFile("objects/static.obj");
    auto surprisedPose = objParser::parseFile("objects/surprised.obj");
    auto angryPose = objParser::parseFile("objects/angry.obj");
    Mesh headMesh = Mesh(std::get<1>(restPose), {std::get<0>(restPose), std::get<0>(surprisedPose),
                                                 std::get<0>(angryPose)}); // TODO: rework memory layout for models


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Camera camera({0.0f, 0.8f, 3.f});


    std::vector<float> coefs = {0.0f, 0.0f};
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        morphingShader.use();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view =  camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
        morphingShader.setMat4("model", model);
        morphingShader.setMat4("view", view);
        morphingShader.setMat4("projection", projection);
        morphingShader.setVec3("lightColor", {1.0f,1.0f,1.0f});
        morphingShader.setVec3("lightPos", camera.getPos());
        morphingShader.setFloatArray("coefs", coefs);
        headMesh.draw(morphingShader);

        // GUI
        ImGui::Begin("Coefficient window");
        ImGui::SliderFloat("Surprised", &coefs[0], 0.0f, 1.0f);
        ImGui::SliderFloat("Angry", &coefs[1], 0.0f, 1.0f);
        ImGui::End();

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