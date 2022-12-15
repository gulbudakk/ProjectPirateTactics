#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>

#include "Application.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Input.h"
#include "Time.h"

#include "PirateTactics/CameraMovement.h"
#include "Texture.h"

using namespace std;
using namespace glm;

int main(void)
{
    Application application("Project Pirate Tactics", 1280, 720, 4);
    application.Enable(GL_DEPTH_TEST);
    application.Enable(GL_CULL_FACE);
    application.SetDepthFunction(GL_LESS);
    
    //glClearColor(0.4f, 0.9f, 0.9f, 0.0f);

    Input::SetMousePosition(Application::GetWidth() / 2, Application::GetHeight() / 2);

    // Ensure we can capture the escape key being pressed below
    Input::SetInputMode(GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    Input::SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    vec3 position(2, 3, 2);
    vec2 angle(-2.355f, -0.795f);
    Camera camera(position, angle, 45.0f, 0.1f, 100.0f);

    Texture texture("res/textures/dirt.png", GL_REPEAT);

    Shader shader("res/shaders/TextureVertexShader.shader", "res/shaders/TextureFragmentShader.shader");

    Object3D object("res/models/cube.obj", shader);

    Renderer renderer(camera, object, texture);

    CameraMovement cameraMovement(camera);

    /* Loop until the user closes the window */
    do
    {
        Time::Tick();

        cameraMovement.Tick();
        
        /* Render here */
        renderer.Clear();

        renderer.Draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(&application.GetWindow());

        /* Poll for and process events */
        glfwPollEvents();
    } 
    while (!glfwWindowShouldClose(&application.GetWindow()) && !Input::GetKey(KeyCode::Escape));

    glfwTerminate();
    return 0;
}