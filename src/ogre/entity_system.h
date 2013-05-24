#pragma once

#include "engine/component.h"
#include "engine/shared_data.h"
#include "engine/system.h"

#include <memory>
#include <OgreSceneManager.h>
#include <OgreString.h>


namespace thrive {

/**
* @brief Component for an entity that has a 3D mesh
*/
class OgreEntityComponent : public Component {
    COMPONENT(Mesh)

public:

    /**
    * @brief Constructor
    *
    * @param meshName
    *   The name of the mesh the entity is to be based on
    */
    OgreEntityComponent(
        std::string meshName
    );

    /**
    * @brief Constructor
    *
    * @param prefabType
    *   The prefab model to use (\c PT_PLANE, \c PT_CUBE or \c PT_SPHERE)
    */
    OgreEntityComponent(
        Ogre::SceneManager::PrefabType prefabType
    );

    /**
    * @brief Lua bindings
    *
    * This component exposes the following \ref shared_data_lua "shared properties":
    * - Properties::meshName
    *
    * @return 
    */
    static luabind::scope
    luaBindings();

    /**
    * @brief The name of the entity's mesh
    *
    * If the entity was not constructed with a named mesh, this string will
    * be empty.
    */
    const std::string m_meshName;

    /**
    * @brief The prefab mesh this entity uses, if any
    *
    * Defaults to Ogre::Entity::PT_SPHERE.
    */
    const Ogre::SceneManager::PrefabType m_prefabType;

};


/**
* @brief Updates meshes of OgreEntityComponents
*/
class OgreEntitySystem : public System {

public:

    /**
    * @brief Constructor
    */
    OgreEntitySystem();

    /**
    * @brief Destructor
    */
    ~OgreEntitySystem();

    /**
    * @brief Initializes the system
    *
    * @param engine
    *   Must be an OgreEngine
    */
    void init(Engine* engine) override;

    /**
    * @brief Shuts the system down
    */
    void shutdown() override;

    /**
    * @brief Updates the graphics engine's data
    *
    * All OgreEntityComponents whose OgreEntityComponent::Properties::meshName has changed
    * will be updated.
    *
    */
    void update(int) override;

private:

    struct Implementation;
    std::unique_ptr<Implementation> m_impl;
};

}


