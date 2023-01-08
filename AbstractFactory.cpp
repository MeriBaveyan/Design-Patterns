#include <iostream>

class AbstractTea {
public:
    virtual ~AbstractTea() {};
    virtual std::string UsefulFunctionTea() const = 0;
};

class ConcreteTeaHot : public AbstractTea {
public:
    std::string UsefulFunctionTea() const override {
        return "The result of the hot tea.";
    }
};

class ConcreteTeaCold : public AbstractTea {
    std::string UsefulFunctionTea() const override {
        return "The result of the cold tea.";
    }
};

class AbstractCoffee {
public:
    virtual ~AbstractCoffee() {};
    virtual std::string UsefulFunctionCoffee() const = 0;
    virtual std::string AnotherUsefulFunctionCoffee(const AbstractTea& collaborator) const = 0;
};

class ConcreteCoffeeHot : public AbstractCoffee {
public:
    std::string UsefulFunctionCoffee() const override {
        return "The result of the hot coffee.";
    }
    std::string AnotherUsefulFunctionCoffee(const AbstractTea& collaborator) const override {
        const std::string result = collaborator.UsefulFunctionTea();
        return "The result of the hot coffee collaborating with ( " + result + " )";
    }
};

class ConcreteCoffeeCold : public AbstractCoffee {
public:
    std::string UsefulFunctionCoffee() const override {
        return "The result of the product cold coffee.";
    }
    std::string AnotherUsefulFunctionCoffee(const AbstractTea & collaborator) const override {
        const std::string result = collaborator.UsefulFunctionTea();
        return "The result of the cold coffee collaborating with ( " + result + " )";
    }
};

class AbstractFactory {
public:
    virtual AbstractTea* CreateTea() const = 0;
    virtual AbstractCoffee* CreateCoffee() const = 0;
};

class ConcreteFactoryHot : public AbstractFactory {
public:
    AbstractTea* CreateTea() const override {
        return new ConcreteTeaHot();
    }
    AbstractCoffee* CreateCoffee() const override {
        return new ConcreteCoffeeHot();
    }
};

class ConcreteFactoryCold : public AbstractFactory {
public:
    AbstractTea* CreateTea() const override {
        return new ConcreteTeaCold();
    }
    AbstractCoffee* CreateCoffee() const override {
        return new ConcreteCoffeeCold();
    }
};

void ClientCode(const AbstractFactory& factory) {
    const AbstractTea* product_a = factory.CreateTea();
    const AbstractCoffee* product_b = factory.CreateCoffee();
    std::cout << product_b->UsefulFunctionCoffee() << "\n";
    std::cout << product_b->AnotherUsefulFunctionCoffee(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactoryHot* f1 = new ConcreteFactoryHot();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactoryCold* f2 = new ConcreteFactoryCold();
    ClientCode(*f2);
    delete f2;
}
