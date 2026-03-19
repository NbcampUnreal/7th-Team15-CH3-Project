#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/AHPlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Interface/AHInteractInterface.h"
#include "AHBaseItem.generated.h"


UCLASS()
class LEVELTEST_API AAHBaseItem : public AActor, public IAHInteractInterface
{
	GENERATED_BODY()
	
public:	
	AAHBaseItem();
	
	virtual void Interact(AActor* Interactor) override;
	
	virtual void StartPrimeAction();
	virtual void EndPrimeAction();
	
	virtual void StartSecondaryAction();
	virtual void EndSecondaryAction();

	virtual void OnEquipped();
	
	//variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Setting")
	FGameplayTag ItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Setting")
	FString ItemName;
	
protected:
	virtual void BeginPlay() override;
	
	AAHPlayerCharacter* GetPlayerOwner() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Compnents")
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Setting")
	int32 MaxStackSize = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Setting")
	int32 CurrentStackSize = 1;

};
