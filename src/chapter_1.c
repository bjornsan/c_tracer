#include "tuple.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
  point3d position;
  vector3d velocity;

}projectile_t;

typedef struct
{
  vector3d gravity;
  vector3d wind;

}environment_t;

void tick(environment_t* env, projectile_t* proj)
{
  // Add position to velocity vector
  add_tuple(&proj->position, &proj->velocity);
  
  // add gravity and wind vector to velocity
  add_tuple(&proj->velocity, &env->gravity);
  add_tuple(&proj->velocity, &env->wind);
}

int main() 
{
  projectile_t* p = (projectile_t*)calloc(1, sizeof(projectile_t));
  environment_t* env = (environment_t*)calloc(1, sizeof(environment_t));
  
  if (!p || !env) {
    fprintf(stderr, "Memory allocation failed\n");
  }

  p->position = *point(0.0, 1.0, 0.0);

  vector3d* vel = vector(1.0, 1.0, 0.0);
  normal(vel);
  p->velocity = *vel;


  env->gravity = *vector(0.0, -0.1, 0.0);
  env->wind = *vector(-0.01, 0.0, 0.0);

  while(p->position.y > 0)
  {
    printf("y: %f\n", p->position.y);
    tick(env, p);
  }

  free(env);
  free(p);
  return 0;

  // investigate perf linux tool
}