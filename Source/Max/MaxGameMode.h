// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MaxGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API AMaxGameMode : public AGameMode
{
	GENERATED_BODY()

		virtual void BeginPlay() override;

public:
	AMaxGameMode();

	//HS = hud state
	enum EHUDState : uint8
	{
		HS_Ingame,
		HS_Item_Inven,
		HS_Spell_Inven	
	};

	/*checks hudstate and then calls applied to apply
	  w.e hud were using*/
	void ApplyHUDChanges();

	//get hud state
	uint8 GetHUDState();

	//setter for hud state, applies new state and calls applyhudchanges
	UFUNCTION(BlueprintCallable, Category = "HUD Functions")
		void ChangeHUDState(uint8 NewState);

	//applies hud to screen, returns true if successful
	bool ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents);


protected:

	//current hudstate
	//0 = HS Ingame, 1 = HS Item Inven, 2 = Spell Inven etc etc
	uint8 HUDState;

	//HUD to be shown in game, inventories
	//meta =  extending to blueprint, by default it doesnt know its protected
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprint Widgets", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> IngameHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprint Widgets", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> ItemInvenHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprint Widgets", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> SpellInvenHUDClass;

	//current hud being displayed

	class UUserWidget* CurrentWidget;


};
