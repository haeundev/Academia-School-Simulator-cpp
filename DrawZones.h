#pragma once
#include "GgaetIp.h"
#include <stack>
#include <atlconv.h>

class DrawZones : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	stack<string> _sStoreZoneKey;

	vector<Object*>* _vTiles;

	Vector2 _startIndex;
	Vector2 _endIndex;

	Vector2 _currentIndex;

	vector<Vector2> _vVertices;

	// 만들어진 Zone을 담을 컨테이너
	map<string, int> _mZones;

	bool _admissionsReady = false;

	Object* _realtimePoly;

public:
	virtual void Init() override;
	virtual void Update() override;

	void DrawZone();

	stack<string>& GetSStoreZoneKey() { return _sStoreZoneKey; }

	map<string, int> GetMZones() { return _mZones; }

	void SetVTilesLink(vector<Object*>* v) { _vTiles = v; }

	wstring StringToWstring(string str)
	{
		USES_CONVERSION;
		return std::wstring(A2W(str.c_str()));
	}
};