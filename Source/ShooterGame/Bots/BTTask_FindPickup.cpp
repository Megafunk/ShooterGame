// Copyright Epic Games, Inc. All Rights Reserved.

#include "BTTask_FindPickup.h"
#include "Bots/ShooterAIController.h"
#include "Bots/ShooterBot.h"
#include "Online/ShooterGameMode.h"
#include "Weapons/ShooterWeapon_Instant.h"
#include "Pickups/ShooterPickup_Ammo.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTask_FindPickup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* MyController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	AShooterBot* MyBot = MyController ? Cast<AShooterBot>(MyController->GetPawn()) : NULL;
	if (MyBot == NULL)
	{
		return EBTNodeResult::Failed;
	}

	AShooterGameMode* GameMode = MyBot->GetWorld()->GetAuthGameMode<AShooterGameMode>();
	if (GameMode == NULL)
	{
		return EBTNodeResult::Failed;
	}

	const FVector MyLoc = MyBot->GetActorLocation();
	AShooterPickup_Ammo* BestPickup = NULL;
	float BestDistSq = MAX_FLT;

	for (int32 i = 0; i < GameMode->LevelPickups.Num(); ++i)
	{
		AShooterPickup_Ammo* AmmoPickup = Cast<AShooterPickup_Ammo>(GameMode->LevelPickups[i]);
		if (AmmoPickup && AmmoPickup->IsForWeapon(AShooterWeapon_Instant::StaticClass()) && AmmoPickup->CanBePickedUp(MyBot))
		{
			const float DistSq = (AmmoPickup->GetActorLocation() - MyLoc).SizeSquared();
			if (BestDistSq == -1 || DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPickup = AmmoPickup;
			}
		}
	}

	if (BestPickup)
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), BestPickup->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
