#include <iostream>
#include <memory>
#include <stack>

#define valid true
#define nonValid false

class Arbiter;
class Slave;
class Master;

class Slave //reciver
{
public:
	Slave(std::string command = "I do nothing. I am free!\n") : m_command(command) {};

	void Execute(std::string command = "No command has passed.\n") {
		std::cout << "Slave: I got command from master.\n Master->Slave: " << m_command << "\nNow I am executing it.\n";
	}

private:
	std::string m_command;
};

class Master //command
{
public:
	Master(std::unique_ptr<Arbiter> arbiter = std::make_unique<Arbiter>(), std::string command = "", bool state = valid) {//, int priority = 2) {
		m_arbiter = std::move(arbiter);
		m_command = command;
		//m_priority = priority;
		m_state = state;
	}

	void SendCommandToSlave() {
		std::cout << "Master: I send command to arbitor for prioritizing and sending to slave.\n";
		//m_arbitor->Proritizing();
		//m_arbiter->SomeLogic();
		m_arbiter->SomeLogic();
	}

	std::string GetCommand() const {
		return m_command;
	}

	/*int GetPrority() const {
		return m_priority;
	}*/

	bool GetState() const {
		return m_state;
	}

private:
	std::unique_ptr<Arbiter> m_arbiter;
	//std::unique_ptr<Slave> m_slave;
	std::string m_command;
	//int m_priority;
	bool m_state;
};

class Arbiter //invoker
{
public:
	Arbiter(std::unique_ptr<Master> master) : m_master(std::move(master)) {};

	/*void Proritizing() {
		if (m_master->GetState()) {
			if (!m_stack.empty()) {
				if (m_stack.top()->GetPrority() < m_master->GetPrority() || !(m_stack.top()->GetState())) {
					SendToSlave(m_master->GetCommand());
				}
				else if (m_stack.top()->GetState()) {
					SendToSlave(m_stack.top()->GetCommand());
					m_stack.pop();
					m_stack.push(m_master);
				}
			}
			else if (m_master->GetState()) {
				SendToSlave(m_master->GetCommand());
			}
		}
		else {
			m_stack.push(m_master);
		}
	}*/

	void SomeLogic() {
		SendToSlave(m_master->GetCommand());
	}

	void SendToSlave(std::string command) {
		m_slave->Execute(command);
	}

private:
	std::unique_ptr<Slave> m_slave;
	std::unique_ptr<Master> m_master;
	std::stack<std::unique_ptr<Master>> m_stack;
};

int main()
{
	//Master master_1(std::unique_ptr<Slave>(), "I am valid!\n", 1, valid);
	//Master master_2(std::unique_ptr<Slave>(), "Command_1!\n", 1, nonValid);
	//Master master_3(std::unique_ptr<Slave>(), "Command_2!\n", 2, valid);
}
