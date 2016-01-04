#include "Entity.h"

NS_O_BEGIN
/*****************Entity****************/
Entity::Entity()
{

}

Entity::~Entity()
{

}

const cocos2d::Map<std::string, Component *>& Entity::getComponents() const
{
	return _components;
}

cocos2d::Map<std::string, Component *>& Entity::getComponents()
{
	return _components;
}

NS_O_END;