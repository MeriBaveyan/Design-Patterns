#include <iostream>
#include <array>

class ConcreteSchool;
class ConcreteUniversity;

class Visitor {
public:
    virtual void VisitConcreteSchool(const ConcreteSchool* element) const = 0;
    virtual void VisitConcreteUniversity(const ConcreteUniversity* element) const = 0;
};

class Component {
public:
    virtual ~Component() {}
    virtual void Accept(Visitor* visitor) const = 0;
};

class ConcreteSchool : public Component {
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteSchool(this);
    }
    std::string ExclusiveMethodOfConcreteSchool() const {
        return "School";
    }
};

class ConcreteUniversity : public Component {
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteUniversity(this);
    }
    std::string SpecialMethodOfConcreteUniversity() const {
        return "University";
    }
};
class ConcreteVisitor1 : public Visitor {
public:
    void VisitConcreteSchool(const ConcreteSchool* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteSchool() << " + ConcreteVisitor1\n";
    }

    void VisitConcreteUniversity(const ConcreteUniversity* element) const override {
        std::cout << element->SpecialMethodOfConcreteUniversity() << " + ConcreteVisitor1\n";
    }
};

class ConcreteVisitor2 : public Visitor {
public:
    void VisitConcreteSchool(const ConcreteSchool* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteSchool() << " + ConcreteVisitor2\n";
    }
    void VisitConcreteUniversity(const ConcreteUniversity* element) const override {
        std::cout << element->SpecialMethodOfConcreteUniversity() << " + ConcreteVisitor2\n";
    }
};
void ClientCode(std::array<const Component*, 2> components, Visitor* visitor) {
    for (const Component* comp : components) {
        comp->Accept(visitor);
    }
}

int main() {
    std::array<const Component*, 2> components = { new ConcreteSchool, new ConcreteUniversity };
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    ConcreteVisitor1* visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    ConcreteVisitor2* visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component* comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;

    return 0;
}
