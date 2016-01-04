#ifndef __ORIGIN_EXCLUSION_H_
#define __ORIGIN_EXCLUSION_H_

#include "cocos2d.h"
#include "OriginMacros.h"
#include "System.h"

NS_O_BEGIN

class ExclusionDefiniation : public cocos2d::Ref
{
public:
	static const unsigned int DEFAULT_EXCLUSION;
	enum class ExclusionType
	{
		PAUSE,
		RESUME,
	};

	ExclusionDefiniation(ExclusionType type);
	virtual ~ExclusionDefiniation();

	const ExclusionType& getType() const;
protected:
	ExclusionType _type;
};

class ExclusionProtocol
{
public:
	virtual ~ExclusionProtocol();

	virtual unsigned int getExclusionCount() const = 0;
	virtual void setExclusionCount(unsigned int exclusionCount) = 0;
};

class ExclusionComponent : public Component, ExclusionProtocol
{
public:
	ExclusionComponent(const ExclusionDefiniation * exclusionDefiniation);
	~ExclusionComponent();

	unsigned int getExclusionCount() const override;

	const ExclusionDefiniation * getExclusionDefiniation() const;
	void ExclusionComponent::setExclusionCount(unsigned int exclusionCount);
protected:
	unsigned int _exclusionCount;

	const ExclusionDefiniation * _exclusionDefiniation;
};

class ExclusionSystemProtocol
{
public:
	virtual ~ExclusionSystemProtocol();

	virtual unsigned int exclusion() = 0;
	virtual unsigned int unexclusion() = 0;
	virtual void resetExclusion() = 0;

	virtual ExclusionComponent * getExclusionComponent() = 0;
};

class ExclusionSystem : public System, ExclusionSystemProtocol
{
public:
	ExclusionSystem(ExclusionComponent * exclusionComponent);
	~ExclusionSystem();

	unsigned int exclusion() override;
	unsigned int unexclusion() override;
	void resetExclusion() override;

	ExclusionComponent * getExclusionComponent() override;
};

NS_O_END;

#endif // !__ORIGIN_EXCLUSION_H_
