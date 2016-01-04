#include "State.h"

NS_O_BEGIN
/**********StateDefiniation**********/
StateDefinitaion::StateDefinitaion(const std::string& stateType)
{
	setStateType(stateType);
}

StateDefinitaion::~StateDefinitaion()
{
}

void StateDefinitaion::setStateType(const std::string& stateType)
{
	if (_stateType == stateType) return;
	_stateType = stateType;
}

const std::string& StateDefinitaion::getStateType() const
{
	return _stateType;
}

/******state******/
State::State(const StateDefinitaion * stateDefiniation, ExclusionComponent * exclusionComponent)
	:_start(false)
	, _running(false)
	, _eventDispatcher(nullptr)
	, _scheduler(nullptr)
	, _stateDefiniation(stateDefiniation)
	, _exclusionComponent(nullptr)
{
	setExclusionComponent(exclusionComponent);
}

State::~State()
{
	CC_SAFE_RELEASE_NULL(_exclusionComponent);
	_stateDefiniation = nullptr;
}

bool State::init()
{
	return true;
}

void State::start(unsigned int defaultExclusionCount)
{
	if (!_start)
	{
		_start = true;
		startExecute();
	}

	_exclusionComponent->setExclusionCount(defaultExclusionCount);
	refresh();
}

void State::stop()
{
	pause();

	if (_start)
	{
		_start = false;
		stopExecute();
	}
}

void State::pause()
{
	if (_start && _running)
	{
		_running = false;
		pauseExecute();
	}
}

void State::resume()
{
	if (_start && !_running)
	{
		_running = true;
		resumeExecute();
	}
}

void State::refresh()
{
	if (getExclusionComponent()->getExclusionCount() == ExclusionDefiniation::DEFAULT_EXCLUSION)
	{
		if (getExclusionComponent()->getExclusionDefiniation()->getType() == ExclusionDefiniation::ExclusionType::PAUSE)
		{
			pause();
		}
		else if (getExclusionComponent()->getExclusionDefiniation()->getType() == ExclusionDefiniation::ExclusionType::RESUME)
		{
			resume();
		}
		else
		{
			CCASSERT(false, "unknow exclusionType");
		}
	}
	else
	{
		if (getExclusionComponent()->getExclusionDefiniation()->getType() == ExclusionDefiniation::ExclusionType::PAUSE)
		{
			resume();
		}
		else if (getExclusionComponent()->getExclusionDefiniation()->getType() == ExclusionDefiniation::ExclusionType::RESUME)
		{
			pause();
		}
		else
		{
			CCASSERT(false, "unknow exclusionType");
		}
	}
}

bool State::isStart() const
{
	return _start;
}

bool State::isRunning() const
{
	return _running;
}

const StateDefinitaion * State::getStateDefiniation() const
{
	return _stateDefiniation;
}

cocos2d::EventDispatcher * State::getEventDispatcher() const
{
	return _eventDispatcher;
}

cocos2d::Scheduler * State::getScheduler() const
{
	return _scheduler;
}

void State::setExclusionComponent(ExclusionComponent * exclusionComponent)
{
	CC_ASSERT(exclusionComponent != nullptr, "State ExclusionComponent must construct!");
	if (_exclusionComponent) _exclusionComponent->release();
	_exclusionComponent = exclusionComponent;
	if (_exclusionComponent) _exclusionComponent->retain();
}

unsigned int State::exclusion()
{
	unsigned int value;
	ExclusionSystem exclusionSystem(getExclusionComponent());
	value = exclusionSystem.exclusion();

	if (value > 0) refresh();
	return value;
}

unsigned int State::unexclusion()
{
	unsigned int value;
	ExclusionSystem exclusionSystem(getExclusionComponent());
	value = exclusionSystem.unexclusion();

	if (value > 0) refresh();
	return value;
}

void State::resetExclusion()
{
	ExclusionSystem exclusionSystem(getExclusionComponent());
	exclusionSystem.resetExclusion();

	refresh();
}

ExclusionComponent * State::getExclusionComponent()
{
	return _exclusionComponent;
}

void State::startExecute()
{

}

void State::stopExecute()
{

}

void State::pauseExecute()
{

}

void State::resumeExecute()
{

}


/*****StateReferenceComponent******/
StateReferenceComponent::StateReferenceComponent() :_state(nullptr), _exclusionCount(0)
{

}

StateReferenceComponent::~StateReferenceComponent()
{

}

void StateReferenceComponent::setStateData(State * state)
{
	_state = state;
}

State * StateReferenceComponent::getStateData() const
{
	return _state;
}

void StateReferenceComponent::setExclusionCount(unsigned int exclusionCount)
{
	_exclusionCount = exclusionCount;
}

unsigned int StateReferenceComponent::getExclusionCount() const
{
	return _exclusionCount;
}

NS_O_END