#pragma once
#include "GgaetIp.h"
#include "Observe.h"

class Observed
{
private:
	vector<Observe*> _vObservers;

public:
	void AddObserver(Observe* observer);
	void RemoveObserver(Observe* observer);
	void Notify(MTYPE type, string event);
};