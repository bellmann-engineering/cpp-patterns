#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

enum class Event {
    OnOffPressed,
    PlayPausePressed
};

class MusicPlayer;

// Abstract State class
class State {
public:
    virtual ~State() = default;
    virtual void entry() = 0;
    virtual void exit() = 0;
    virtual void handle(Event event, MusicPlayer& player) = 0;
};

// Forward declarations of concrete states
class Inactive;
class On;
class Playing;
class Paused;

// Context class
class MusicPlayer {
public:
    MusicPlayer() : state(std::make_unique<Inactive>(*this)), led_on(false) {
        state->entry();
    }

    void setState(std::unique_ptr<State> new_state) {
        state->exit();
        state = std::move(new_state);
        state->entry();
    }

    void turnLedOn() {
        led_on = true;
        std::cout << "🌕 LED on\n";
    }

    void turnLedOff() {
        led_on = false;
        std::cout << "🌑 LED off\n";
    }

    void playMusic() {
        std::cout << "🔊 Music playing\n";
    }

    void pauseMusic() {
        std::cout << "🔇 Music paused\n";
    }

    void handle(Event event) {
        state->handle(event, *this);
    }

private:
    std::unique_ptr<State> state;
    bool led_on;
};

// Concrete State: Inactive
class Inactive : public State {
public:
    explicit Inactive(MusicPlayer& player) : player(player) {}

    void entry() override {
        std::cout << "Entering 'inactive' state\n";
        player.turnLedOff();
    }

    void exit() override {
        std::cout << "Exiting 'inactive' state\n";
    }

    void handle(Event event, MusicPlayer& player) override {
        if (event == Event::OnOffPressed) {
            std::cout << "OnOffPressed event in 'inactive' state\n";
            player.setState(std::make_unique<On>(player));
        }
    }

private:
    MusicPlayer& player;
};

// Concrete State: On
class On : public State {
public:
    explicit On(MusicPlayer& player) : player(player) {}

    void entry() override {
        std::cout << "Entering 'on' state\n";
        player.turnLedOn();
    }

    void exit() override {
        std::cout << "Exiting 'on' state\n";
    }

    void handle(Event event, MusicPlayer& player) override {
        if (event == Event::PlayPausePressed) {
            player.setState(std::make_unique<Playing>(player));
        } else if (event == Event::OnOffPressed) {
            player.setState(std::make_unique<Inactive>(player));
        }
    }

private:
    MusicPlayer& player;
};

// Concrete State: Playing
class Playing : public State {
public:
    explicit Playing(MusicPlayer& player) : player(player) {}

    void entry() override {
        std::cout << "Entering 'playing' state\n";
        player.playMusic();
    }

    void exit() override {
        std::cout << "Exiting 'playing' state\n";
    }

    void handle(Event event, MusicPlayer& player) override {
        if (event == Event::PlayPausePressed) {
            player.setState(std::make_unique<Paused>(player));
        }
    }

private:
    MusicPlayer& player;
};

// Concrete State: Paused
class Paused : public State {
public:
    explicit Paused(MusicPlayer& player) : player(player) {}

    void entry() override {
        std::cout << "Entering 'paused' state\n";
        player.pauseMusic();
    }

    void exit() override {
        std::cout << "Exiting 'paused' state\n";
    }

    void handle(Event event, MusicPlayer& player) override {
        if (event == Event::PlayPausePressed) {
            player.setState(std::make_unique<Playing>(player));
        } else if (event == Event::OnOffPressed) {
            player.setState(std::make_unique<Inactive>(player));
        }
    }

private:
    MusicPlayer& player;
};

// Main function
int main() {
    MusicPlayer player;

    std::unordered_map<int, Event> menu = {
        {1, Event::OnOffPressed},
        {2, Event::PlayPausePressed}
    };

    while (true) {
        std::cout << "Press a button:\n";
        std::cout << "1. On / Off\n";
        std::cout << "2. Play / Pause\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        if (menu.find(choice) != menu.end()) {
            player.handle(menu[choice]);
        } else {
            std::cout << "Invalid choice.\n";
        }

        std::cout << "\n";
    }

    return 0;
}
