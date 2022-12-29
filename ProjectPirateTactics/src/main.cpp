#include <GL/glew.h>
#include <GL/GLU.h>  
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <cstdint>

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
#include "PirateTactics/BoardCubeTile.h"
#include "Tilemap.h"
#include "ui/Font.h"
#include "ui/Text.h"
#include "ui/TextRenderer.h"
#include "PirateTactics/ScoreText.h"
#include "WaterRenderer.h"
#include "DepthBuffer.h"
#include "FrameBuffer.h"

using namespace std;
using namespace glm;


int main(void)
{
    Application application("Project Pirate Tactics", 1280, 720, 4);
    Application::Enable(GL_DEPTH_TEST);
    Application::Enable(GL_CULL_FACE);
    Application::SetDepthFunction(GL_LESS);

    //glClearColor(0.8f, 1, 1, 0.0f);

    Input::SetMousePosition(Application::GetWidth() / 2, Application::GetHeight() / 2);

    // Ensure we can capture the escape key being pressed below
    Input::SetInputMode(GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    Input::SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    vec3 position(2, 3, 2);
    vec2 angle(-2.355f, -0.795f);
    Camera camera(position, angle, 45.0f, 0.1f, 100.0f);

    vector<GameObject*> objects;

    Texture textureRock("res/textures/grey.png", GL_REPEAT);
    Texture texture("res/textures/dirt.png", GL_REPEAT);

    Shader shader("res/shaders/StandardVertexShading.shader", "res/shaders/StandardFragmentShading.shader");
    Object3D object("res/models/cube.obj");

    unsigned int rows = 4, cols = 4;
    Tilemap tilemap(rows, cols, 2.1, 0);
    objects.push_back(&tilemap);

    Tilemap obstacleTilemap(rows, cols, 2.1, 1);
    objects.push_back(&obstacleTilemap);

    for (unsigned int r = 0; r < rows; r++)
    {
        for (unsigned int c = 0; c < cols; c++)
        {
            BoardCubeTile *tile = new BoardCubeTile(camera, object, texture, shader);
            tilemap.Draw(*tile, r, c);
        }
    }

    BoardCubeTile rock1(camera, object, textureRock, shader);
    obstacleTilemap.Draw(rock1, 2, 2);

    CameraMovement cameraMovement(camera);
    objects.push_back(&cameraMovement);

    Texture fontTexture("res/fonts/arial.png", GL_REPEAT);
    Shader textShader("res/shaders/FontVertexShader.shader", "res/shaders/FontFragmentShader.shader");
    Font font(fontTexture, "res/fonts/arial.fnt");

    Text text1(font, 1, 1, "6", 5);
    Text text2(font, 1, 1, "6", 5);

    ScoreText scoreText1(text1, textShader);
    ScoreText scoreText2(text2, textShader);

    objects.push_back(&scoreText1);
    objects.push_back(&scoreText2);

    scoreText1.SetPosition(vec2(-0.9f, 0.0f));
    scoreText2.SetPosition(vec2(0.9f, 0.0f));

    vector<vec3> quadVertexPositions = { vec3(-1, 0, -1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(1, 0, -1), vec3(-1, 0, 1), vec3(1, 0, 1) };
    Object3D waterQuad(quadVertexPositions);

    Transform waterTransform;
    Shader waterShader("res/shaders/WaterVertexShader.shader", "res/shaders/WaterFragmentShader.shader");
    WaterRenderer waterRenderer(camera, waterQuad, waterTransform, waterShader);

    waterTransform.SetPosition(vec3(3.15 , 1.1, 3.15));
    waterTransform.SetScale(vec3(4.15));

    int reflectionWidth = 320, reflectionHeight = 180,
        refractionWidth = 1280, refractionHeight = 720;

    Texture depthTexture(refractionWidth, refractionHeight, NULL, GL_DEPTH_COMPONENT32);
    DepthBuffer depthBuffer(reflectionWidth, reflectionHeight);

    FrameBuffer reflectionBuffer(reflectionWidth, reflectionHeight, depthBuffer);
    FrameBuffer refractionBuffer(refractionWidth, refractionHeight, depthTexture);

    reflectionBuffer.Unbind();

    BoardCubeTile rock10(camera, object, reflectionBuffer.GetTexture(), shader);
    rock10.GetTransform().SetPosition(vec3(3, 3, -1));

    /* Loop until the user closes the window */
    do
    {
        Time::Tick();

        /* Render here */
        waterRenderer.Clear();

        reflectionBuffer.Bind();

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Clear();
        }

        waterRenderer.Draw();

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Tick();
        }

        reflectionBuffer.Unbind();

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Clear();
        }

        waterRenderer.Draw();

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Tick();
        }

        rock10.Tick();

        /* Swap front and back buffers */
        glfwSwapBuffers(&application.GetWindow());

        /* Poll for and process events */
        glfwPollEvents();
    } 
    while (!glfwWindowShouldClose(&application.GetWindow()) && !Input::GetKey(KeyCode::Escape));

    glfwTerminate();
    return 0;
}