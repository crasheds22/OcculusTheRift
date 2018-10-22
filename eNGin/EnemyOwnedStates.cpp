#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Player.h"

#include <iostream>
using namespace std;

//======================================================
//Wander State

WanderState::WanderState(Enemy* entity) {
	flags = entity->GetFlags();

	fIter = flags.begin();
}

void WanderState::Enter(Enemy* entity) {

}

void WanderState::Execute(Enemy* entity) {
	//Check player location for detection
	Vector3 pDirection(entity->GetPos() - Player::GetInstance()->GetPos());
	double pDistance = pDirection.VectorMagnitude();

	if (pDistance <= 24) {
		//If player in range, chase them
		entity->ChangeState(entity->GetChase(*fIter));
	}

	//Move to flag
	Vector3 temp = *fIter;

	Vector3 direction(temp - entity->GetPos());
	double distance = direction.VectorMagnitude();

	direction = direction.UnitVector();

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

void WanderState::Exit(Enemy* entity) {

}

//======================================================
//Chase State

void ChaseState::Enter(Enemy* entity) {

}

void ChaseState::Execute(Enemy* entity) {
	Vector3 target(Player::GetInstance()->GetPos() - entity->GetPos());
	double distance = target.VectorMagnitude();

	Vector3 unitTarget = target.UnitVector();

	Vector3 Vn(0, 1, 0);
	Vector3 Va(Player::GetInstance()->GetPos()), Vb(target);
	Vector3 cross = Vb.CrossProduct(Va);
	double dot = Va.DotProduct(Vb);

	double angle = atan2(cross.DotProduct(Vn), dot);
	angle *= 180 / 3.141592653;

	if (angle < 0)
		angle = -angle;

	if (distance <= 8.0) {
		//Close enough to attack
		entity->MoveX(0);
		entity->MoveY(0);
		entity->MoveZ(0);

		entity->ChangeState(entity->GetAttack());
	}
	else if (distance > 24.0) {
		//Player out of range
		entity->ChangeState(entity->GetWander());
	}

	//Chase player down
	entity->MoveX(unitTarget.GetPointX());
	entity->MoveY(unitTarget.GetPointY());
	entity->MoveZ(unitTarget.GetPointZ());

	entity->SetRot(0, entity->GetRot().GetPointY() + angle, 0);
}

void ChaseState::Exit(Enemy* entity) {

}

void ChaseState::SetLastTarget(Vector3 last) {
	lastTarget.SetPointX(last.GetPointX());
	lastTarget.SetPointY(last.GetPointY());
	lastTarget.SetPointZ(last.GetPointZ());
}

//======================================================
//Attack State

void AttackState::Enter(Enemy* entity) {
}

void AttackState::Execute(Enemy* entity) {
	entity->MoveX(0);
	entity->MoveY(0);
	entity->MoveZ(0);

	entity->Shoot();

	entity->ChangeState(entity->GetChase(Player::GetInstance()->GetPos()));
}

void AttackState::Exit(Enemy* entity) {

}

//======================================================
