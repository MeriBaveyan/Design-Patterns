#include <iostream>

class AXI {
public:
    virtual ~AXI() = default;

    virtual std::string Request() const {
        return "AXI: The default AXI's behavior.";
    }
};

class AHB {
public:
    std::string SpecificRequest() const {
        return ".BHA eht fo roivaheb laicepS";
    }
};

class Adapter : public AXI {
private:
    AHB* m_ahb;

public:
    Adapter(AHB* adaptee) : m_ahb(adaptee) {}
    std::string Request() const override {
        std::string to_reverse = m_ahb->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

void ClientCode(const AXI* target) {
    std::cout << target->Request();
}

int main() {
    std::cout << "Client: I can work just fine with the AXI objects:\n";
    AXI* axi = new AXI;
    ClientCode(axi);
    std::cout << "\n\n";
    AHB* ahb = new AHB;
    std::cout << "Client: The AHB class has a weird interface. See, I don't understand it:\n";
    std::cout << "AHB: " << ahb->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter* adapter = new Adapter(ahb);
    ClientCode(adapter);
    std::cout << "\n";

    delete axi;
    delete ahb;
    delete adapter;
}
