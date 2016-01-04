#ifndef __ORIGIN_STATE_H_
#define __ORIGIN_STATE_H_

#include "cocos2d.h"
#include "Exclusion.h"

NS_O_BEGIN

class StateDefinitaion : public cocos2d::Ref
{
public:
	StateDefinitaion(const std::string& stateType);
	virtual ~StateDefinitaion();

	void setStateType(const std::string& stateType);

	const std::string& getStateType() const;

protected:
	std::string _stateType;
};

class State : public cocos2d::Ref, ExclusionSystemProtocol
{
public:
	State(const StateDefinitaion * stateDefiniation, ExclusionComponent * exclusionComponent);
	virtual ~State();

	virtual bool init();

	void start(unsigned int defaultExclusionCount = ExclusionDefiniation::DEFAULT_EXCLUSION);
	void stop();

	void pause();
	void resume();

	/*****检测当前排斥*****/
	void refresh();

	bool isStart() const;
	bool isRunning() const;

	const StateDefinitaion * getStateDefiniation() const;

	cocos2d::EventDispatcher * getEventDispatcher() const;
	cocos2d::Scheduler * getScheduler() const;

	void setExclusionComponent(ExclusionComponent * exclusionComponent);

	unsigned int exclusion() override;
	unsigned int unexclusion() override;
	void resetExclusion() override;
	ExclusionComponent * getExclusionComponent() override;
protected:
	virtual void startExecute();
	virtual void stopExecute();

	virtual void pauseExecute();
	virtual void resumeExecute();

	const StateDefinitaion * _stateDefiniation;
	ExclusionComponent * _exclusionComponent;

	/****标记状态是否已经开始****/
	bool _start;
	/****标记状态是否在运行***/
	bool _running;

	cocos2d::EventDispatcher * _eventDispatcher;
	cocos2d::Scheduler * _scheduler;
};

class StateReferenceComponent : public Component
{
public:
	StateReferenceComponent();
	virtual ~StateReferenceComponent();

	void setStateData(State * data);
	State * getStateData() const;

	void setExclusionCount(unsigned int exclusionCount);
	unsigned int getExclusionCount() const;
protected:
	State * _state;
	unsigned int _exclusionCount;
};

template <class T>
class StateContainer : public State
{
public:
	StateContainer<T>(const StateDefinitaion * stateDefiniation);
	virtual ~StateContainer<T>();
protected:
	
	T _container;
};

NS_O_END

#endif