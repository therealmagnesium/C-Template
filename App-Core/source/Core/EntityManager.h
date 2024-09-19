#pragma once
#include "Core/Base.h"
#include "Core/Components.h"

#include "Core/Entity.h"
#include <string>
#include <unordered_map>
#include <vector>

typedef std::vector<Entity> EntityVec;
typedef std::unordered_map<std::string, std::vector<Entity>> EntityMap;

class EntityManager
{
public:
    EntityManager() = default;
    void Update();
    Entity AddEntity(const char* tag);

    inline u64 GetEntityCount() { return m_totalEntities; }

    std::vector<Entity>& GetEntities();
    std::vector<Entity>& GetEntities(const char* tag);

private:
    u64 m_totalEntities = 0;
    EntityVec m_entities;
    EntityVec m_toAdd;
    EntityMap m_entityMap;
};
