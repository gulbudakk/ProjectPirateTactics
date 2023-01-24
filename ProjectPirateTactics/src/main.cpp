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
#include "PirateTactics/HealthText.h"
#include "WaterRenderer.h"
#include "DepthBuffer.h"
#include "FrameBuffer.h"
#include "WaterObject.h"
#include "PirateTactics/Heart.h"
#include "PirateTactics/GameManager.h"

using namespace std;
using namespace glm;


int main(void)
{
    Application application("Project Pirate Tactics", 1280, 720, 4);
    Application::Enable(GL_DEPTH_TEST);
    Application::Enable(GL_CULL_FACE);
    Application::Enable(GL_CLIP_DISTANCE0);
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
    Object3D rock("res/models/rock.obj");

    unsigned int rows = 7, cols = 7;
    Tilemap tilemap(rows, cols, 2.05, 0);
    objects.push_back(&tilemap);

    Tilemap obstacleTilemap(rows, cols, 2.05, 0.52);
    objects.push_back(&obstacleTilemap);

    for (unsigned int r = 0; r < rows; r++)
    {
        for (unsigned int c = 0; c < cols; c++)
        {
            BoardCubeTile *tile = new BoardCubeTile(camera, object, texture, shader);
            tilemap.Draw(*tile, r, c);
        }
    }

    {
        BoardCubeTile rock1(camera, rock, textureRock, shader);
        rock1.GetTransform().SetScale(vec3(0.3, 0.3, 0.3));
        obstacleTilemap.Draw(rock1, 1, 1);

        BoardCubeTile rock2(camera, rock, textureRock, shader);
        rock2.GetTransform().SetScale(vec3(0.3, 0.3, 0.3));
        obstacleTilemap.Draw(rock2, 1, 2);

        BoardCubeTile rock3(camera, rock, textureRock, shader);
        rock3.GetTransform().SetScale(vec3(0.3, 0.3, 0.3));
        obstacleTilemap.Draw(rock3, 2, 1);

        BoardCubeTile rock4(camera, rock, textureRock, shader);
        rock4.GetTransform().SetScale(vec3(0.3, 0.3, 0.3));
        obstacleTilemap.Draw(rock4, 5, 5);

        BoardCubeTile rock5(camera, rock, textureRock, shader);
        rock5.GetTransform().SetScale(vec3(0.3, 0.3, 0.3));
        obstacleTilemap.Draw(rock5, 5, 4);

        BoardCubeTile rock6(camera, rock, textureRock, shader);
        rock6.GetTransform().SetScale(vec3(0.3, 0.3, 0.3));
        obstacleTilemap.Draw(rock6, 4, 5);

        BoardCubeTile rock7(camera, rock, textureRock, shader);
        rock7.GetTransform().SetScale(vec3(0.3, 0.3, 0.3));
        obstacleTilemap.Draw(rock7, 3, 3);

        BoardCubeTile rock8(camera, rock, textureRock, shader);
        rock8.GetTransform().SetScale(vec3(0.3, 0.3, 0.3));
        obstacleTilemap.Draw(rock8, 3, 3);

        BoardCubeTile rock9(camera, rock, textureRock, shader);
        rock9.GetTransform().SetScale(vec3(0.3, 0.3, 0.3));
        obstacleTilemap.Draw(rock9, 3, 3);
    }

    CameraMovement cameraMovement(camera);
    objects.push_back(&cameraMovement);

    Texture fontTexture("res/fonts/arial.png", GL_REPEAT);
    Shader textShader("res/shaders/FontVertexShader.shader", "res/shaders/FontFragmentShader.shader");
    Font font(fontTexture, "res/fonts/arial.fnt");

    Text text1(font, 1, 1, "3", 6);

    HealthText healthText(text1, textShader);

    healthText.SetPosition(vec2(-0.62f, -0.01f));

    vector<vec3> quadVertexPositions = { vec3(-1, 0, -1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(1, 0, -1), vec3(-1, 0, 1), vec3(1, 0, 1) };
    Object3D waterQuad(quadVertexPositions);
    Shader waterShader("res/shaders/WaterVertexShader.shader", "res/shaders/WaterFragmentShader.shader");

    int reflectionWidth = 320, reflectionHeight = 180,
        refractionWidth = 1280, refractionHeight = 720;

    Texture dudvTexture("res/textures/waterdudvmap.png", GL_REPEAT);
    Texture normalmapTexture("res/textures/waternormalmap.png", GL_REPEAT);
    WaterObject waterObject(camera, reflectionWidth, reflectionHeight, refractionWidth, refractionHeight, waterQuad, waterShader, dudvTexture, normalmapTexture);
    waterObject.GetTransform().SetPosition(vec3(6.12, 1.1, 6.12));
    waterObject.GetTransform().SetScale(vec3(7.15));
    
    vec4 clippingPlane(0, 0, 0, 0);
    vec4 clippingPlaneReflection(0, 1, 0, -waterObject.GetTransform().GetPosition().y - 0.1);
    vec4 clippingPlaneRefraction(0, -1, 0, waterObject.GetTransform().GetPosition().y);

    Object3D heartObject("res/models/heart2.obj");
    Texture diceTexture("res/textures/red.jpeg", GL_REPEAT);
    Shader orthographicShader("res/shaders/OrtographicVertexShader.shader", "res/shaders/OrtographicFragmentShader.shader");
    Heart dice1(camera, heartObject, diceTexture, orthographicShader);
    dice1.GetTransform().SetPosition(vec3(-0.85, 0.7, 0.0));
    dice1.GetTransform().SetScale(vec3(0.1, 0.1, 0.1));

    Object3D ship("res/models/PirateShip.obj");
    Texture shipTexture("res/textures/dice.jpg", GL_CLAMP_TO_BORDER);
    Ship boat(camera, ship, shipTexture, shader, obstacleTilemap);
    boat.GetTransform().SetPosition(vec3(0.0, 1, 0.0));
    boat.GetTransform().SetScale(vec3(0.2, 0.2, 0.2));
    objects.push_back(&boat);

    Player player(boat, healthText);
    GameManager gameManager(player, obstacleTilemap);

    Renderer::GetLight().SetPosition(vec3(6.12, 10.1, 6.12));

    /* Loop until the user closes the window */
    do
    {
        Time::Tick();

        gameManager.Tick();

        //render reflection texture
        waterObject.GetReflectionBuffer().Bind();

        //move the camera below the water

        vec3 cameraPosition = camera.GetPosition();
        float distance = 2 * (cameraPosition.y - waterObject.GetTransform().GetPosition().y -0.1);
        vec3 newPosition = vec3(cameraPosition.x, cameraPosition.y - distance, cameraPosition.z);
        camera.SetPosition(newPosition);
        camera.SetUp(-camera.GetUp());

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Clear();
        }

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Tick(clippingPlaneReflection);
        }

        waterObject.GetReflectionBuffer().Unbind();


        camera.SetPosition(cameraPosition);
        camera.SetUp(-camera.GetUp());

        //render refraction texture

        waterObject.GetRefractionBuffer().Bind();

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Clear();
        }

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Tick(clippingPlaneRefraction);
        }

        waterObject.GetRefractionBuffer().Unbind();

        /* Render here */

        waterObject.Clear();
        healthText.Clear();

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Clear();
        }

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->Tick(clippingPlane);
        }

        waterObject.Tick();

        healthText.Tick(clippingPlane);
        dice1.Tick(clippingPlane);

        /* Swap front and back buffers */
        glfwSwapBuffers(&application.GetWindow());

        /* Poll for and process events */
        glfwPollEvents();
    } 
    while (!glfwWindowShouldClose(&application.GetWindow()) && !Input::GetKey(KeyCode::Escape));

    glfwTerminate();
    return 0;
}