#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#include "Camera.h"
#include "Gravity.h"
#include "Planet.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 20.0f, 100.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Gravity gravity(0.1f); 

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar System", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader shader(RESOURCES_PATH "Sphere/Sphere.vert", RESOURCES_PATH "Sphere/Sphere.frag");

    Planet sun(10.0f, 1000.0f, glm::vec3(0.0f), glm::vec3(0.0f), "Sun");

    Planet mercury(1.0f, 0.055f, glm::vec3(5.8f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 6.55f), "Mercury");
    Planet venus(1.8f, 0.815f, glm::vec3(10.8f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.79f), "Venus");
    Planet earth(2.0f, 1.0f, glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.08f), "Earth");
    Planet mars(1.5f, 0.107f, glm::vec3(22.8f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 3.29f), "Mars");
    Planet jupiter(8.0f, 317.8f, glm::vec3(77.9f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.79f), "Jupiter");
    Planet saturn(7.5f, 95.2f, glm::vec3(143.3f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.33f), "Saturn");
    Planet uranus(4.5f, 14.6f, glm::vec3(287.3f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.94f), "Uranus");
    Planet neptune(4.2f, 17.2f, glm::vec3(449.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.75f), "Neptune");

    sun.setStatic(true);
    gravity.addObject(&sun);
    gravity.addObject(&mercury);
    gravity.addObject(&venus);
    gravity.addObject(&earth);
    gravity.addObject(&mars);
	gravity.addObject(&jupiter);
	gravity.addObject(&saturn);
	gravity.addObject(&uranus);
	gravity.addObject(&neptune);


    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        if (deltaTime > 0.1f) deltaTime = 0.1f;
         
        processInput(window);

        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
        glm::mat4 view = camera.GetViewMatrix();

		gravity.applyAll(deltaTime);

        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, sun.getPosition());
        shader.setMat4("model", model);
        sun.update(deltaTime);
        sun.draw();

        model = glm::mat4(1.0f);
        model = glm::translate(model, earth.getPosition());
		shader.setMat4("model", model);
		earth.update(deltaTime);
		earth.draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, mercury.getPosition());
		shader.setMat4("model", model);
		mercury.update(deltaTime);
		mercury.draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, venus.getPosition());
		shader.setMat4("model", model);
		venus.update(deltaTime);
		venus.draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, mars.getPosition());
		shader.setMat4("model", model);
		mars.update(deltaTime);
		mars.draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, jupiter.getPosition());
		shader.setMat4("model", model);
		jupiter.update(deltaTime);
		jupiter.draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, saturn.getPosition());
		shader.setMat4("model", model);
		saturn.update(deltaTime);
		saturn.draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, uranus.getPosition());
		shader.setMat4("model", model);
		uranus.update(deltaTime);
		uranus.draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, neptune.getPosition());
        shader.setMat4("model", model);
		neptune.update(deltaTime);
		neptune.draw();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
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
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
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