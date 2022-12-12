#include <iostream>
#include <memory>
#include <string>

class Optometrist {
public:
	Optometrist(bool eyeState = true) {
		m_eyeState = eyeState;
	}

	std::string ExamineEye() {
		return (m_eyeState ? "Your eye is normal\n" : "You need to operate your eye.\n");
	}

	void EyeOperation() {
		m_eyeState = true;
	}

private:
	bool m_eyeState;
};

class Neurologist {
public:
	Neurologist(int nerousState = 25) {
		m_nervousState = nerousState;
	}

	std::string ExamineNervousState() {
		return (m_nervousState < 26 ? "Your nerous state is normal\n" : "You need to take medication.\n");
	}

	std::string Medication() {
		if (m_nervousState > 50) {
			return "Use X medication.\n";
		}
		else if (m_nervousState > 25) {
			return "Use Y medication.\n";
		}
		else {
			return "Your nerous state is normal\n";
		}
	}

private:
	int m_nervousState;
};

class Cardiologist {
public:
	Cardiologist(bool hurtState = true) {
		m_hurtState = hurtState;
	}

	std::string ExamineHurt() {
		return (m_hurtState ? "Your hurt is normal\n" : "You need to operate your hurt.\n");
	}

	void HurtOperation() {
		m_hurtState = true;
	}

private:
	bool m_hurtState;
};

class Therapist {
public:
	Therapist(const bool eyeState = 1, const int nervousState = 25, const bool hurtState = 1) {
		m_pOptometrist = std::make_unique<Optometrist>(eyeState);
		m_pNeurologist = std::make_unique<Neurologist>(nervousState);
		m_pCardiologist = std::make_unique<Cardiologist>(hurtState);
	}

	void AnnualMedicalExamination() {
		std::cout << "Therapist's epicrisis\n";
		std::cout << m_pOptometrist->ExamineEye();
		std::cout << m_pNeurologist->ExamineNervousState();
		std::cout << m_pCardiologist->ExamineHurt();
		std::cout << std::endl;
	}

private:
	std::unique_ptr<Optometrist> m_pOptometrist;
	std::unique_ptr<Neurologist> m_pNeurologist;
	std::unique_ptr<Cardiologist> m_pCardiologist;
};

class Client {
public:
	Client(const bool eyeState = 1, const int nervousState = 25, const bool hurtState = 1) {
		m_pTherapist = std::make_unique<Therapist>(eyeState, nervousState, hurtState);
	}

	void GetPatienState() {
		return m_pTherapist->AnnualMedicalExamination();
	}

private:
	std::unique_ptr<Therapist> m_pTherapist;
};

int main()
{
	//Client client(1, 50, 0);
	//Client client;
	Client client(0);
	client.GetPatienState();
}
