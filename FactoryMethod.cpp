#include <iostream>

class PlayMusic
{
public:
	virtual ~PlayMusic() {}
	virtual void Play() = 0;
};

class PlayPiano : public PlayMusic
{
public:
	void Play() override {
		std::cout << "You can listen to music with piano melody.\n";
	}
};

class PlayViolin : public PlayMusic
{
public:
	void Play() override {
		std::cout << "You can listen to music with violin melody.\n";
	}
};

class Composer
{
public:
	virtual ~Composer() {}
	virtual PlayMusic* FactoryMethod() = 0;

	void SomeOperation() {
		PlayMusic* music = FactoryMethod();
		std::cout << "I'm composer.";
		music->Play();
		delete music;
	}
};

class ComposterPiano : public Composer
{
	PlayMusic* FactoryMethod() override {
		return new PlayPiano();
	}
};

class ComposterViolin : public Composer
{
	PlayMusic* FactoryMethod() override {
		return new PlayViolin();
	}
};

int main()
{
	Composer* composer_1 = new ComposterPiano();
	composer_1->SomeOperation();
	std::cout << std::endl;
	Composer* composer_2 = new ComposterViolin();
	composer_2->SomeOperation();

	delete composer_1;
	delete composer_2;
}
