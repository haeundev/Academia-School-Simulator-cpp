#pragma once
#include "GgaetIp.h"
#include "Tile.h"
#include <queue>
#include "Observed.h"

struct ObjData
{
    char name[50];
    Vector2 position;
    int depth;
    bool isActive;
};

struct TileData
{
    Vector2 position;
    ATTRIBUTE attribute;
    unsigned char flag;
    Vector2 index;
    bool isActive;
};

struct WallData
{
    Vector2 position;
    Vector2 index;
    char name[50];
    char tag[50];
    int depth;
    bool isActive;
};

struct tagWork
{
    Vector2 workAreaIndex;
    Object* object;
    bool isDummy;
    bool isDone;
};

class FollowMouseSprite;
class Budget;
class ObjectData;
class MapTool :	public Script, public Observed
{
private:
    vector<Object*>* _vTiles;
    FollowMouseSprite* _followMouseSprite;

    Vector2 _floorStartIndex;
	Vector2 _floorEndIndex;

    ObjectData* _attributeInfo;
    ATTRIBUTE _attribute;
    map<string, ATTRIBUTE> _mNameAndAttribute;
    int _cost;

    Vector2 _mousePosition;
    Vector3 _mousePosition_V3;
    Vector3 _mouseWorldPosition;
    float _mouseX;
    float _mouseY;
    
    Vector2 _currentIndex;

    Object* _newWall;
    Sprite* _newWallSprite;

    vector<Object*> _vWalls;

    vector<Object*> _vAllItems;

    Object* _realtimePoly;

    map<string, queue<tagWork>> _mWorkLoad;

    Budget* _budget;

    int i = 1;

public:
    virtual void Init() override;
    virtual void Update() override;

    void SetVTilesLink(vector<Object*>* v) { _vTiles = v; }
    void SetFollowMouseSpriteLink(FollowMouseSprite* s) { _followMouseSprite = s; }
    void SetAttributeInfoLink(ObjectData* o) { _attributeInfo = o; }
    void SetBudgetLink(Budget* b) { _budget = b; }
    
    void PlaceObjects();
    void PlaceWalls();
    void PlaceFloors();

	void Save();
	void Load();

    map<string, queue<tagWork>>& GetMWorkLoad() { return _mWorkLoad; }
};