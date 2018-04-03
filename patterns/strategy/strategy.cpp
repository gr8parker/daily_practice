#include <iostream>
#include <memory>

class WeaponBehavior
{
public:
    virtual void use() = 0;
};

class AxeBehavior : public WeaponBehavior
{
public:
    void use() override
    {
        std::cout << "Axe" << std::endl;
    }
};

class SwordBehavior : public WeaponBehavior
{
public:
    void use() override
    {
        std::cout << "Sword" << std::endl;
    }
};

class Character
{
public:
    Character(WeaponBehavior* weaponBehavior)
        : m_weaponBehavior(weaponBehavior)
    {}
    virtual ~Character() = default;
    virtual void useWeapon()
    {
        m_weaponBehavior->use();
    }
    
    void setWeapon(WeaponBehavior* weaponBehavior)
    {
        m_weaponBehavior = std::move(std::unique_ptr<WeaponBehavior>(weaponBehavior));
    }
    
private:
    std::unique_ptr<WeaponBehavior> m_weaponBehavior;
};

class King : public Character
{
public:
    King()
        : Character(new SwordBehavior())
    {}
};

class Barbar : public Character
{
public:
    Barbar()
        : Character(new AxeBehavior())
    {}
};

int main()
{
    std::shared_ptr<Character> character(new King());
    character->setWeapon(new AxeBehavior());
    character->useWeapon();
}
