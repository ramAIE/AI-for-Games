#pragma once
#include "SteeringForce.h"
namespace aie {
	class Input;
}
class SeekForce : public SteeringForce {
public:
	SeekForce();
	~SeekForce();

	void setTarget(aie::Input* input, Vector3 target){
		m_input = input;
		m_target = target;
	}

	virtual Vector3 getForce(Agent* agent);

private:
	aie::Input* m_input;
	Vector3 m_target;
};

