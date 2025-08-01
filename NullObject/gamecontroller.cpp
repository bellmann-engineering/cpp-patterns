#include <iostream>

// --- Interface ---
class Controller {
public:
    virtual void movePlayer(int dx, int dy) = 0;
    virtual void jump() = 0;
    virtual ~Controller() = default;
};

// --- Real implementation ---
class GamepadController : public Controller {
public:
    void movePlayer(int dx, int dy) override {
        std::cout << "Moving player with joystick: dx=" << dx << ", dy=" << dy << "\n";
    }

    void jump() override {
        std::cout << "Player jumps (gamepad)\n";
    }
};

// --- Null implementation ---
class NullController : public Controller {
public:
    void movePlayer(int, int) override {
        // Do nothing
    }

    void jump() override {
        // Do nothing
    }
};

// --- Game logic using Controller interface ---
class Game {
    Controller* controller;
public:
    Game(Controller* ctrl) : controller(ctrl) {}

    void onUpdate() {
        controller->movePlayer(1, 0);  // Move right
        controller->jump();
    }
};

int main() {
    bool controllerConnected = false;  // Simulate controller detection

    Controller* input = controllerConnected
        ? static_cast<Controller*>(new GamepadController())
        : static_cast<Controller*>(new NullController());

    Game game(input);
    game.onUpdate();

    delete input;
    return 0;
}
