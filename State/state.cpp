#include <iostream>
#include <unordered_map>

// Events for state transitions
enum class Event {
    OnOffPressed,
    PlayPausePressed
};

// Abstract State class
class State {
public:
    virtual ~State() = default;

    virtual void entry() = 0;
    virtual void exit() = 0;
    virtual void handle(Event event, class MusicPlayer& player) = 0;
};

// Context class (MusicPlayer)
class MusicPlayer {
public:
    MusicPlayer();

    ~MusicPlayer();

    void setState(State* new_state);

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

    void handle(Event event);

private:
    State* state;  // Raw pointer to the current state
    bool led_on;
};

// Concrete State: Inactive
class Inactive : public State {
public:
    Inactive(MusicPlayer& player) : player(player) {}

    void entry() override {
        std::cout << "Entering 'inactive' state\n";
        player.turnLedOff();
    }

    void exit() override {
        std::cout << "Exiting 'inactive' state\n";
    }

    void handle(Event event, MusicPlayer& player) override;

private:
    MusicPlayer& player;
};

// Concrete State: On
class On : public State {
public:
    On(MusicPlayer& player) : player(player) {}

    void entry() override {
        std::cout << "Entering 'on' state\n";
        player.turnLedOn();
    }

    void exit() override {
        std::cout << "Exiting 'on' state\n";
    }

    void handle(Event event, MusicPlayer& player) override;

private:
    MusicPlayer& player;
};

// Concrete State: Playing
class Playing : public State {
public:
    Playing(MusicPlayer& player) : player(player) {}

    void entry() override {
        std::cout << "Entering 'playing' state\n";
        player.playMusic();
    }

    void exit() override {
        std::cout << "Exiting 'playing' state\n";
    }

    void handle(Event event, MusicPlayer& player) override;

private:
    MusicPlayer& player;
};

// Concrete State: Paused
class Paused : public State {
public:
    Paused(MusicPlayer& player) : player(player) {}

    void entry() override {
        std::cout << "Entering 'paused' state\n";
        player.pauseMusic();
    }

    void exit() override {
        std::cout << "Exiting 'paused' state\n";
    }

    void handle(Event event, MusicPlayer& player) override;

private:
    MusicPlayer& player;
};

// Implementation of State methods

void Inactive::handle(Event event, MusicPlayer& player) {
    if (event == Event::OnOffPressed) {
        std::cout << "OnOffPressed event in 'inactive' state\n";
        player.setState(new On(player));
    }
}

void On::handle(Event event, MusicPlayer& player) {
    if (event == Event::PlayPausePressed) {
        player.setState(new Playing(player));
    } else if (event == Event::OnOffPressed) {
        player.setState(new Inactive(player));
    }
}

void Playing::handle(Event event, MusicPlayer& player) {
    if (event == Event::PlayPausePressed) {
        player.setState(new Paused(player));
    }
}

void Paused::handle(Event event, MusicPlayer& player) {
    if (event == Event::PlayPausePressed) {
        player.setState(new Playing(player));
    } else if (event == Event::OnOffPressed) {
        player.setState(new Inactive(player));
    }
}

// MusicPlayer Implementation

MusicPlayer::MusicPlayer() : state(new Inactive(*this)), led_on(false) {
    state->entry();
}

MusicPlayer::~MusicPlayer() {
    delete state;
}

void MusicPlayer::setState(State* new_state) {
    state->exit();
    delete state;
    state = new_state;
    state->entry();
}

void MusicPlayer::handle(Event event) {
    state->handle(event, *this);
}

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
