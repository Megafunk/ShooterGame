// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_HasLoSTo.generated.h"

// Checks if the AI pawn has Line of sight to the specified Actor or Location(Vector).
UCLASS()
class SHOOTERGAME_API UBTDecorator_HasLoSTo : public UBTDecorator
{
	GENERATED_BODY()
public:

	UBTDecorator_HasLoSTo();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	
	UPROPERTY(EditAnywhere, Category = Condition)
 	struct FBlackboardKeySelector EnemyKey;

private:
	bool LOSTrace(AActor* InActor, AActor* InEnemyActor, const FVector& EndLocation) const;	
};
