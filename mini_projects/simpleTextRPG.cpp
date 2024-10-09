#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class Player {
private:
    std::string name;
    int health;
    int damage;

public:
    Player(const std::string& playerUsername) : name(playerUsername), health(100), damage(10) {}

    void damageDealt() const {
        std::cout << name << " attacked the enemy and dealt: " << damage << " damage.\n";
    }

    void damageTaken(int takenDamage) {
        health -= takenDamage;
        if (health <= 0) {
            std::cout << "You died!\n";
            exit(0);
        } else {
            std::cout << "You took " << takenDamage << " damage. You now have " << health << " health left.\n"; 
        }
    }

    bool isAlive() const {
        return health > 0;
    }

    void heal(int amountHealed) {
        health += amountHealed;
        std::cout << "You healed " << amountHealed << " health. Your total health is now " << health << ".\n";
    }

    int getDamage() const {
        return damage;
    }
};

class Enemy {
private:
    std::string enemyType;
    int health;
    int damage;

public:
    Enemy(const std::string& enemyType) : enemyType(enemyType), health(50), damage(5) {}

    void attack() {
        std::cout << "The " << enemyType << " attacks you and deals " << damage << " damage!\n";
    }

    void takeDamage(int amount) {
        health -= amount;
        if (health <= 0) {
            std::cout << "You defeated the " << enemyType << "!\n";
        } else {
            std::cout << "You dealt " << amount << " damage to the " << enemyType << ". It has " << health << " health left.\n";
        }
    }

    bool isAlive() const {
        return health > 0;
    }

    int getDamage() const {
        return damage;
    }
};

class Room {
private:
    std::string description;
    std::vector<Enemy> enemies;
    std::vector<std::string> items;

public:
    Room(const std::string& roomDesc) : description(roomDesc) {}

    void addEnemy(const Enemy& enemy) {
        enemies.push_back(enemy);
    }

    void addItem(const std::string& item) {
        items.push_back(item);
    }

    void displayDesc() const {
        std::cout << "You are in " << description << ".\n";
        if (!enemies.empty()) {
            std::cout << "There are enemies around...\n";
        }
        if (!items.empty()) {
            std::cout << "You see some items around...\n";
        }
    }

    std::vector<Enemy>& getEnemies() {
        return enemies;
    }

    const std::vector<std::string>& getItems() const {
        return items;
    }
};

void combat(Player& player, std::vector<Enemy>& enemies) {
    for (Enemy& enemy : enemies) {
        while (player.isAlive() && enemy.isAlive()) {
            player.damageDealt();
            enemy.takeDamage(player.getDamage());
            if (enemy.isAlive()) {
                enemy.attack();
                player.damageTaken(enemy.getDamage());
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Player player1("Player1");

    Room room1("a spooky room");
    Room room2("a dark cave");

    room1.addEnemy(Enemy("Goblin"));
    room2.addEnemy(Enemy("Troll"));

    room1.addItem("Healing Potion");
    room2.addItem("Magic Sword");

    room1.displayDesc();
    combat(player1, room1.getEnemies());

    if (player1.isAlive()) {
        std::cout << "\nYou proceed to the next room.\n";
        room2.displayDesc();
        combat(player1, room2.getEnemies());
    }

    std::cout << "* You have completed the game *\n";

    return 0;
}
