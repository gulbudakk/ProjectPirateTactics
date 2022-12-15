#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

using namespace std;

class Application
{
private:
    static GLFWwindow* m_Window;
    static int m_Width;
    static int m_Height;
    static float m_Ratio;

public:
    Application(const char* name, int width, int height, int samples);

    void Enable(GLenum cap) const;
    void SetWindowHint(int hint, int value) const;
    void SetDepthFunction(GLenum function) const;

    static GLFWwindow& GetWindow() { return *m_Window; };
    static int GetHeight() { return m_Height; };
    static int GetWidth() { return m_Width; };
    static float GetRatio() { return m_Ratio; };
};