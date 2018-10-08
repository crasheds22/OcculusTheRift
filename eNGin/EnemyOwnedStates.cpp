#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Player.h"

//==================
#include <iostream>
//==================

//======================================================

WanderState* WanderState::Instance() {
	static WanderState instance;

	return &instance;
}

void WanderState::Enter(Enemy* entity) {
	std::cout << "Enter wander state" << std::endl;
}

void WanderState::Execute(Enemy* entity) {
	//Check player location for detection
	Vector3 pDirection(entity->GetLR() - Player::GetInstance()->GetLR(), entity->GetUD() - Player::GetInstance()->GetUD(), entity->GetFB() - Player::GetInstance()->GetFB());
	double pDistance = pDirection.VectorMagnitude();

	if (pDistance <= 24) {
		//If player in range
		entity->ChangeState(ChaseState::Instance());
	}
	else {
		//Move to next flag in list
		Vector3 temp = *fIter;

		Vector3 direction(temp.GetPointX() - entity->GetLR(), temp.GetPointY() - entity->GetUD(), temp.GetPointZ() - entity->GetFB());
		double distance = direction.VectorMagnitude();

		if (distance <= 2.0) {
			if (fIter == flags.end()) {
				fIter = flags.begin();
			}
			else {
				fIter++;
			}
		}
		else {
			entity->MoveX(direction.GetPointX());
			entity->MoveY(direction.GetPointY());
			entity->MoveZ(direction.GetPointZ());
		}
	}
}

void WanderState::Exit(Enemy* entity) {
	std::cout << "Exit wander state" << std::endl;
}

void WanderState::SetFlags(std::vector<Vector3> tempFlags) {
	flags = tempFlags;

	fIter = flags.begin();
}

//======================================================

ChaseState* ChaseState::Instance() {
	static ChaseState instance;

	return &instance;
}

void ChaseState::Enter(Enemy* entity) {
	std::cout << "Chase state enter" << std::endl;
}

void ChaseState::Execute(Enemy* entity) {
	Vector3 target = Player::GetInstance()->GetPos();
	double distance = target.VectorMagnitude();

	if (distance <= 8.0) {
		//Close enough to attack
		entity->ChangeState(AttackState::Instance());
	}
	else if (distance >= 24.0) {
		//Get last known player position, move towards it.
		entity->ChangeState(WanderState::Instance());
	}
	else {
		//Chase player down
		entity->MoveX(target.GetPointX());
		entity->MoveY(target.GetPointY());
		entity->MoveZ(target.GetPointZ());
	}
}

void ChaseState::Exit(Enemy* entity) {
	std::cout << "Exit chase state" << std::endl;
}

//======================================================

AttackState* AttackState::Instance() {
	static AttackState instance;

	return &instance;
}

void AttackState::Enter(Enemy* entity) {
	std::cout << "Enter attack state" << std::endl;
}

void AttackState::Execute(Enemy* entity) {

	entity->ChangeState(ChaseState::Instance());

}

void AttackState::Exit(Enemy* entity) {
	std::cout << "Exit attack state" << std::endl;
}

//======================================================
