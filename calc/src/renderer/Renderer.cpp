#include "src/renderer/Renderer.hpp"

#include "src/renderer/data.hpp"

#include "glad.h"

#include <GLFW/glfw3.h>
#include <cstdio>

namespace Renderer {

// GLFW stuff
GLFWwindow *window = nullptr;
GLFWwindow *otherWindow = nullptr; // TODO: REMOVE AFTER RAYLIB IS GONE
int window_w, window_h;

// GL Stuff
unsigned int VBO = 0;
unsigned int VAO = 0;
unsigned int shaderProgram = 0;

// TODO: REMOVE AFTER RAYLIB IS GONE
void SetContext() {
  otherWindow = glfwGetCurrentContext();
  glfwMakeContextCurrent(window);
}

// TODO: REMOVE AFTER RAYLIB IS GONE
void RestoreContext() {
  if (otherWindow) {
    glfwMakeContextCurrent(otherWindow);
  }
  otherWindow = nullptr;
}

void OnFramebufferResize(GLFWwindow *win, int width, int height) {
  SetContext();
  window_w = width;
  window_h = height;
  glViewport(0, 0, window_w, window_h);
  RestoreContext();
}

bool Init(int width, int height, const char *title) {
  if (glfwInit() == GLFW_FALSE) {
    const char *description;
    glfwGetError(&description);
    printf("Failed to init GLFW %s\n", description);
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    const char *description;
    glfwGetError(&description);
    printf("Failed to create GLFW window %s\n", description);
    glfwTerminate();
    return false;
  }
  window_w = width;
  window_h = height;

  glfwMakeContextCurrent(window);

  gladLoadGL((GLADloadfunc)glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(window, OnFramebufferResize);
  glViewport(0, 0, window_w, window_h);

  /**
   * OPENGL SETUP
   */

  // build shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
  glCompileShader(vertexShader);

  {
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      printf("Vertex Shader Compilation Failed: %s\n", infoLog);
      return false;
    }
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
  glCompileShader(fragmentShader);

  {
    int success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      printf("Fragment Shader Compilation Failed: %s\n", infoLog);
      return false;
    }
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  {
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      printf("Failed to link shader shader. %s\n", infoLog);
      return false;
    }
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // VAO stuff
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Buffer stuff
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);

  // Set the attribute pointers for the shader
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  return true;
}

void BeginDrawing() {
  SetContext();
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void EndDrawing() {
  glfwSwapBuffers(window);
  glfwPollEvents();

  glUseProgram(0);
  RestoreContext();
}

void Destroy() {
  glDeleteProgram(shaderProgram);
  shaderProgram = 0;
  glDeleteBuffers(1, &VBO);
  VBO = 0;
  glDeleteVertexArrays(1, &VAO);
  VAO = 0;
  glfwTerminate();
}

} // namespace Renderer
