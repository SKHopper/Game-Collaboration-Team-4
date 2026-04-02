

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MazeNavComp.generated.h"

//shmovin' diagonally
#define sqrtTwo 1.414f

//https://www.geeksforgeeks.org/dsa/a-search-algorithm/

USTRUCT()
struct FNavNode {
	GENERATED_BODY()

	//g = from start   h = heuristic direct

	FIntVector2 pos;
	float gCost = 0.f;
	float hCost = 0.f;
	FIntVector2 parent = FIntVector2(-1, -1);

	float fCost() {
		return gCost + hCost;
	}
};

USTRUCT()
struct FPositionDistance {

	GENERATED_BODY()

	FIntVector2 pos;
	float distance = 1.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class UNIT_2B_TEAM_4_API UMazeNavComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMazeNavComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//our location
	UPROPERTY(BlueprintReadWrite)
	FIntVector2 myPos;

	UFUNCTION(BlueprintCallable)
	TArray<FIntVector2> pathfind(FIntVector2 start, FIntVector2 target, float searchDistance);

	UFUNCTION(BlueprintImplementableEvent)
	bool isBlocked(FIntVector2 point);

	UFUNCTION()
	float heuristic(FIntVector2 from, FIntVector2 to);

	UFUNCTION()
	TArray<FIntVector2> makePath(TMap<FIntVector2, FIntVector2>& previous, FIntVector2& end);

	UFUNCTION()
	TArray<FPositionDistance> neighboursWithDistance(FIntVector2& centre);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
