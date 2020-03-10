#include "stdafx.h"
#include "GgaetIp.h"

void BoxCollider::Update()
{
    Collider::Update();
}

BoxCollider::BoxCollider()
{
    size = Vector2::zero;
}

void BoxCollider::SetSize(Vector2 _size)
{
    size = _size * 2;
    transform->SetSize({ 0,0, size.x,size.y });
    synchronizeSprite = false;
}

Vector2 BoxCollider::GetSize()
{
    return size;
}

bool BoxCollider::PtInCollider(Vector2 point)
{
    Transform* cameraTransform = CameraManager::GetInstance()->GetRenderCamera()->GetTransform();
    RECT rect;
    if (synchronizeSprite)
        rect = transform->GetRect();
    else
    {
        rect.left = -size.x / 2;
        rect.right = size.x / 2;
        rect.top = -size.y / 2;
        rect.bottom = size.y / 2;
    }
    Vector2 delta = DesignResolution / ApplicationManager::GetInstance()->GetResolution();
    Vector3 worldPointPosition = Vector3(point.x * delta.x, point.y * delta.y, 1);
    if (object->GetCameraAffected())
        worldPointPosition = Matrix3x3::Mul(worldPointPosition, cameraTransform->GetLocalToWorldMatrix().GetInverseMatrix());
    worldPointPosition = Matrix3x3::Mul(worldPointPosition, transform->GetLocalToWorldMatrix().GetInverseMatrix());

    return rect.top < worldPointPosition.y && rect.bottom > worldPointPosition.y && rect.right > worldPointPosition.x&& rect.left < worldPointPosition.x;
}

void BoxCollider::Init()
{
    Collider::Init();
    RECT rect = transform->GetRect();
    Vector2 scale = transform->GetScale();

    Vector2 position = transform->GetWorldPosition() * PhysicsManager::GetInstance()->GetWorldToPhysicsWorld();

    b2BodyDef bodyDef;
    bodyDef.angle = transform->GetRotation() * Deg2Rad;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.userData = object;
    bodyDef.allowSleep = false;
    bodyDef.fixedRotation = fixedRotation;
    if (physicsComponent != nullptr)
        bodyDef.type = (b2BodyType)physicsComponent->GetBodyType();
    else
        bodyDef.type = b2BodyType::b2_staticBody;
    body = PhysicsManager::GetInstance()->AddPhysicsBody(&bodyDef);

    Vector2 size;
    if (synchronizeSprite)
        size = Vector2(rect.right - rect.left, rect.bottom - rect.top);
    else
        size = this->size;
    size = size * scale * PhysicsManager::GetInstance()->GetWorldToPhysicsWorld();

    b2PolygonShape shape;
    shape.SetAsBox(size.x / 2, size.y / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    if (physicsComponent != nullptr)
    {
        fixtureDef.density = physicsComponent->GetDensity();
        fixtureDef.friction = physicsComponent->GetFriction();
        fixtureDef.restitution = physicsComponent->GetRestitution();
        fixtureDef.isSensor = physicsComponent->GetIgnoreCollision();
    }
    else
    {
        fixtureDef.density = 1;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 0;
        fixtureDef.isSensor = false;
    }
    //fixtureDef.filter = filter;
    fixture = body->CreateFixture(&fixtureDef);
}

void BoxCollider::Release()
{
    //SceneManager::GetInstance()->GetNowScene()->DeletePhysicsBody(body);
    Collider::Release();
}

void BoxCollider::UpdateSize()
{
    if (!body)
        return;
    if (fixture)
        body->DestroyFixture(fixture);
    Vector2 scale = transform->GetScale();
    RECT rect = transform->GetRect();
    Vector2 size;
    if (synchronizeSprite)
        size = Vector2(rect.right - rect.left, rect.bottom - rect.top);
    else
        size = this->size;
    size = size * scale * PhysicsManager::GetInstance()->GetWorldToPhysicsWorld();

    b2PolygonShape shape;
    shape.SetAsBox(size.x / 2, size.y / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    if (physicsComponent != nullptr)
    {
        fixtureDef.density = physicsComponent->GetDensity();
        fixtureDef.friction = physicsComponent->GetFriction();
        fixtureDef.restitution = physicsComponent->GetRestitution();
        fixtureDef.isSensor = physicsComponent->GetIgnoreCollision();
    }
    else
    {
        fixtureDef.density = 1;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 0;
        fixtureDef.isSensor = false;
    }
    fixture = body->CreateFixture(&fixtureDef);
}