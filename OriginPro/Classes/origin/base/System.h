#ifndef __ORIGIN_SYSTEM_H_
#define __ORIGIN_SYSTEM_H_

#include "cocos2d.h"
#include "OriginMacros.h"
#include "Entity.h"

NS_O_BEGIN

class System
{
public:
	System(Component * component);
	virtual ~System();

protected:
	Component * _component;
};

class EntitySystem : public System
{
public:
	EntitySystem(Component * component, Entity * entity);
	virtual ~EntitySystem();

protected:
	Entity * _entity;
};

class ComponentContainerSystem : public System
{
public:
	ComponentContainerSystem(ComponentContainer * component);
	virtual ~ComponentContainerSystem();

	virtual bool addComponent(Component * component);
	virtual void removeComponent(const std::string&type);

	Component * getComponent(const std::string& type) const;
};

NS_O_END;

#endif // !__ORIGIN_SYSTEM_H_
