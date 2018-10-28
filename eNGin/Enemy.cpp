#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* own, Model* mod, Texture* tex, float xPos, float yPos, float zPos) : Actor(mod, tex),
																												 owner(own),
																												 shootTime(2),
																												 shootTimer(shootTime),
	damageTime(1),
	damageTimer(damageTime)
{
	SetPos(xPos, yPos, zPos);
	SetMoveSpeed(4);
	SetRotateSpeed(5);

	wander = new WanderState();
	chase = new ChaseState();
	attack = new AttackState();

	currentState = wander;
	stopTime = 0.03;

	SetMaxHealth(2);
	SetCurrentHealth(2);
}

Enemy::~Enemy() {
	delete wander;
	wander = NULL;

	delete chase;
	chase = NULL;

	delete attack;
	attack = NULL;

	delete currentState;
	currentState = NULL;

	delete owner;
	owner = NULL;
}

void Enemy::Update(float deltaTime, std::map<int, std::vector<Actor*>> entityMap) {
	dT = deltaTime;

	if (currentState) {
		currentState->Execute(this);
	}

	float boxSize = 2.2;

	collisionBox.SetMaxPoint(GetPos().GetPointX() + boxSize, GetPos().GetPointY() + boxSize, GetPos().GetPointZ() + boxSize);
	collisionBox.SetMinPoint(GetPos().GetPointX() - boxSize, GetPos().GetPointY() - boxSize, GetPos().GetPointZ() - boxSize);

	//Check for Wall Collisions
	for (std::size_t ii = 0; ii < entityMap[2].size(); ii++)
	{
		if (collisionBox.AABBtoAABB(entityMap[2][ii]->GetCollider()))
		{
			collisionBox.CollideWith(this, *entityMap[2][ii]);

		}
	}
	//Check for other enemy collisions
	if (stopTimer > 0)
	{
		stopTimer -= deltaTime;
	}
	else
	{
		for (std::size_t ii = 0; ii < entityMap[1].size(); ii++)
		{
			if (collisionBox.AABBtoAABB(entityMap[1][ii]->GetCollider()))
			{
				collisionBox.CollideWith(this, *entityMap[1][ii]);
				stopTimer = stopTime;
			}

		}
	}

	//Check for projectile collisions
	for (std::size_t ii = 0; ii < entityMap[5].size(); ii++)
	{
		if (entityMap[5][ii] != NULL) {
			if (collisionBox.AABBtoAABB(entityMap[5][ii]->GetCollider()))
			{
				Projectile *p = dynamic_cast<Projectile*>(entityMap[5][ii]);
				if (p) {
					if (!p->GetIsEnemy()) {
						if (damageTimer <= 0) {
							SetCurrentHealth(GetCurrentHealth() - 1);
							owner->PlaySoundAt(4);
							damageTimer = damageTime;
						}
					}
				}
			}
		}
	}

	shootTimer -= dT;
	damageTimer -= dT;
}

void Enemy::ChangeState(State* newState) {
	currentState->Exit(this);

	currentState = newState;

	currentState->Enter(this);
}

State* Enemy::GetWander() {
	return wander;
}

State* Enemy::GetChase() {
	return chase;
}

State* Enemy::GetAttack() {
	return attack;
}

void Enemy::Shoot() {
	if (shootTimer <= 0) {
		owner->AddProjectile(this, this->GetPos(), (owner->GetPlayer()->GetPos() - this->GetPos()).UnitVector() * 3, 18, true);
		
		shootTimer = shootTime;
	}
}

float Enemy::GetdT() {
	return dT;
}

void Enemy::PlaySound(int index)
{
	owner->PlaySoundAt(index);
}

bool Enemy::IsStopped()
{
	return (stopTimer <= 0);
}

//=============================================================================

//========================================
// Functions that move the Actor
//========================================

void Enemy::MoveX(double moveX) {
	double newX = 0.0;

	newX = position.GetPointX() + (moveX * moveSpeed * dT);

	position.SetPointX(newX);
}

void Enemy::MoveY(double moveY) {
	double newY = 0.0;

	newY = position.GetPointY() + (moveY * moveSpeed * dT);

	position.SetPointY(newY);
}

void Enemy::MoveZ(double moveZ) {
	double newZ = 0.0;

	newZ = position.GetPointZ() + (moveZ * moveSpeed * dT);

	position.SetPointZ(newZ);
}
