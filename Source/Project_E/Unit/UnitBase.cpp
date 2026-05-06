// Engine classes
#include "UnitBase.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
// Custom classes
#include "AudioMixerBlueprintLibrary.h"
#include "../Input/PlayerControls.h"
#include "../AI/AIUnit.h"
#include "../Ability/Ability.h"
#include "../Misc/FUnitSpawnDataRow.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DecalMaterial = LoadObject<UMaterialInterface>(
		nullptr,
		TEXT("/Game/Assets/Decal/UnitTarget_Mat")
	);
	AutoPossessAI = EAutoPossessAI::Spawned;
	AIControllerClass = AAIUnit::StaticClass();
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	CreateDecal();
	SetPlayerController();
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
	PlayerController = Cast<APlayerControls>(GetWorld()->GetFirstPlayerController());
}

void AUnitBase::SetAIController(AAIUnit* NewAIController)
{
	AIController = NewAIController;
}

void AUnitBase::InitFromSpawnData()
{
	UDataTable* StatTable = LoadObject<UDataTable>(nullptr,
		TEXT("/Game/Framework/DataTable/DT_UnitSpawnData.DT_UnitSpawnData"));
	if (!StatTable) return;

	
	FName RowName = FName(*StaticEnum<EUnitArchetype>()->GetNameStringByValue((int64)Archetype));
	FFUnitSpawnDataRow* Row = StatTable->FindRow<FFUnitSpawnDataRow>(RowName, TEXT("InitData"));
	if (!Row)
	{
		UE_LOG(LogTemp, Warning, TEXT("No stat row found for %s"), *GetClass()->GetDisplayNameText().ToString());
		return;
	}
	
	GetMesh()->SetSkeletalMesh(Row->Mesh);
	FixLocAndRot();
	BehaviorTree = Row->BehaviorTree;
	if (AIController && BehaviorTree)
		AIController->RunBehaviorTree(BehaviorTree);
	GrantedAbilities = Row->DefaultAbilities;
	Stats = Row->Stats;
}

bool AUnitBase::GetStat(EStat Stat, float& OutValue) const
{
	if (const float* Value = Stats.Find(Stat))
	{
		OutValue = *Value;
		return true;
	}

	return false;
}

void AUnitBase::ChangeStat(EStat Stat, float NewStatValue)
{
	if (float* Value = Stats.Find(Stat))
		*Value = NewStatValue;
	else
		UE_LOG(LogTemp, Warning, TEXT("%s was not found in %s."),
			*UEnum::GetDisplayValueAsText(Stat).ToString(),
			*GetName());
}

void AUnitBase::SetFaction(EUnitFaction NewFaction)
{
	UnitFaction = NewFaction;
	switch (NewFaction)
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

void AUnitBase::SetArchetype(EUnitArchetype NewArchetype)
{
	Archetype = NewArchetype;
}

// Sets the Unit at the bottom of capsule component, and rotates it correctly
void AUnitBase::FixLocAndRot()
{
	GetMesh()->SetRelativeLocationAndRotation(
	FVector(											// offset down to feet
		0.f,
		0.f,
		-GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
	FRotator(0.f, -90.f, 0.f)			// rotate to face forward
	);
}

float AUnitBase::GetCurrentHealth()
{
	float Health;
	GetStat(EStat::Health,Health);
	return Health;
}

float AUnitBase::GetMaxHealth()
{
	float MaxHealth;
	GetStat(EStat::MaxHealth,MaxHealth);
	return MaxHealth;
}

void AUnitBase::ReceiveDamage(float RawDamage, EDamageType DamageType)
{
	float Damage = FMath::RoundToInt(
		RawDamage * MitigationFactor(DamageType) * AbilityFactor()	);
	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);
	ChangeHealth(-Damage);
}

void AUnitBase::ReceiveHeal(float RawHealing)
{
	float Healing = FMath::RoundToInt(
		RawHealing * AbilityFactor()	);
	ChangeHealth(Healing);
}

void AUnitBase::ChangeHealth(float ChangeInHealth)
{
	float Health;
	float MaxHealth;
	GetStat(EStat::Health,Health);
	GetStat(EStat::MaxHealth,MaxHealth);
	int NewHealth = FMath::Clamp(Health + ChangeInHealth, 0, MaxHealth);
	ChangeStat(EStat::Health, NewHealth);
	if (NewHealth == 0)
		Die();
}

float AUnitBase::MitigationFactor(EDamageType DamageType)
{
	float MaxArmour = 75;		//TODO: Put this somewhere it makes sense
	float MaxMagicResist = 75;	//TODO: Put this somewhere it makes sense

	// 0.8 means early armour contributes slightly more than late armour
	float Curve = 0.8;
	float Mitigation;
	float MaxValue;
	
	switch (DamageType)
	{
	default:
		return 1.f; // no mitigation for unhandled damage types
	case EDamageType::Physical:
		GetStat(EStat::Armour, Mitigation);
		MaxValue = MaxArmour;
		break;
	case EDamageType::Magical:
		GetStat(EStat::MagicResist, Mitigation);
		MaxValue = MaxMagicResist;
		break;
	}
	Mitigation = FMath::Clamp(Mitigation, 0.f, MaxValue);
	float Reduction = 1 - (0.75 * FMath::Pow(Mitigation/MaxValue, Curve));

	return Reduction;;
}

float AUnitBase::AbilityFactor()
{
	/*	Run through an array of effects and check if they are affecting damage received
	 *
	 */
	return 1.f;
}


void AUnitBase::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("I died lol"))
}
