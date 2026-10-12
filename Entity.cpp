#include "Entity.h"

Entity::Entity(int id) : id(id) {}
Entity::~Entity() {}

int Entity::getId() const { return id; }
void Entity::setId(int newId) { id = newId; }
