#include <algorithm>
#include <iostream>
#include <list>
#include <string>

class Component {
protected:
    Component* m_clkTime;
public:
    virtual ~Component() {}
    void SetClkTime(Component* clkTime) {
        this->m_clkTime = clkTime;
    }
    Component* GetClkTime() const {
        return this->m_clkTime;
    }
    virtual void Add(Component* component) {}
    virtual void Remove(Component* component) {}
    virtual bool IsComposite() const {
        return false;
    }
    virtual std::string Operation() const = 0;
};

class LogicElement : public Component {
public:
    std::string Operation() const override {
        return "Logic element";
    }
};

class Composite : public Component {
protected:
    std::list<Component*> m_elements;

public:
    void Add(Component* component) override {
        this->m_elements.push_back(component);
        component->SetClkTime(this);
    }
    void Remove(Component* component) override {
        m_elements.remove(component);
        component->SetClkTime(nullptr);
    }
    bool IsComposite() const override {
        return true;
    }
    std::string Operation() const override {
        std::string result;
        for (const Component* c : m_elements) {
            if (c == m_elements.back()) {
                result += c->Operation();
            }
            else {
                result += c->Operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
};
void ClientCode(Component* component) {
    std::cout << "RESULT: " << component->Operation();
}

void ClientCode2(Component* component1, Component* component2) {
    if (component1->IsComposite()) {
        component1->Add(component2);
    }
    std::cout << "RESULT: " << component1->Operation();
}

int main() {
    Component* simple = new LogicElement;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";
    Component* clkTime = new Composite;
    Component* branch1 = new Composite;

    Component* elem_1 = new LogicElement;
    Component* elem_2 = new LogicElement;
    Component* elem_3 = new LogicElement;
    branch1->Add(elem_1);
    branch1->Add(elem_2);
    Component* branch2 = new Composite;
    branch2->Add(elem_3);
    clkTime->Add(branch1);
    clkTime->Add(branch2);
    std::cout << "Client: Now I've got a composite tree:\n";
    ClientCode(clkTime);
    std::cout << "\n\n";

    std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode2(clkTime, simple);
    std::cout << "\n";

    delete simple;
    delete clkTime;
    delete branch1;
    delete branch2;
    delete elem_1;
    delete elem_2;
    delete elem_3;
}
