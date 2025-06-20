#ifndef SNAKE_SHADER_H
#define SNAKE_SHADER_H

#include <glad/glad.h>

typedef struct {
  unsigned int ID;
} ShaderProgram;

ShaderProgram sp_new(const char *vertex_src_path,
                     const char *fragment_src_path);
void sp_use(ShaderProgram *program);
static char *read_shader_file(const char *path);
#endif
