#include "Subsystem/EventSubsystem.h"
#include "Kismet/GameplayStatics.h"


UEventSubsystem* UEventSubsystem::Get(const UObject* WorldContext)
{
	if (WorldContext == nullptr) return nullptr;
	
	UGameInstance* GI = UGameplayStatics::GetGameInstance(WorldContext);
	if (GI)
	{
		return GI->GetSubsystem<UEventSubsystem>();
	}
	return nullptr;
}
