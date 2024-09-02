// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArmComp;

		UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComp;


	UPROPERTY(EditDefaultsOnly, Category = "ch")
	class UInputMappingContext* imc_Base;
		UPROPERTY(EditDefaultsOnly, Category = "ch")
	class UInputAction* ia_Move;

		UPROPERTY(EditDefaultsOnly, Category = "ch")
	class UInputAction* ia_Look;

		UPROPERTY(EditDefaultsOnly, Category = "ch")
	class UInputAction* ia_Jump;


	FVector Direction;


	void OnMyActionMove(const struct FInputActionValue& inputValue);

	void OnMyActionLook(const struct FInputActionValue& inputValue);

	void OnMyActionJump(const struct FInputActionValue& inputValue);






};
