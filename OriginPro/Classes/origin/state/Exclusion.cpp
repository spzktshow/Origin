#include "Exclusion.h"

NS_O_BEGIN
/***************ExclusionDefiniation****************/
const unsigned int ExclusionDefiniation::DEFAULT_EXCLUSION = 0;

ExclusionDefiniation::ExclusionDefiniation(ExclusionType type){}

ExclusionDefiniation::~ExclusionDefiniation(){}

const ExclusionDefiniation::ExclusionType& ExclusionDefiniation::getType() const
{
	return _type;
}

/**************ExclusionProtocol*****************/
ExclusionProtocol::~ExclusionProtocol()
{

}

/********ExclusionComponent*********/
ExclusionComponent::ExclusionComponent(const ExclusionDefiniation * exclusionDefiniation) 
	:_exclusionDefiniation(exclusionDefiniation)
{
	_exclusionCount = ExclusionDefiniation::DEFAULT_EXCLUSION;
}

ExclusionComponent::~ExclusionComponent()
{

}

void ExclusionComponent::setExclusionCount(unsigned int exclusionCount)
{
	_exclusionCount = exclusionCount;
}

unsigned int ExclusionComponent::getExclusionCount() const
{
	return _exclusionCount;
}

const ExclusionDefiniation * ExclusionComponent::getExclusionDefiniation() const
{
	return _exclusionDefiniation;
}

/********************ExclusionSystem********************/
unsigned int ExclusionSystem::exclusion()
{
	CCASSERT(getExclusionComponent()->getExclusionCount() > 0, "state exclusion count should be greater than 0");
	const unsigned int value = 1;
	getExclusionComponent()->setExclusionCount(getExclusionComponent()->getExclusionCount() + value);
	return value;
}

unsigned int ExclusionSystem::unexclusion()
{
	CCASSERT(getExclusionComponent()->getExclusionCount() > 0, "state exclusion count should be greater than 0");
	const unsigned int value = 1;
	getExclusionComponent()->setExclusionCount(getExclusionComponent()->getExclusionCount() - value);
	return value;
}

void ExclusionSystem::resetExclusion()
{
	getExclusionComponent()->setExclusionCount(ExclusionDefiniation::DEFAULT_EXCLUSION);
}

ExclusionComponent * ExclusionSystem::getExclusionComponent()
{
	return dynamic_cast<ExclusionComponent *>(_component);
}

NS_O_END;