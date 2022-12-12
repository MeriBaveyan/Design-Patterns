#include <iostream>
#include <list>
#include <memory>

class JiraTickets;
class User;

class JiraTickets //Subject
{
public:
	JiraTickets(std::string notification = "Nothing has changed!\n")
	{
		m_notification = notification;
	}

	void AddToWatchList(std::shared_ptr<User> pUser)
	{
		m_pUsers.push_back(pUser);
	}

	void RemoveFromWatchList(std::shared_ptr<User> pUser)
	{
		m_pUsers.remove(pUser);
	}

	void Notify()
	{
		std::list<std::shared_ptr<User>>::iterator iterator = m_pUsers.begin();
		while (iterator != m_pUsers.end())
		{
			(*iterator)->Update(m_notification);
			++iterator;
		}
	}

	void AddComment(std::string comment = "Nothing has changed!\n")
	{
		m_notification = comment;
		Notify();
	}

	void UsersCount()
	{
		std::cout << "This ticket watched " << m_pUsers.size() << " users.\n";
	}

	void ChangeInTicket(std::string notification)
	{
		m_notification = "Update will come.\n";
		Notify();
		std::cout << "Changed ticket state.\n";
	}

private:
	std::list<std::shared_ptr<User>> m_pUsers;
	std::string m_notification;
};

class User
{
public:
	User(std::unique_ptr<JiraTickets> pTicket)
	{
		m_pTicket->AddToWatchList(std::make_shared<User>(this));
	};

	void RemoveFromWatchList()
	{
		m_pTicket->RemoveFromWatchList(std::make_shared<User>(this));
	}

	void Update(std::string updateFromJira)
	{
		m_updateFromJira = updateFromJira;
		std::cout << "Update: " << m_updateFromJira << "\n";
	}

private:
	std::shared_ptr<JiraTickets> m_pTicket;
	std::string m_updateFromJira;
};


int main()
{
	std::unique_ptr<JiraTickets> pTicket;
	User user_1(std::move(pTicket));	
}
