// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGame_FreeForAll.h"
#include "Player/ShooterPlayerState.h"
#include "Online/ShooterGameState.h"

AShooterGame_FreeForAll::AShooterGame_FreeForAll()
{
	bDelayedStart = true;
}

void AShooterGame_FreeForAll::DetermineMatchWinner()
{
	AShooterGameState const* const MyGameState = CastChecked<AShooterGameState>(GameState);
	float BestScore = MIN_flt;
	int32 BestPlayer = -1;
	int32 NumBestPlayers = 0;

	for (int32 i = 0; i < MyGameState->PlayerArray.Num(); i++)
	{
		const float PlayerScore = MyGameState->PlayerArray[i]->GetScore();
		if (BestScore < PlayerScore)
		{
			BestScore = PlayerScore;
			BestPlayer = i;
			NumBestPlayers = 1;
		}
		else if (BestScore == PlayerScore)
		{
			NumBestPlayers++;
		}
	}

	WinnerPlayerState = (NumBestPlayers == 1) ? Cast<AShooterPlayerState>(MyGameState->PlayerArray[BestPlayer]) : NULL;
}

bool AShooterGame_FreeForAll::IsWinner(AShooterPlayerState* PlayerState) const
{
	return PlayerState && !PlayerState->IsQuitter() && PlayerState == WinnerPlayerState;
}
