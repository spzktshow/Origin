#ifndef __ORIGIN_ENTITY_H_
#define __ORIGIN_ENTITY_H_

#include "cocos2d.h"
#include "OriginMacros.h"
#include "Component.h"

NS_O_BEGIN

class Entity : public cocos2d::Ref, public ComponentContainerProtocol
{
public:
	Entity();
	virtual ~Entity();

	const cocos2d::Map<std::string, Component *>& getComponents() const override;
	cocos2d::Map<std::string, Component *>& getComponents() override;
protected:
	cocos2d::Map<std::string, Component *> _components;
};

NS_O_END;

#endif // !__ORIGIN_ENTITY_H_
