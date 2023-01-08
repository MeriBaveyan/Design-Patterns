#include <iostream>

class MakeCake
{
public:

	virtual void cookCakeSlices() {
		std::cout << "Added a slice.\n";
	}

	virtual void coverCakeWithCream() {
		std::cout << "Added cream.\n";
	}
	virtual void addNuts() {
		std::cout << "Added nuts.\n";
	}

	virtual void addBerries() {
		std::cout << "Added berries.\n";
	}
};

class MakeOrdinaryCake : public MakeCake
{
public:
	MakeOrdinaryCake() {
		MakeCake();
	}

	void MakeCake() {
		std::cout << "\nYou have ordered ordinary cake:\n";
		cookCakeSlices();
		coverCakeWithCream();
		cookCakeSlices();
		coverCakeWithCream();
	}
};

class MakeLuxuryCake : public MakeCake
{
public:
	MakeLuxuryCake() {
		MakeCake();
	}

	void MakeCake() {
		std::cout << "\nYou have ordered luxury cake:\n";
		cookCakeSlices();
		coverCakeWithCream();
		addNuts();
		cookCakeSlices();
		coverCakeWithCream();
		addBerries();
		cookCakeSlices();
		coverCakeWithCream();
		addNuts();
		addBerries();
	}
};

class MakeMyOwnCake : public MakeCake
{
public:
	MakeMyOwnCake() {
		std::cout << "\nYour cake receipt:\n";
	}
};

int main()
{
	MakeOrdinaryCake* orindaryCake = new MakeOrdinaryCake();
	MakeLuxuryCake* luxuryCake = new MakeLuxuryCake();
	MakeMyOwnCake* myCake = new MakeMyOwnCake();
	myCake->cookCakeSlices();
	myCake->coverCakeWithCream();
	myCake->addNuts();
	myCake->cookCakeSlices();
	myCake->coverCakeWithCream();
	myCake->addBerries();
}
