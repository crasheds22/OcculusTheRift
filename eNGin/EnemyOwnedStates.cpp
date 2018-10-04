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
	
}

void WanderState::Execute(Enemy* entity) {
	
	entity->Wander();

}

void WanderState::Exit(Enemy* entity) {

}

//======================================================

ChaseState* ChaseState::Instance() {
	static ChaseState instance;

	return &instance;
}

void ChaseState::Enter(Enemy* entity) {

}

void ChaseState::Execute(Enemy* entity) {

	entity->Chase(Player::GetInstance()->GetPos());

}

void ChaseState::Exit(Enemy* entity) {

}

//======================================================

AttackState* AttackState::Instance() {
	static AttackState instance;

	return &instance;
}

void AttackState::Enter(Enemy* entity) {

}

void AttackState::Execute(Enemy* entity) {

	entity->Attack();

}

void AttackState::Exit(Enemy* entity) {

}

//======================================================

SearchState* SearchState::Instance() {
	static SearchState instance;

	return &instance;
}

void SearchState::Enter(Enemy* entity) {

}

void SearchState::Execute(Enemy* entity) {
	
	entity->Search(Player::GetInstance()->GetPos());
}

void SearchState::Exit(Enemy* entity) {

}

//======================================================
