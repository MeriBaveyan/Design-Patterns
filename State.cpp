#include <iostream>

class TrafficLight;
class State;
class ConcreteStateA;
class ConcreteStateB;

class State {
protected:
    TrafficLight* m_trafficLight;

public:
    virtual ~State() {
    }

    void SetTrafficLight(TrafficLight* trafficLight) {
        this->m_trafficLight = trafficLight;
    }

    virtual void Green() = 0;
    virtual void Red() = 0;
    virtual void Yellow() = 0;
};

class TrafficLight {
private:
    State* m_state;

public:
    TrafficLight(State* state) : m_state(nullptr) {
        TransitionTo(state);
    }

    ~TrafficLight() {
        delete m_state;
    }

    void TransitionTo(State* state) {
        std::cout << "Traffic light: Transition to " << typeid(*state).name() << ".\n";
        if (m_state != nullptr)
            delete m_state;
        m_state = state;
        m_state->SetTrafficLight(this);
    }

    void Pedestrians() {
        m_state->Green();
    }

    void Cars() {
        m_state->Red();
    }
};

class ConcreteStateA : public State {
public:
    void Green() override {
        std::cout << "ConcreteStateA handles green.\n";
        std::cout << "ConcreteStateA wants to change the state of the traffic light.\n";

        m_trafficLight->TransitionTo(new ConcreteStateA);
    }

    void Yellow() override {
        std::cout << "ConcreteStateA handles yellow";////////
    }

    void Red() override {
        std::cout << "ConcreteStateA handles red.\n";///////////
    }
};

class ConcreteStateB : public State {
public:
    void Red() override {
        std::cout << "ConcreteStateB handles red.\n";
        std::cout << "ConcreteStateB wants to change the state of the traffic light.\n";
        m_trafficLight->TransitionTo(new ConcreteStateA);
    }

    void Yellow() override {
        std::cout << "ConcreteStateB handles yellow";////////
    }

    void Green() override {
        std::cout << "ConcreteStateB handles green.\n";////////
    }
};

void ClientCode() {
    TrafficLight* trafficLight = new TrafficLight(new ConcreteStateA);
    trafficLight->Pedestrians();
    trafficLight->Cars();
    delete trafficLight;
}

int main() {
    ClientCode();
    return 0;
}
