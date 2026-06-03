#include "src/renderer/Renderer.hpp"

#include "lib/glm/ext/matrix_clip_space.hpp"
#include "lib/glm/ext/matrix_transform.hpp"
#include "lib/glm/trigonometric.hpp"
#include "src/renderer/data.hpp"

#include "glad.h"
#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"

#include <GLFW/glfw3.h>
#include <cstdio>

namespace Renderer {

// GLFW stuff
GLFWwindow *window = nullptr;
int window_w, window_h;

// GL Stuff
unsigned int VBO = 0;
unsigned int VAO = 0;
unsigned int shaderProgram = 0;

// View stuff
glm::mat4 projectionMat;

void OnFramebufferResize(GLFWwindow *win, int width, int height) {
  window_w = width;
  window_h = height;
  glViewport(0, 0, window_w, window_h);
  projectionMat =
      glm::ortho(0.0, (double)window_w, (double)window_h, 0.0, -1.0, 1.0);
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
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
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

  glfwSetFramebufferSizeCallback(window, OnFramebufferResize);
  glfwMakeContextCurrent(window);

  gladLoadGL((GLADloadfunc)glfwGetProcAddress);

  /**
   * OPENGL SETUP
   */

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

  projectionMat =
      glm::ortho(0.0, (double)window_w, (double)window_h, 0.0, -1.0, 1.0);

  return true;
}

void BeginDrawing() {
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void EndDrawing() {
  glfwSwapBuffers(window);
  glfwPollEvents();

  glUseProgram(0);
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

void FillRect(int x, int y, int w, int h, glm::vec4 color) {
  glm::mat4 modelMat = glm::mat4(1.0f);
  modelMat = glm::translate(modelMat, {x, y, 0});
  modelMat = glm::scale(modelMat, {w, h, 1});

  // TODO: Move this to a one-time lookup
  GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMat[0][0]);
  GLint projLoc = glGetUniformLocation(shaderProgram, "proj");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projectionMat[0][0]);

  GLint resLoc = glGetUniformLocation(shaderProgram, "resolution");
  glUniform2f(resLoc, (float)window_w, (float)window_h);

  GLint tintLoc = glGetUniformLocation(shaderProgram, "tint");
  glUniform4fv(tintLoc, 1, &color[0]);

  GLint sizeLoc = glGetUniformLocation(shaderProgram, "size");
  glUniform2f(sizeLoc, (float)w, (float)h);

  GLint radiusLoc = glGetUniformLocation(shaderProgram, "radius");
  glUniform1f(radiusLoc, 20.0f);

  GLint originLoc = glGetUniformLocation(shaderProgram, "origin");
  glUniform2f(originLoc, x, window_h - y);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

bool WindowCloseRequested() { return glfwWindowShouldClose(window); }

} // namespace Renderer
