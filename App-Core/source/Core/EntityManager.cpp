#include "Core/EntityManager.h"
#include <algorithm>
#include <string>

void EntityManager::Update()
{
    for (Entity& entity : m_toAdd)
    {
        std::string& entityTag = entity.GetTag();
        m_entities.push_back(entity);
        m_entityMap[entityTag].push_back(entity);
    }

    for (u64 i = 0; i < m_entities.size(); i++)
    {
        Entity& entity = m_entities[i];
        std::string& entityTag = entity.GetTag();
        if (!entity.IsActive())
        {
            m_entities.erase(m_entities.begin() + i);
            m_entityMap[entityTag].erase(m_entities.begin() + i);
        }
    }

    m_toAdd.clear();
}

Entity EntityManager::AddEntity(const char* tag)
{
    Entity entity = Entity(m_totalEntities++, tag);
    entity.SetActive(true);
    m_toAdd.push_back(entity);
    return entity;
}

std::vector<Entity>& EntityManager::GetEntities() { return m_entities; }
std::vector<Entity>& EntityManager::GetEntities(const char* tag) { return m_entityMap[tag]; }
