#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Player.h"

//======================================================
//Wander State

void WanderState::Enter(Enemy* entity) {

}

void WanderState::Execute(Enemy* entity) {
	//Check player location for detection
	Vector3 pDirection(entity->GetPos() - Player::GetInstance()->GetPos());
	double pDistance = pDirection.VectorMagnitude();

	if (pDistance <= 24) {
		//If player in range, chase them
		entity->ChangeState(entity->GetChase());
	}
}

void WanderState::Exit(Enemy* entity) {

}

//======================================================
//Chase State

void ChaseState::Enter(Enemy* entity) {
	//entity->PlaySound(4);
}

void ChaseState::Execute(Enemy* entity) {
	Vector3 target(Player::GetInstance()->GetPos() - entity->GetPos());
	double distance = target.VectorMagnitude();

	Vector3 unitTarget = target.UnitVector();

	Vector3 Vn(0, 1, 0);
	Vector3 Va(Player::GetInstance()->GetPos()), Vb(target);
	Vector3 cross = Va.CrossProduct(Vb);
	double dot = Vb.DotProduct(Va);

	double angle = atan2(cross.DotProduct(Vn), dot);
	angle *= 180 / 3.141592653;

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
		entity->PlaySound(3);
	}
	else {
		//Chase player down
		entity->MoveX(unitTarget.GetPointX());
		//entity->MoveY(unitTarget.GetPointY());
		entity->MoveZ(unitTarget.GetPointZ());

		entity->SetRot(0, angle - 240, 0);
	}
}

void ChaseState::Exit(Enemy* entity) {

}

//======================================================
//Attack State

void AttackState::Enter(Enemy* entity) {
	//entity->PlaySound(1);
}

void AttackState::Execute(Enemy* entity) {
	Vector3 Vn(0, 1, 0);
	Vector3 Va(Player::GetInstance()->GetPos()), Vb(Va - entity->GetPos());
	Vector3 cross = Va.CrossProduct(Vb);
	double dot = Vb.DotProduct(Va);

	double angle = atan2(cross.DotProduct(Vn), dot);
	angle *= 180 / 3.141592653;

	entity->MoveX(0);
	entity->MoveY(0);
	entity->MoveZ(0);

	entity->SetRot(0, angle - 240, 0);

	entity->Shoot();

	entity->ChangeState(entity->GetChase());
}

void AttackState::Exit(Enemy* entity) {

}

//======================================================
