#pragma once
#include <map>
#include <vector>

class AppState;

enum AppStates
{
    MENU,
    GAME,
    MINING,
};
class App
{
private:
    static constexpr double dt = 1.0 / 120.0;
    float smoothedFps = 60.0f;
    bool running = true;
    bool showFps = true;
    std::map<AppStates, AppState *> AppReg;
    AppState *currentState;
    std::vector<AppState *> PersistApps;

public:
    double mstime;
    App();
    void run();
    void changeAppState(AppStates state);
    void printFps(double frameTime);
    void toggleFps();
    void exitApp() { running = false; };
    AppState* getState(AppStates state);
};