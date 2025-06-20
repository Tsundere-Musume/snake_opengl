#include "./shader.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

ShaderProgram sp_new(const char *vertex_src_path,
                           const char *fragment_src_path) {
  char *vertex_src = read_shader_file(vertex_src_path);
  char *fragment_src = read_shader_file(fragment_src_path);

  unsigned int vertex, fragment;
  int success;
  char info_log[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, (const char **)&vertex_src, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, info_log);
    fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n",
            info_log);
  }
  free(vertex_src);

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, (const char **)&fragment_src, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, info_log);
    fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n",
            info_log);
  }
  free(fragment_src);

  ShaderProgram shader = {0};
  shader.ID = glCreateProgram();
  glAttachShader(shader.ID, vertex);
  glAttachShader(shader.ID, fragment);
  glLinkProgram(shader.ID);
  glGetShaderiv(fragment, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader.ID, 512, NULL, info_log);
    fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  return shader;
}

void sp_use(ShaderProgram *program) { glUseProgram(program->ID); }
// https://craftinginterpreters.com/scanning-on-demand.html
static char *read_shader_file(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "ERROR::SHADER::FILE: couldn't open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t file_size = ftell(file);
  rewind(file);

  char *buffer = (char *)malloc(file_size + 1);
  if (buffer == NULL) {
    fprintf(stderr, "ERROR::SHADER::FILE: not enough memory to read \"%s\".\n",
            path);
    exit(74);
  }
  size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
  if (bytes_read < file_size) {
    fprintf(stderr, "ERROR::SHADER::FILE: could not read file \"%s\".\n", path);
    exit(74);
  }
  buffer[bytes_read] = '\0';

  fclose(file);
  return buffer;
}
