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

Camera camera(glm::dvec3(0.0, 20.0, 100.0));
double lastX = SCR_WIDTH / 2.0;
double lastY = SCR_HEIGHT / 2.0;
bool firstMouse = true;
double deltaTime = 0.0;
double lastFrame = 0.0;

Gravity gravity(0.1); 

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

    Planet sun(10.0, 1000.0, glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0), "Sun");
    sun.setColor(glm::dvec3(1.0, 1.0, 0.0)); // Bright yellow

    Planet mercury(1.0, 0.06, glm::dvec3(39.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.601), "Mercury");
    mercury.setColor(glm::dvec3(0.6, 0.6, 0.6)); // Gray
    Planet venus(1.8, 0.82, glm::dvec3(72.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.178), "Venus");
    venus.setColor(glm::dvec3(0.8, 0.5, 0.0)); // Orange-brown
    Planet earth(2.0, 1.0, glm::dvec3(100.0, 0.0, 0.0), glm::dvec3(0.0, 0.0 , 1.000), "Earth");
    earth.setColor(glm::dvec3(0.0, 0.0, 1.0)); // Blue
    Planet mars(1.5, 0.11, glm::dvec3(152.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.811), "Mars");
    mars.setColor(glm::dvec3(0.8, 0.2, 0.0)); // Red
    Planet jupiter(8.0, 317.89, glm::dvec3(520.0, 0.0, 0.0), glm::dvec3(0.0, 0.438, 0.0), "Jupiter");
    jupiter.setColor(glm::dvec3(0.9, 0.7, 0.5)); // Light brown
    Planet saturn(7.5, 95.17, glm::dvec3(954.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.324), "Saturn");
    saturn.setColor(glm::dvec3(0.9, 0.8, 0.6)); // Pale yellow
    Planet uranus(4.5, 14.56, glm::dvec3(1922.0, 0.0, 0.0), glm::dvec3(0.0, 0.0 , 0.228), "Uranus");
    uranus.setColor(glm::dvec3(0.5, 0.8, 0.9)); // Light blue
    Planet neptune(4.2, 17.24, glm::dvec3(3006.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.182), "Neptune");
    neptune.setColor(glm::dvec3(0.2, 0.2, 0.8)); // Dark blue

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
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
         
        processInput(window);

        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::dmat4 projection = glm::perspective(glm::radians(camera.Zoom), (double)SCR_WIDTH / (double)SCR_HEIGHT, 0.1, 10000.0);
        glm::dmat4 view = camera.GetViewMatrix();

		gravity.applyAll(deltaTime);

        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // Light properties
        glm::dvec3 lightPos = sun.getPosition();
        glm::dvec3 lightColor = glm::dvec3(1.0, 1.0, 0.8); // Bright yellow light

        shader.setVec3("lightPos", lightPos);
        shader.setVec3("lightColor", lightColor);
        shader.setVec3("viewPos", camera.Position);

        // Draw Sun
        glm::dmat4 model = glm::dmat4(1.0);
        model = glm::translate(model, sun.getPosition());
        shader.setMat4("model", model);
        shader.setVec3("objectColor", sun.getColor());
        shader.setVec3("emissiveColor", glm::dvec3(1.0, 1.0, 0.8)); // Sun is emissive
        sun.update(deltaTime);
        sun.draw();

        // Draw Mercury
        model = glm::dmat4(1.0);
        model = glm::translate(model, mercury.getPosition());
        shader.setMat4("model", model);
        shader.setVec3("objectColor", mercury.getColor());
        shader.setVec3("emissiveColor", glm::dvec3(0.0, 0.0, 0.0)); // Not emissive
        mercury.update(deltaTime);
        mercury.draw();

        // Draw Venus
        model = glm::dmat4(1.0);
        model = glm::translate(model, venus.getPosition());
        shader.setMat4("model", model);
        shader.setVec3("objectColor", venus.getColor());
        shader.setVec3("emissiveColor", glm::dvec3(0.0, 0.0, 0.0));
        venus.update(deltaTime);
        venus.draw();

        // Draw Earth
        model = glm::dmat4(1.0);
        model = glm::translate(model, earth.getPosition());
        shader.setMat4("model", model);
        shader.setVec3("objectColor", earth.getColor());
        shader.setVec3("emissiveColor", glm::dvec3(0.0, 0.0, 0.0));
        earth.update(deltaTime);
        earth.draw();

        // Draw Mars
        model = glm::dmat4(1.0);
        model = glm::translate(model, mars.getPosition());
        shader.setMat4("model", model);
        shader.setVec3("objectColor", mars.getColor());
        shader.setVec3("emissiveColor", glm::dvec3(0.0, 0.0, 0.0));
        mars.update(deltaTime);
        mars.draw();

        // Draw Jupiter
        model = glm::dmat4(1.0);
        model = glm::translate(model, jupiter.getPosition());
        shader.setMat4("model", model);
        shader.setVec3("objectColor", jupiter.getColor());
        shader.setVec3("emissiveColor", glm::dvec3(0.0, 0.0, 0.0));
        jupiter.update(deltaTime);
        jupiter.draw();

        // Draw Saturn
        model = glm::dmat4(1.0);
        model = glm::translate(model, saturn.getPosition());
        shader.setMat4("model", model);
        shader.setVec3("objectColor", saturn.getColor());
        shader.setVec3("emissiveColor", glm::dvec3(0.0, 0.0, 0.0));
        saturn.update(deltaTime);
        saturn.draw();

        // Draw Uranus
        model = glm::dmat4(1.0);
        model = glm::translate(model, uranus.getPosition());
        shader.setMat4("model", model);
        shader.setVec3("objectColor", uranus.getColor());
        shader.setVec3("emissiveColor", glm::dvec3(0.0, 0.0, 0.0));
        uranus.update(deltaTime);
        uranus.draw();

        // Draw Neptune
        model = glm::dmat4(1.0);
        model = glm::translate(model, neptune.getPosition());
        shader.setMat4("model", model);
        shader.setVec3("objectColor", neptune.getColor());
        shader.setVec3("emissiveColor", glm::dvec3(0.0, 0.0, 0.0));
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
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    double xpos = xposIn;
    double ypos = yposIn;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}