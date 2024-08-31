// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/BSU_VehicleWheelFront.h"

UBSU_VehicleWheelFront::UBSU_VehicleWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;

	WheelRadius = 39.0f;
	WheelWidth = 35.0f;
	FrictionForceMultiplier = 3.0f;

	MaxBrakeTorque = 4500.0f;
	MaxHandBrakeTorque = 6000.0f;
}