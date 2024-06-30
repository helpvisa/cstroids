#include "../defs.h"
#include "../structs.h"
#include "../wrap_sdl/draw.h"
#include <math.h>

extern float zoom_x;
extern float zoom_y;
extern float ratio;
extern float screen_width;
extern float screen_height;

Particle *create_particle(Vector2 pos, Vector2 velocity, int lifetime, Colour col) {
  Particle *part = malloc(sizeof(Particle));
  part->pos = pos;
  part->velocity = velocity;
  part->lifetime = lifetime;
  part->life = lifetime;
  part->col = col;
  return part;
}

void insert_particle_at_beginning(struct ParticleNode **head, Particle *part) {
  struct ParticleNode *new_node = malloc(sizeof(struct ParticleNode));
  new_node->part = part;
  new_node->next = *head;
  *head = new_node;
}

void insert_particle_at_end(struct ParticleNode **head, Particle *part) {
  struct ParticleNode *new_node = malloc(sizeof(struct ParticleNode));
  new_node->part = part;
  new_node->next= NULL;

  if (*head == NULL) {
    *head = new_node;
    return;
  }

  // iterate toward final node to add to end of list
  struct ParticleNode *current = *head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_node;
}

void update_particle(Particle *part) {
  part->pos.x += part->velocity.x;
  part->pos.y += part->velocity.y;
  part->velocity.x *= 0.9;
  part->velocity.y *= 0.9;
  part->life -= 1;
}

void draw_particle(Particle *part) {
  Vector2 point = {part->pos.x * zoom_x, part->pos.y * zoom_y};
  render_point(point, part->col);
}

void update_particle_list(struct ParticleNode **head) {
  if (*head == NULL || (*head)->part == NULL) {
    return;
  }

  // update head
  update_particle((*head)->part);

  // iterate through all particles in linked list
  struct ParticleNode *current = *head;
  while (current->next != NULL) {
    current = current->next;
    update_particle(current->part);
  }
}

void draw_particle_list(struct ParticleNode **head) {
  if (*head == NULL || (*head)->part == NULL) {
    return;
  }

  draw_particle((*head)->part);

  struct ParticleNode *current = *head;
  while (current->next != NULL) {
    current = current->next;
    draw_particle(current->part);
  }
}
