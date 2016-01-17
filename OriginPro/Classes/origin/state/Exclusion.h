#ifndef __ORIGIN_EXCLUSION_H_
#define __ORIGIN_EXCLUSION_H_

#include "OriginMacros.h"

NS_O_BEGIN

class ExclusionDefiniation
{
public:
	static const unsigned int DEFAULT_EXCLUSION;
	enum class ExclusionType
	{
		PAUSE = 0,
		RESUME,
	};

	ExclusionDefiniation(ExclusionType type);
	virtual ~ExclusionDefiniation();

	const ExclusionType& getType() const;

	unsigned int getDefaultExculsion() const;
protected:
	ExclusionType _type;

	unsigned int _defaultExclusion;
};

class ExclusionProtocol
{
public:
	virtual ~ExclusionProtocol();

	virtual unsigned int exclusion() = 0;
	virtual unsigned int unexclusion() = 0;
	virtual void resetExclusion() = 0;
};

class Exclusion : public ExclusionProtocol
{
public:
	Exclusion(const ExclusionDefiniation * exclusionDefiniation);
	virtual ~Exclusion();

	unsigned int exclusion() override;
	unsigned int unexclusion() override;
	void resetExclusion() override;

	const ExclusionDefiniation::ExclusionType& checkType() const;
protected:
	const ExclusionDefiniation * _exclusionDefiniation;

	int _exclusionCount;
};

NS_O_END;

#endif // !__ORIGIN_EXCLUSION_H_
