// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BESCIENCEUNREAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	public: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* CameraComp;


	UPROPERTY(EditDefaultsOnly, Category = "ch")
	class UInputMappingContext* imc_Base;
		UPROPERTY(EditDefaultsOnly, Category = "ch")
	class UInputAction* ia_Move;

		UPROPERTY(EditDefaultsOnly, Category = "ch")
	class UInputAction* ia_Look;
		
		UPROPERTY(EditDefaultsOnly, Category = "ch")
	class UInputAction* ia_Jump;

		UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Dash;


		UPROPERTY(EditDefaultsOnly, Category = "ch")
	class UInputAction* ia_Function;


	FVector Direction;


	void OnMyActionMove(const FInputActionValue& inputValue);

	void OnMyActionLook(const FInputActionValue& inputValue);

	void OnMyActionJump(const FInputActionValue& inputValue);
	void OnMyActionFunction(const FInputActionValue& inputValue);

	void OnMyActionDashOngoing(const FInputActionValue& Value);
	void OnMyActionDashCompleted(const FInputActionValue& Value);


	UFUNCTION(BlueprintCallable)
	void CameraMoveMent();

	UFUNCTION(BlueprintCallable)
	void MoveCamera();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DashSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float WalkSpeed = 500.0f;




	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_HiddenState)
    bool bIsHidden;
	
	UFUNCTION()
    void OnRep_HiddenState();

	    // 서버에서 숨김 상태를 설정하는 함수
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSetHidden(bool bPlayerHidden);

	void SetHidden(bool bPlayerHidden);

	// 서버에서 숨김 상태를 설정하는 함수
	UFUNCTION(Server, Reliable)
	void ServerRideVehicle(ABSU_VehiclePawn* pawn);
	void RideVehicle(ABSU_VehiclePawn* pawn);

	void PrintNetLog();
};
