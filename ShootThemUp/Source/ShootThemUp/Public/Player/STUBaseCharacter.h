// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class UAnimationMontage;
class USTUWeaponComponent;
UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

  public:
	// Sets default values for this character's properties
	ASTUBaseCharacter();
	UPROPERTY(EditAnywhere)
	USTUHealthComponent *HealthComponent;
  protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent *SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent *CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Movement")
	float MaxRunSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom Movement")
	float DefaultSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Movement")
	float ImpulseMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Movement")
	bool IsWantToRun;

	bool IsMovingForward;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	UTextRenderComponent *TextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage *DeathAnimationMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	USTUWeaponComponent* WeaponComponent;
	

  public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	bool IsRunning();

	// Return angle between ForwardVector and VelocityVector
	UFUNCTION(BlueprintCallable)
	float GetMovementDirection() const;

	USTUHealthComponent *GetHealthComponent(){return HealthComponent;}

  private:
	void MoveForward(float Input);
	void MoveRight(float Input);
	void StartRun();
	void StopRun();
	void OnDeath();
	void OnHealthChanged(float health);
};
