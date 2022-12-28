#include "Application.h"

#include <iostream>
#include <string>

using namespace std;

GLFWwindow* Application::m_Window;
int Application::m_Width, Application::m_Height;
float Application::m_Ratio;

Application::Application(const char* name, int width, int height, int samples) {
    this->m_Width = width;
    this->m_Height = height;
    this->m_Ratio = width/height;

    /* Initialize the library */
    if (!glfwInit())
        cout << "Error: GLFW couldn't be initialized!" << endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, samples);

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        cout << "Error: Window couldn't be created." << endl;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);

    if (glewInit() != GLEW_OK)
        cout << "Error: GLEW couldn't be initialized!" << endl;

    cout << glGetString(GL_VERSION) << endl;
}

void Application::Enable(GLenum cap) {
    glEnable(cap);
}

void Application::Disable(GLenum cap) {
    glDisable(cap);
}

void Application::SetWindowHint(int hint, int value) const {
    glfwWindowHint(hint, value);
}
void Application::SetDepthFunction(GLenum function) {
    glDepthFunc(function);
}

void Application::SetBlendFunction(GLenum sfactor, GLenum dfactor) {
    glBlendFunc(sfactor, dfactor);
}