// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

  public:
	// Sets default values for this character's properties
	ASTUBaseCharacter();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent *SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent *CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Movement")
	float MaxRunSpeed;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Custom Movement")
	float DefaultSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Movement")
	float ImpulseMultiplier;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Movement")
	bool IsWantToRun;

	bool IsMovingForward;
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


  private:
	void MoveForward(float Input);
	void MoveRight(float Input);
	void StartRun();
	void StopRun();
	
};
