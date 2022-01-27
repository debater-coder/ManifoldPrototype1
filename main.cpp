#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>

// Forward declarations:
void drawImGuiStuff(GLFWwindow* window, ImGuiIO& io);
void setTheme();

auto showDemoWindow = false;

int main(int argc, char* argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    auto mWindow = glfwCreateWindow(1200, 800, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigDockingWithShift = true;
    io.Fonts->AddFontFromFileTTF("OpenSans-Regular.ttf", 16);
    ImGui::StyleColorsDark();
    setTheme();
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Tell ImGui a new frame is about to begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        drawImGuiStuff(mWindow, io);

        // Renders the ImGUI elements
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    
    }   
    
    glfwTerminate();
    return EXIT_SUCCESS;
}

void drawImGuiStuff(GLFWwindow* window, ImGuiIO& io)
{
    ImGui::DockSpaceOverViewport();
    if (showDemoWindow)
        ImGui::ShowDemoWindow(&showDemoWindow);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {

            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open")) {}
            
            ImGui::Separator();    
            
            if (ImGui::MenuItem("Save", "CTRL+S")) {}
            if (ImGui::MenuItem("Save as", "CTRL+SHIFT+S")) {}  // Disabled item

            ImGui::Separator();

            if (ImGui::MenuItem("Exit")) glfwSetWindowShouldClose(window, true);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {

            if (ImGui::MenuItem("Demo")) {
                showDemoWindow = true;
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Begin("Hello World");
    ImGui::Text("Hello I am text!");
    ImGui::End();

    ImGui::Begin("Boring Window");
    ImGui::Text("Hello I am boring window.");
    ImGui::End();

    ImGui::Begin("Console");
    ImGui::Text("Hello I am important console.");
    ImGui::End();
}

void setTheme()
{
    ImGui::GetStyle().WindowRounding = 4.0f;// <- Set this on init or use ImGui::PushStyleVar()
    ImGui::GetStyle().ChildRounding = 4.0f;
    ImGui::GetStyle().FrameRounding = 4.0f;
    ImGui::GetStyle().GrabRounding = 4.0f;
    ImGui::GetStyle().PopupRounding = 4.0f;
    ImGui::GetStyle().ScrollbarRounding = 4.0f;
}
