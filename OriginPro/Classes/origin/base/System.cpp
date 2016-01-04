#include "System.h"

NS_O_BEGIN

/********System**********/
System::System(Component * component)
{
	_component = component;
}

System::~System()
{
	_component = nullptr;
}

/************EntitySystem*************/
EntitySystem::EntitySystem(Component * component, Entity * entity) :System(component), _entity(entity)
{

}

EntitySystem::~EntitySystem()
{
	_entity = nullptr;
}

/******************ComponentContainerSystem********************/
ComponentContainerSystem::ComponentContainerSystem(ComponentContainer * component) :System(component)
{
}

ComponentContainerSystem::~ComponentContainerSystem()
{
}

bool ComponentContainerSystem::addComponent(Component * component)
{
	if (getComponent(component->getType())) return false;
	ComponentContainer * componentContainer = dynamic_cast<ComponentContainer *>(_component);
	if (componentContainer != nullptr)
	{
		componentContainer->getComponents().insert(component->getType(), component);
		return true;
	}
	return false;
}

void ComponentContainerSystem::removeComponent(const std::string&type)
{
	ComponentContainer * componentContainer = dynamic_cast<ComponentContainer *>(_component);
	if (componentContainer != nullptr)
	{
		componentContainer->getComponents().erase(type);
	}
}

Component * ComponentContainerSystem::getComponent(const std::string& type) const
{
	ComponentContainer * componentContainer = dynamic_cast<ComponentContainer *>(_component);
	if (componentContainer != nullptr)
	{
		return componentContainer->getComponents().at(type);
	}
	return nullptr;
}

NS_O_END;