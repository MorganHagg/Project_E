//Engine classes
#include "AIControls.h"
#include "BehaviorTree/BehaviorTree.h"
// Custom classes
#include "../Misc/UnitManager.h"
#include "../Unit/UnitBase.h"
#include "../Component/UnitHandler.h"


AAIControls::AAIControls()
{
	PrimaryActorTick.bCanEverTick = true;
	UnitHandler = CreateDefaultSubobject<UUnitHandler>(TEXT("UnitHandler"));
}

void AAIControls::BeginPlay()
{
	Super::BeginPlay();
	UUnitManager* UnitManager = GetGameInstance()->GetSubsystem<UUnitManager>();
	FVector Location = GetPawn()->GetActorLocation();
	UnitHandler->AddToSquad(UnitManager->SpawnUnit(EUnitArchetype::Warrior, Location, this));
}

void AAIControls::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BehaviorTree = LoadObject<UBehaviorTree>(nullptr,
	TEXT("/Game/Framework/AI/AICommander/BT_AICommander.BT_AICommander"));
	if (BehaviorTree)
			RunBehaviorTree(BehaviorTree);
}

void AAIControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}