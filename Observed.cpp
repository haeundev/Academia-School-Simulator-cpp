#include "stdafx.h"
#include "Observed.h"

void Observed::AddObserver(Observe* observer)
{
	_vObservers.push_back(observer);
}

void Observed::RemoveObserver(Observe* observer)
{
	for (int i = 0; i < _vObservers.size(); i++)
	{
		if (_vObservers[i] != observer)
			continue;

		_vObservers.erase(_vObservers.begin() + i);
		break;
	}
}

void Observed::Notify(MTYPE type, string event)
{
	for (int i = 0; i < _vObservers.size(); i++)
	{
		_vObservers[i]->OnNotify(type, event);
	}
}