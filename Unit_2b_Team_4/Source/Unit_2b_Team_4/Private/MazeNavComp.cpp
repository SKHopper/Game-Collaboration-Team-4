


#include "MazeNavComp.h"


// Sets default values for this component's properties
UMazeNavComp::UMazeNavComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMazeNavComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

TArray<FIntVector2>  UMazeNavComp::pathfind(FIntVector2 start, FIntVector2 target, float searchDistance) {

	if (FVector2D::Distance({ double(start.X), double(start.Y) }, { double(target.X), double(target.Y) }) > searchDistance) {
		return {}; 
	}

	TMap<FIntVector2, FNavNode> toSearch;
	TSet<FIntVector2> searched;
	TMap<FIntVector2, FIntVector2> bestPrevious;

	FNavNode startNode;
	startNode.pos = start;
	startNode.gCost = 0.f;
	startNode.hCost = heuristic(start, target);
	toSearch.Add(start, startNode);

	while (toSearch.Num() > 0) {

		//get lowest

		FIntVector2 current = { 0, 0 };
		float lowestFCost = 1234567890;
		
		for (TPair<FIntVector2, FNavNode>& searchPair : toSearch) {
			if (searchPair.Value.fCost() < lowestFCost) {
				lowestFCost = searchPair.Value.fCost();
				current = searchPair.Key;
			}
		}

		//check there yet
		if (current == target) { return makePath(bestPrevious, current); }

		//not there yet move on
		FNavNode currentNode = toSearch[current];
		toSearch.Remove(current);
		searched.Add(current);

		for (FPositionDistance neighbourPair : neighboursWithDistance(current)) {
			FIntVector2 neighbour = neighbourPair.pos;
			float distance = neighbourPair.distance;

			//validate
			if (
				searched.Contains(neighbour) 
				or isBlocked(neighbour)
				or FVector2D::Distance({ double(start.X), double(start.Y) }, { double(neighbour.X), double(neighbour.Y) }) > searchDistance
			) { 
				continue; 
			}

			float newGCost = currentNode.gCost + distance;

			if (not toSearch.Contains(neighbour) or newGCost < toSearch.Find(neighbour)->gCost) {

				FNavNode neighbourNode;
				neighbourNode.pos = neighbour;
				neighbourNode.gCost = newGCost;
				neighbourNode.hCost = heuristic(neighbour, target);

				toSearch.Add(neighbour, neighbourNode);
				bestPrevious.Add(neighbour, current);
			}
		}
	}
	
	//fail
	return {};
}

float UMazeNavComp::heuristic(FIntVector2 from, FIntVector2 to)
{
	int32 x = FMath::Abs(from.X - to.X);
	int32 y = FMath::Abs(from.Y - to.Y);
	return sqrtTwo * FMath::Min(x, y) + FMath::Abs(x - y);
}

TArray<FIntVector2> UMazeNavComp::makePath(TMap<FIntVector2, FIntVector2>& previous, FIntVector2& end) {
	TArray<FIntVector2> path;

	FIntVector2 current = end;
	//prepend from end
	while (previous.Contains(current)) {
		path.Insert(current, 0);
		current = previous[current];
	}

	//needs start
	path.Insert(current, 0);
	return path;
	
}

TArray<FPositionDistance> UMazeNavComp::neighboursWithDistance(FIntVector2& centre)
{
	return {
		//norf souf eass wess
		{ FIntVector2(centre.X + 1, centre.Y), 1.0f },
		{ FIntVector2(centre.X - 1, centre.Y), 1.0f },
		{ FIntVector2(centre.X, centre.Y + 1), 1.0f },
		{ FIntVector2(centre.X, centre.Y - 1), 1.0f },
		//diagonal
		{ FIntVector2(centre.X + 1, centre.Y + 1), sqrtTwo },
		{ FIntVector2(centre.X - 1, centre.Y + 1), sqrtTwo },
		{ FIntVector2(centre.X + 1, centre.Y - 1), sqrtTwo },
		{ FIntVector2(centre.X - 1, centre.Y - 1), sqrtTwo }
	};
}

// Called every frame
void UMazeNavComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


