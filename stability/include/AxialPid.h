#pragma once

#ifndef AXIALPID_H
#define AXIALPID_H
#include "MiniPID.h"

class RotPIDController {
private:
	//pid control objects
	MiniPID rollControl;
	MiniPID pitchControl;
	MiniPID yawControl;

	//pid tuning (kp, ki, kd)
	float rollKp, rollKi, rollKd;
	float pitchKp, pitchKi, pitchKd;
	float yawKp, yawKi, yawKd;

	//pid output limits
	int OUT_LIMIT;

	//pid target closeness constant
	int MARGIN;

	//pid targets
	float rollTarget;
	float pitchTarget;
	float yawTarget;

	//latest sensor input
	float rollVal;
	float pitchVal;
	float yawVal;

	//pid reverses (just in case something is messed up)
	bool rollFlip;
	bool pitchFlip;
	bool yawFlip;

public:
	//constructors
	RotPIDController(float newRKp, float newRKi, float newRKd, float newPKp, float newPKi, float newPKd, float newYKp, float newYKi, float newYKd, float rTarget, float pTarget, float yTarget);
		
	RotPIDController(float newRKp, float newRKi, float newRKd, float newPKp, float newPKi, float newPKd, float newYKp, float newYKi, float newYKd);

	RotPIDController();

	//LOOP FUNCTIONS (TO BE CALLED IN A LOOP THING)

	//returns all pid outputs in a vector in this order (roll, pitch, yaw)
	void getMotorValues(float rollValue, float pitchValue, float yawValue, float& rollOut, float& pitchOut, float& yawOut);

	//runs pid without returning values
	void runPID(float, float, float);

	//returns just roll pid output
	float getRollValue(float rollValue);

	//returns just pitch pid output
	float getPitchValue(float pitchValue);

	//returns just yaw pid output
	float getYawValue(float yawValue);

	//returns whether the current roll position is at the target (within a certain margin)
	bool atRollTarget(float rollValue);

	//returns whether the current pitch position is at the target (within a certain margin)
	bool atPitchTarget(float pitchValue);

	//returns whether the current yaw position is at the target (within a certain margin)
	bool atYawTarget(float yawValue);

	//returns whether the current rotation is at the target (within a certain margin)
	bool atTarget(float rollValue, float pitchValue, float yawValue);

	//SPECIALTY FUNCTIONS (called not in a loop)

	//flips pid control (for if the robot is moving away from target instead of towards it)
	void flipRoll();

	void flipPitch();

	void flipYaw();

	//set pid tunings
	void setRollPID(float kp, float ki, float kd);
	void setPitchPID(float kp, float ki, float kd);
	void setYawPID(float kp, float ki, float kd);

	//set pid target values
	void setRollTarget(float newTarget);

	void setPitchTarget(float newTarget);

	void setYawTarget(float newTarget);

	void startRosLoop(int, char**);

	void setTargets(std_msgs::Float64, std_msgs::Float64, std_msgs::Float64);

	void setInputs(sensor_msgs::Imu);
};

#endif