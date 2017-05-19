// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto patrolRouteComp = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRoute>();

	if (!ensure(patrolRouteComp)) { return EBTNodeResult::Aborted; }

	// Get Patrol Points
	auto patrolPointsArr = patrolRouteComp->GetPatrolPoints();

	if (patrolPointsArr.Num() <= 0)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("No patrol points for %s"), *OwnerComp.GetAIOwner()->GetPawn()->GetName())
		return EBTNodeResult::Aborted;
	}

	// Set Next Waypoint
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, patrolPointsArr[index]);

	// Cycle Index
	int32 newIndex = (index + 1) % patrolPointsArr.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, newIndex);

	return EBTNodeResult::Succeeded;
}
