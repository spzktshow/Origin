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

/***************state****************/
State::State(const StateDefinitaion * stateDefiniation)
	:_start(false)
	, _running(false)
	, _eventDispatcher(nullptr)
	, _scheduler(nullptr)
	, _stateDefiniation(stateDefiniation)
{
	CCASSERT(stateDefiniation != nullptr, "stateDefiniation must != nullptr");
}

State::~State()
{
	_stateDefiniation = nullptr;
}

bool State::init()
{
	return true;
}

void State::start()
{
	if (!_start)
	{
		_start = true;
		startExecute();
	}

	resume();
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

/*****************DynamicState****************/
DynamicState::DynamicState(const StateDefinitaion * stateDefiniation, const ExclusionDefiniation * exclusionDefiniation) :State(stateDefiniation), _exclucsion(nullptr)
{
	_exclucsion = new Exclusion(exclusionDefiniation);
}

DynamicState::~DynamicState()
{
	CC_SAFE_DELETE(_exclucsion);
}

unsigned int DynamicState::exclusion()
{
	return _exclucsion->exclusion();
}

unsigned int DynamicState::unexclusion()
{
	return _exclucsion->unexclusion();
}

void DynamicState::resetExclusion()
{
	_exclucsion->resetExclusion();
}

void DynamicState::start(unsigned int exclusionCount)
{
	if (!_start)
	{
		_start = true;
		startExecute();
	}

	refresh();
}

void DynamicState::startDefault()
{

}

void DynamicState::refresh()
{

}

NS_O_END