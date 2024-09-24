#pragma once
#include "Core/Base.h"
#include "Core/Components.h"

#include <assert.h>
#include <string>
#include <tuple>
#include <utility>

typedef std::tuple<TransformComponent, ModelComponent> ComponentTuple;

class Entity
{
public:
    Entity() = default;
    Entity(u64 id, const char* tag);

    inline u64 GetID() const { return m_id; }
    inline b8 IsActive() const { return m_isActive; }
    inline b8 IsAlive() const { return m_isAlive; }
    inline const char* GetTag() { return m_tag.c_str(); }

    inline void SetActive(b8 active) { m_isActive = active; }
    inline void Destroy() { m_isAlive = false; }

    template <typename T> T& GetComponent() { return std::get<T>(m_components); }
    template <typename T> const T& GetComponent() const { return std::get<T>(m_components); }
    template <typename T> b8 HasComponent() const { return GetComponent<T>().enabled; }
    template <typename T, typename... TArgs> T& AddComponent(TArgs&&... args)
    {
        T& component = GetComponent<T>();
        component = T(std::forward<TArgs>(args)...);
        component.enabled = true;
        return component;
    }
    template <typename T> void RemoveComponent() { GetComponent<T>() = T(); }

    bool operator==(const Entity& other) const { return m_id == other.m_id; }
    bool operator!=(const Entity& other) const { return !(operator==(other)); }

private:
    friend class EntityManager;

    u64 m_id = 0;
    b8 m_isActive = false;
    b8 m_isAlive = true;
    std::string m_tag;
    ComponentTuple m_components;
};
