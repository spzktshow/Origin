#include "Component.h"

NS_O_BEGIN

/*******Component********/
/********如果Entity或Component在编译器就能决定依赖某个具体类型的Component就能省略Component的Type类型
*在这样的情况下可以直接使用默认的noTypeComponent类型
********/
const std::string Component::DEFAULT_COMPONENT_TYPE = "noTypeComponent";

Component::Component(const std::string& type /* = DEFAULT_COMPONENT_TYPE */) :_type(type)
{

}

Component::~Component()
{

}

const std::string& Component::getType() const
{
	return _type;
}

/****************ComponentContainer***************/
const cocos2d::Map<std::string, Component*>& ComponentContainer::getComponents() const
{
	return _components;
}

cocos2d::Map<std::string, Component*>& ComponentContainer::getComponents()
{
	return _components;
}

NS_O_END;