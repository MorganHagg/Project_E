// Engine classes
#include "UnitBase.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
// Custom classes
#include "../Input/ControllerBase.h"
#include "../AI/AIBase.h"
#include "../AI/AIPlayer.h"
#include "../AI/AIEnemy.h"
#include "../Ability/Ability.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DecalMaterial = LoadObject<UMaterialInterface>(
		nullptr,
		TEXT("/Game/Assets/Decal/UnitTarget_Mat")
	);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AUnitBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	if (AIControllerClass)
		switch (UnitType)
		{
	case EUnitFaction::Controlled:
			AIControllerClass = AAIPlayer::StaticClass();
			break;
	case EUnitFaction::Hostile:
			AIControllerClass = AAIEnemy::StaticClass();
			break;
		}
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	CreateDecal();
	SetPlayerController();
	InitStats();
}

void AUnitBase::CreateDecal()
{
	if (GetMesh())
		GetMesh()->bReceivesDecals = false;

	if (!DecalMaterial) return;

	DecalMatInstance = UMaterialInstanceDynamic::Create(DecalMaterial, this);

	FRotator DecalRotation = FRotator(-90.f, 0.f, 0.f);

	FVector DecalLocation = GetActorLocation();
	DecalLocation.Z -= 90.f;

	DecalComponent = UGameplayStatics::SpawnDecalAttached(
		DecalMatInstance,
		FVector (DecalThickness, DecalSize, DecalSize),
		GetRootComponent(),
		NAME_None,
		DecalLocation,
		DecalRotation,
		EAttachLocation::KeepWorldPosition,
		0.f
	);
	DecalComponent->SetVisibility(false);	// Starts the unit with decal off
	
}

void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitBase::ToggleSelect()
{
	if (!PlayerController) return;

	if (bool* bSelected = PlayerController->Squad.Find(this))
	{
		*bSelected = !(*bSelected);
	}
}

void AUnitBase::DrawDecal()
{
	if (DecalComponent)
		DecalComponent->SetVisibility(true);
}

void AUnitBase::RemoveDecal()
{
	if (DecalComponent)
		DecalComponent->SetVisibility(false);
}

void AUnitBase::SetDecalColor(FLinearColor Color)
{
	if (!DecalMatInstance) return;
	DecalMatInstance->SetVectorParameterValue(TEXT("TintColor"), Color);
}

void AUnitBase::SetPlayerController()
{
	PlayerController = Cast<AControllerBase>(GetWorld()->GetFirstPlayerController());
}

void AUnitBase::SetAIController(AAIBase* NewAIController)
{
	AIController = NewAIController;
}

void AUnitBase::InitStats()
{
	Stats.Add(StatName::Health, 100);
	Stats.Add(StatName::MaxHealth, 100);
	Stats.Add(StatName::Armour, 100);
	Stats.Add(StatName::MagicResist, -1);
	Stats.Add(StatName::Strength, -1);
	Stats.Add(StatName::Intellect, -1);
	Stats.Add(StatName::Agility, -1);
}

bool AUnitBase::GetStat(FName StatName, int& OutValue) const
{
	if (const int* Value = Stats.Find(StatName))
	{
		OutValue = *Value;
		return true;
	}

	return false;
}

void AUnitBase::ChangeStat(FName StatName, int NewStatValue)
{
	if (int* Value = Stats.Find(StatName))
		*Value = NewStatValue;
	else
		UE_LOG(LogTemp, Warning, TEXT("%s was not found in %s."),
			*StatName.ToString(),
			*GetName());
}

void AUnitBase::SetUnitType(EUnitFaction NewType)
{
	UnitType = NewType;
	switch (UnitType)
	{
	case EUnitFaction::Controlled:
		PlayerController->AddToSquad(this);
		break;
	case EUnitFaction::Hostile:
		if (PlayerController->Squad.Contains(this))
			PlayerController->RemoveFromSquad(this);	
		break;
	}
}
void AUnitBase::MoveTo(FVector Location)
{
	if (AIController)
		AIController->SetDestination(Location);
}

AUnitBase* AUnitBase::GetTarget()
{
	if (AIController)
	{
		return AIController->GetTarget();
	}
	else
		return nullptr;
}

void AUnitBase::ClearTarget()
{
	if (AIController)
		AIController->ClearTarget();
}

void AUnitBase::SetTarget(AUnitBase* Target)
{
	if (AIController)
		AIController->SetTarget(Target);
}

void AUnitBase::AddAbility(TSubclassOf<UAbility> NewAbility)
{
	if (!NewAbility) {UE_LOG(LogTemp, Error, TEXT("No ability chosen")) return;};

	int Index = GrantedAbilities.Find(NewAbility);
	if (Index == INDEX_NONE)
		GrantedAbilities.Add(NewAbility);
	else
		UE_LOG(LogTemp, Warning, TEXT("AddAbility: Ability already granted at slot %d"), Index);
}

void AUnitBase::ReplaceAbility(TSubclassOf<UAbility> OldAbility, TSubclassOf<UAbility> NewAbility)
{
	if (!OldAbility || !NewAbility) {UE_LOG(LogTemp, Error, TEXT("No ability chosen")) return;};

	int Index = GrantedAbilities.Find(OldAbility);
	if (Index != INDEX_NONE)
		GrantedAbilities[Index] = NewAbility;
	else
		UE_LOG(LogTemp, Warning, TEXT("%s was not found in GrantedAbilities."), *OldAbility->GetName())
	
}

void AUnitBase::RemoveAbility(TSubclassOf<UAbility> OldAbility)
{
	if (!OldAbility) {UE_LOG(LogTemp, Error, TEXT("No ability chosen")) return;};
	int Index = GrantedAbilities.Find(OldAbility);
	if (Index != INDEX_NONE)
		GrantedAbilities.RemoveAt(Index);
}

void AUnitBase::ActivateAbility(int AbilityIndex)
{
	if (!GrantedAbilities.IsValidIndex(AbilityIndex)) return;
	UAbility* Ability = NewObject<UAbility>(this, GrantedAbilities[AbilityIndex]);
	if (Ability)
		Ability->Initiate(this);
}

int AUnitBase::GetCurrentHealth()
{
	int Health;
	GetStat(StatName::Health,Health);
	return Health;
}

int AUnitBase::GetMaxHealth()
{
	int MaxHealth;
	GetStat(StatName::MaxHealth,MaxHealth);
	return MaxHealth;
}

void AUnitBase::ReceiveDamage(int Damage)
{
	ChangeHealth(-Damage);
}

void AUnitBase::ReceiveHeal(int Healing)
{
	ChangeHealth(Healing);
}

void AUnitBase::ChangeHealth(int ChangeInHealth)
{
	int Health;
	int MaxHealth;
	GetStat(StatName::Health,Health);
	GetStat(StatName::MaxHealth,MaxHealth);
	int NewHealth = FMath::Clamp(Health + ChangeInHealth, 0, MaxHealth);;
	ChangeStat(StatName::Health, NewHealth);
	if (NewHealth == 0)
		Die();
}

void AUnitBase::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("I died lol"))
}
