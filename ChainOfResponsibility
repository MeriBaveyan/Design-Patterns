#include <iostream>
#include <memory>
#include <vector>
#include <exception>

class Handler {
public:
    virtual std::unique_ptr<Handler> SetNext(std::unique_ptr<Handler> handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};

class AbstractHandler : public Handler {
private:
    std::unique_ptr<Handler> m_next_handler;

public:
    AbstractHandler() : m_next_handler(nullptr) {
    }
    std::unique_ptr<Handler> SetNext(std::unique_ptr<Handler> handler) override {
        m_next_handler = std::move(handler);
        return handler;
    }
    std::string Handle(std::string request) override {
        if (m_next_handler) {
            return m_next_handler->Handle(request);
        }
        return {};
    }
};

class Meri : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "PCI") {
            return "Meri: I'll review the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};

class Lilit : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "DMAC") {
            return "Lilit: I'll review the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};

class Ani : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "SSI") {
            return "Ani: I'll review the " + request + " IP.\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};

class Elen : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "Ethernet") {
            return "Elen: I'll review the " + request + " IP.\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};

void ClientCode(std::unique_ptr<Handler> handler = std::make_unique<Handler>()) {
    std::vector<std::string> IPs = { "DMAC", "Ethernet", "PCI", "SSI"};
    for (const std::string& ip : IPs) {
        std::cout << "Client: Who can review " << ip << "?\n";
        const std::string result = handler->Handle(ip);
        if (!result.empty()) {
            std::cout << "  " << result;
        }
        else {
            std::cout << "  " << ip << " was left untouched.\n";
        }
    }
}

int main() {

    std::unique_ptr<Meri> ae_1 = std::move(std::unique_ptr<Meri>());
    std::unique_ptr<Lilit> ae_2 = std::make_unique<Lilit>();
    std::unique_ptr<Ani> ae_3 = std::make_unique<Ani>();
    std::unique_ptr<Elen> ae_4 = std::make_unique<Elen>();
    ae_1->SetNext(reinterpret_cast<std::unique_ptr<Handler>>(ae_2))->SetNext(reinterpret_cast<std::unique_ptr<Handler>>(ae_3))->SetNext(reinterpret_cast<std::unique_ptr<Handler>>(ae_4));

    std::cout << "Chain: Meri > Lilit > Ani > Elen\n\n";
    ClientCode(std::unique_ptr<Meri>());
    std::cout << "\n";
    std::cout << "Subchain: Lilit > Ani > Elen\n\n";
    ClientCode(std::unique_ptr<Ani>());
                    
    return 0;
}
