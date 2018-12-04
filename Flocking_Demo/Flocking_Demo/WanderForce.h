/************************************************************************************************************************/
/* Title: Steering Behaviour - Wander																									*/
/* Author: Ramkumar Thiyagarajan																						*/
/* Date: 4/12/2018																										*/	
/* Summary: Wander steering behaviour aims to produce a realistic casual movement										*/	
/* Reference : https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624		*/
/************************************************************************************************************************/


#pragma once
#include "SteeringForce.h"
class WanderForce : public SteeringForce {
public:
	WanderForce();
	~WanderForce();

	void SetRadius(float radius) { m_wanderRadius = radius; }

	void SetDistance(float distance) { m_wanderDistance = distance; }

	void SetWanderAngle(float angle) { m_wanderAngle = angle; }

	virtual Vector3 getForce(Agent* agent);

private:
	float m_wanderRadius;
	float m_wanderDistance;
	float m_wanderAngle;
};

