#ifndef __ORIGIN_COMPONENT_H_
#define __ORIGIN_COMPONENT_H_

#include "cocos2d.h"
#include "OriginMacros.h"

NS_O_BEGIN

/*************
*组件代表功能的最小单元,组件可以有一个Type类型来标记唯一性
**************/
class Component : public cocos2d::Ref
{
public:
	static const std::string DEFAULT_COMPONENT_TYPE;

	Component(const std::string& type = DEFAULT_COMPONENT_TYPE);
	virtual ~Component();

	const std::string& getType() const;
protected:
	std::string _type;
};

class ComponentContainerProtocol
{
public:
	virtual ~ComponentContainerProtocol(){};

	virtual const cocos2d::Map<std::string, Component *>& getComponents() const = 0;
	virtual cocos2d::Map<std::string, Component*>& getComponents() = 0;
};

/*****
组合多个容器的组件容器,本身也可以用Type类型标记唯一性
****/
class ComponentContainer : public Component, ComponentContainerProtocol
{
public:
	ComponentContainer(const std::string&type = Component::DEFAULT_COMPONENT_TYPE);
	virtual ~ComponentContainer();

	const cocos2d::Map<std::string, Component*>& getComponents() const override;
	cocos2d::Map<std::string, Component *>& getComponents() override;

protected:
	cocos2d::Map<std::string, Component*> _components;
};

NS_O_END;

#endif // !__ORIGIN_COMPONENT_H_
