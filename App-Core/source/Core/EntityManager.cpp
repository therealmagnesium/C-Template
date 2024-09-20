#include "Core/EntityManager.h"
#include "Core/Components.h"
#include "Core/Log.h"
#include "Graphics/Renderer.h"
#include <algorithm>
#include <memory>
#include <string>

std::shared_ptr<Entity> EntityManager::AddEntity(const char* tag)
{
    std::shared_ptr<Entity> entity = std::make_shared<Entity>(m_totalEntities++, tag);
    entity->SetActive(true);
    m_toAdd.push_back(entity);
    return entity;
}

void EntityManager::Update()
{
    for (auto& entity : m_toAdd)
    {
        const char* entityTag = entity->GetTag();
        m_entities.push_back(entity);
        m_entityMap[entityTag].push_back(entity);
    }

    for (u64 i = 0; i < m_entities.size(); i++)
    {
        auto& entity = m_entities[i];
        const char* entityTag = entity->GetTag();
        if (!entity->IsActive())
        {
            m_entities.erase(m_entities.begin() + i);
            m_entityMap[entityTag].erase(m_entities.begin() + i);
        }
    }

    m_toAdd.clear();
}

void EntityManager::DrawEntities()
{
    for (u64 i = 0; i < m_entities.size(); i++)
    {
        auto& entity = m_entities[i];
        if (entity->HasComponent<TransformComponent>() && entity->HasComponent<ModelComponent>())
        {
            TransformComponent& tc = entity->GetComponent<TransformComponent>();
            ModelComponent& mc = entity->GetComponent<ModelComponent>();

            Renderer.DrawModel(mc.model, tc.position, tc.rotation, tc.scale);
        }
    }
}

EntityVec& EntityManager::GetEntities() { return m_entities; }
EntityVec& EntityManager::GetEntities(const char* tag) { return m_entityMap[tag]; }
