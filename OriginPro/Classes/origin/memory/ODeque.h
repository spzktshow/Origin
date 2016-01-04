#ifndef __ODEQUE_H__
#define __ODEQUE_H__

#include "base/CCRef.h"
#include "OriginMacros.h"

NS_O_BEGIN

template<class T>
class Deque
{
public:
	typedef typename std::deque<T>::iterator iterator;
	typedef typename std::deque<T>::const_iterator const_iterator;
	typedef typename std::deque<T>::reverse_iterator reverse_iterator;
	typedef typename std::deque<T>::const_reverse_iterator const_reverse_iterator;

	iterator begin() { return _data.begin(); }
	const_iterator begin() const { return _data.begin(); }
	iterator end() { return _data.end(); }
	const_iterator end() { return _data.end(); }
	const_iterator cbegin() const { return _data.cbegin(); }
	const_iterator cend() const { return _data.cend(); }
	reverse_iterator rbegin() { return _data.rbegin(); }
	const_reverse_iterator rbegin() { return _data.rbegin(); }
	reverse_iterator rend() { return _data.rend(); }
	const_reverse_iterator rend() const { return _data.rend(); }
	const_reverse_iterator crbegin() const { return _data.crbegin(); }
	const_reverse_iterator crend() const { return _data.crend(); }

	Deque<T>() : _data()
	{
		static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for origin::Deque<T>!");
	}

	explicit Deque<T>(ssize_t capacity) : _data()
	{
		static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for origin::Deque<T>!");
		CCLOGINFO("In the default constructor with capacity of Deque.");
		reserve(capacity);
	}

	~Deque<T>()
	{
		CCLOGINFO("In the destructor of Deque.");
		clear();
	}

	Deque<T>(const Deque<T>& other)
	{
		static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for origin::Deque<T>!");
		CCLOGINFO("In the copy constructor!");
		_data = other._data;
		addRefForAllObjects();
	}

	Deque<T>(Deque<T>&& other)
	{
		static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for origin::Deque<T>!");
		CCLOGINFO("In the move constructor of Deque!");
		_data = std::move(other._data);
	}

	Deque<T>& operator=(const Deque<T>&other)
	{
		if (this != &other)
		{
			CCLOGINFO("In the copy assignment operator!");
			clear();
			_data = other._data;
			addRefForAllObjects();
		}
		return *this;
	}

	Deque<T>& operator=(Deque<T>&& other)
	{
		if (this != &other)
		{
			CCLOGINFO("In the move assignment operator!");
			clear();
			_data = std::move(other._data);
		}
		return *this;
	}

	void reserve(ssize_t n)
	{
		_data.reserve(n);
	}

	ssize_t capacity() const
	{
		return _data.capacity();
	}

	ssize_t size() const
	{
		return _data.size();
	}

	bool empty() const
	{
		return _data.empty();
	}

	ssize_t max_size() const
	{
		return _data.max_size();
	}

	ssize_t getIndex(T object) const
	{
		auto iter = std::find(_data.begin(), _data.end(), object);
		if (iter != _data.end())
		{
			return iter - _data.begin();
		}
		return -1;
	}

	const_iterator find(T object) const
	{
		return std::find(_data.begin(), _data.end(), object);
	}

	iterator find(T object)
	{
		return std::find(_data.begin(), _data.end(), object);
	}

	T at(ssize_t index) const
	{
		CCASSERT(index >= 0 && index < size(), "index out of range in getObjectAtIndex()");
		return _data[index];
	}

	T front() const
	{
		return _data.front();
	}

	T back() const
	{
		return _data.back();
	}

	T getRandomObject() const
	{
		if (!_data.empty())
		{
			ssize_t randIdx = rand() % _data.size();
			return *(_data.begin() + randIdx);
		}
		return nullptr;
	}

	bool contains(T object) const
	{
		return (std::find(_data.begin(), _data.end(), object) != _data.end());
	}

	bool equals(const Deque<T>&other)
	{
		ssize_t s = size();
		if (s != other.size())
			return false;

		for (ssize_t i = 0; i < s; i ++)
		{
			if (at(i) != other.at(i))
			{
				return false;
			}
		}
		return true;
	}

	void pushBack(T object)
	{
		CCASSERT(object != nullptr, "The object should not be nullptr");
		_data.push_back(object);
		object->retain();
	}

	void pushBack(const Deque<T>&other)
	{
		for (const auto&obj : other)
		{
			_data.push_back(obj);
			obj->retain();
		}
	}

	void insert(ssize_t index, T object)
	{
		CCASSERT(index >= 0 && index <= size(), "Invalid index!");
		CCASSERT(object != nullptr, "The object should not be nullptr");
		_data.insert((std::begin(_data) + index), object);
	}

	void popBack()
	{
		CCASSERT(!_data.empty(), "no objects added");
		auto last = _data.back();
		_data.pop_back();
		last->release();
	}

	void eraseObject(T object, bool removeAll = false)
	{
		CCASSERT(object != nullptr, "The object should not be nullptr");

		if (removeAll)
		{
			for (auto iter = _data.begin(), iter != _data.end();)
			{
				if ((*iter) == object)
				{
					iter = _data.erase(iter);
					object->release();
				}
				else
				{
					++iter;
				}
			}
		}
		else
		{
			auto iter = std::find(_data.begin(), _data.end(), object);
			if (iter != _data.end())
			{
				_data.erase(iter);
				object->release();
			}
		}
	}

	iterator erase(iterator position)
	{
		CCASSERT(position >= _data.begin() && position < _data.end(), "Invalid position!");
		(*position)->release();
		return _data.erase(position);
	}

	iterator erase(iterator first, iterator last)
	{
		for (auto iter = first; iter != last; ++iter)
		{
			(*iter)->release();
		}
		return _data.erase(first, last);
	}

	iterator erase(ssize_t index)
	{
		CCASSERT(!_data.empty() && index >= 0 && index < size(), "Invalid index!");
		auto it = std::next(begin(), index);
		(*it)->release();
		return _data.erase(it);
	}

	void clear()
	{
		for (auto it = std::begin(_data); it != std::end(_data); ++it)
		{
			(*it)->release();
		}
		_data.clear();
	}
protected:
	std::deque<T> _data;
};

NS_O_END;

#endif // !__ODEQUE_H__
