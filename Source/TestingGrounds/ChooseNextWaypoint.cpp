// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"
#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto pawn = OwnerComp.GetAIOwner()->GetPawn();

	// Get Patrol Points
	auto patrolPointsArr = Cast<APatrollingGuard>(pawn)->PatrolPointsCPP;

	// Set Next Waypoint
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, patrolPointsArr[index]);

	// Cycle Index
	int32 newIndex = (index + 1) % patrolPointsArr.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, newIndex);

	return EBTNodeResult::Succeeded;
}
