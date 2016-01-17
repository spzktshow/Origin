#include "Exclusion.h"
#include "cocos2d.h"
NS_O_BEGIN
/***************ExclusionDefiniation****************/
const unsigned int ExclusionDefiniation::DEFAULT_EXCLUSION = 0;

ExclusionDefiniation::ExclusionDefiniation(ExclusionType type) :_defaultExclusion(ExclusionDefiniation::DEFAULT_EXCLUSION), _type(type){}

ExclusionDefiniation::~ExclusionDefiniation(){}

const ExclusionDefiniation::ExclusionType& ExclusionDefiniation::getType() const
{
	return _type;
}

unsigned int ExclusionDefiniation::getDefaultExculsion() const
{
	return _defaultExclusion;
}

/**************ExclusionProtocol*****************/
ExclusionProtocol::~ExclusionProtocol()
{

}

/********Exclusion*********/
Exclusion::Exclusion(const ExclusionDefiniation * exclusionDefiniation) :_exclusionDefiniation(exclusionDefiniation)
{
	CCASSERT(_exclusionDefiniation != nullptr, "exclusionDefiniation must !=nullptr");
}

Exclusion::~Exclusion()
{
	_exclusionDefiniation = nullptr;
}

unsigned int Exclusion::exclusion()
{
	CCASSERT(_exclusionCount > 0, "exclusion count should be greater than 0");
	++_exclusionCount;
	return _exclusionCount;
}

unsigned int Exclusion::unexclusion()
{
	CCASSERT(_exclusionCount > 0, "exclusion count should be greater than 0");
	--_exclusionCount;
	return _exclusionCount;
}

void Exclusion::resetExclusion()
{
	CCASSERT(_exclusionCount > 0, "exclusion count should be greater than 0");
	_exclusionCount = _exclusionDefiniation->getDefaultExculsion();
}

const ExclusionDefiniation::ExclusionType& Exclusion::checkType() const
{
	if (_exclusionDefiniation->getType() == ExclusionDefiniation::ExclusionType::PAUSE)
	{
		if (_exclusionCount == ExclusionDefiniation::DEFAULT_EXCLUSION)
		{
			return ExclusionDefiniation::ExclusionType::PAUSE;
		}
		else
		{
			return ExclusionDefiniation::ExclusionType::RESUME;
		}
	}
	else //_exclusionDefiniation->getType() == ExclusionDefiniation::ExclusionType::RESUME
	{
		if (_exclusionCount == ExclusionDefiniation::DEFAULT_EXCLUSION)
		{
			return ExclusionDefiniation::ExclusionType::RESUME;
		}
		else
		{
			return ExclusionDefiniation::ExclusionType::PAUSE;
		}
	}
}

NS_O_END;