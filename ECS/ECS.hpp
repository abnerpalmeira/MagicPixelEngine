//
//  ECS.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 08/06/22.
//

#pragma once
#ifndef ECS_hpp
#define ECS_hpp

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID(){
    static ComponentID last_id = 0;
    return last_id;
}

template <typename t> inline ComponentID GetComponentTypeID() noexcept{
    static ComponentID type_id = GetComponentTypeID();
    return type_id;
}

constexpr std::size_t kMax_components = 32;

using ComponentBitSet = std::bitset<kMax_components>;
using ComponentArray = std::array<Component*,kMax_components>;

class Component{
public:
    Entity* entity_;
    virtual void Init(){}
    virtual void Update(){}
    virtual void Draw(){}
    virtual ~Component(){}
};

class Entity{
private:
    bool active_ = true;
    std::vector<std::unique_ptr<Component> > components_;
    ComponentBitSet component_bitset_;
    ComponentArray component_array_;
public:
    void Update(){
        for(auto& c: components_) c->Update();
    }
    void Draw(){
        for(auto& c: components_) c->Draw();
    }
    bool IsActive() const{
        return active_;
    }
    void Destroy(){
        active_ = false;
    }
    
    template <typename T> bool HasComponent() const{
        return component_bitset_[GetComponentTypeID<T>];
    }
    
    template <typename T, typename ...TArgs> T& AddComponent(TArgs&&... mArgs){
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> u_ptr{c};
        components_.emplace_back(std::move(u_ptr));
        component_array_[GetComponentTypeID<T>()] = c;
        component_bitset_[GetComponentTypeID<T>()] = true;
        
        c->Init();
        return *c;
    }
    template <typename T, typename ...TArgs> T& GetComponent() const{
        auto ptr(component_array_[GetComponentTypeID<T>()]);
        return *staic_cast<T*>(ptr);
    }
};

class Manager{
private:
    std::vector<std::unique_ptr<Entity> > entities_;
public:
    void Update(){
        for(auto& e: entities_) e->Update();
    }
    void Draw(){
        for(auto& e: entities_) e->Draw();
    }
    void Refresh(){
        entities_.erase(std::remove_if(std::begin(entities_), std::end(entities_), [](const std::unique_ptr<Entity> &m_entity){
            return m_entity->IsActive();
        }),std::end(entities_));
    }
    
    Entity& AddEntity(){
        Entity* e = new Entity();
        std::unique_ptr<Entity> u_ptr{e};
        entities_.emplace_back(std::move(u_ptr));
        return *e;
    }
};

#endif /* ECS_hpp */
