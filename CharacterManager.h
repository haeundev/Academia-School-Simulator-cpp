#pragma once
#include "GgaetIp.h"
#include <stack>
#include "MapTool.h"
#include "Observe.h"

class TopBar;
class Schedule;
class CharacterManager : public Script, public Observe
{
private:
	map<string, int> _mFaculty;
	map<string, int> _mZones;
	int _facultyNum = 0;
	vector<Object*> _vNurse;
	vector<Object*> _vPrincipal;
	vector<Object*> _vStaff;
	vector<Object*> _vStudents;
	vector<Object*> _vWorkers;
	vector<Object*> _vJanitors;
	vector<Object*> _vAllCharacters;

	vector<Object*>* _vTiles;

	TopBar* _topBar;

	list<string> _lStudentNames;

	int _wNum = 1;
	int _jNum = 0;
	int _sNum = 0;

	MapTool* _mapTool;

	Schedule* _schedule;

public:
	virtual void Init() override;

	void CreateFaculty(string name);
	void CreateNurse();
	void CreatePrincipal();
	void CreateStudent();
	void CreateWorker();
	void CreateJanitor();

	void FireFaculty(string name);
	void FireNurse();
	void ExpelStudent(Object* object);
	void FireWorker();
	void FireJanitor();

	void SetVTilesLink(vector<Object*>* v) { _vTiles = v; }
	void SetTopBarLink(TopBar* t) { _topBar = t; }
	void SetMZonesLink(map<string, int> m) { _mZones = m; }
	void SetMapToolLink(MapTool* m) { _mapTool = m; }
	void SetScheduleLink(Schedule* s) { _schedule = s; }

	map<string, int> GetMFaculty() { return _mFaculty; }
	int GetFacultyNum() { return _facultyNum; }
	vector<Object*> GetVStaff() { return _vStaff; }
	vector<Object*> GetVStudents() { return _vStudents; }
	vector<Object*> GetVWorkers() { return _vWorkers; }
	vector<Object*> GetVJanitors() { return _vJanitors; }

	virtual void OnNotify(MTYPE type, string event) override;
};