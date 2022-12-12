#include <iostream>
#include <memory>
//#include <string>

class RequestProjectIP;
class Proxy;

class IRequestIP
{
	virtual void RequestIP() const = 0;
};

class RequestProjectIP : public IRequestIP
{
public:

	RequestProjectIP(std::string ID = "us01abc") : m_projectID(ID) {};

	std::string GetProjectID() const
	{
		return m_projectID;
	}

	void RequestIP() const override {
		std::cout << "Request from original IP.\n";
	}

private:
	std::string m_projectID;
};

class Proxy : public IRequestIP
{
public:
	Proxy(std::unique_ptr<RequestProjectIP> pRequestIP = std::make_unique<RequestProjectIP>())
	{
		m_pRequestIP = std::move(pRequestIP);
	}

	void RequestIP() const override {
		std::cout << "Request from Proxy.\n";
	}

private:
	std::unique_ptr<RequestProjectIP> m_pRequestIP;

	bool CheckProjectID(const std::string projectID)
	{
		if (!(projectID.compare(m_pRequestIP->GetProjectID())))
		{
			RequestIP();
		}
	}
};

int main()
{
	std::unique_ptr<RequestProjectIP> pRequestIP_real = std::make_unique<RequestProjectIP>();
	std::unique_ptr<Proxy> pRequestIP_proxy = std::make_unique<Proxy>(std::unique_ptr<RequestProjectIP>());
	pRequestIP_real->RequestIP();
	pRequestIP_proxy->RequestIP();
}
