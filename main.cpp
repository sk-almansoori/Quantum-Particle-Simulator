#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <algorithm>

struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float radius;
};

void UpdateParticles(std::vector<Particle>& particles, int screenWidth, int screenHeight) {
    for (auto& particle : particles) {
        particle.position.x += particle.velocity.x;
        particle.position.y += particle.velocity.y;
        if (particle.position.x <= 0 || particle.position.x >= screenWidth) {
            particle.velocity.x *= -1;
        }
        if (particle.position.y <= 0 || particle.position.y >= screenHeight) {
            particle.velocity.y *= -1;
        }
    }
}

void DrawParticles(const std::vector<Particle>& particles) {
    for (const auto& particle : particles) {
        DrawCircleV(particle.position, particle.radius, particle.color);
    }
}

enum GameState {
    MENU,
    SIMULATION,
    SETTINGS,
    ABOUT,
    GAMES,
    QUANTUM_DODGE,
    FORMULA_QUIZ
};

void DrawMenu(int screenWidth, int screenHeight, int menuSelection) {
    DrawText("Quantum Particle Simulation", screenWidth / 2 - 300, screenHeight / 2 - 200, 40, PURPLE);
    DrawText("Start Simulation", screenWidth / 2 - 150, screenHeight / 2 - 50, 30, menuSelection == 0 ? YELLOW : WHITE);
    DrawText("Settings", screenWidth / 2 - 150, screenHeight / 2, 30, menuSelection == 1 ? YELLOW : WHITE);
    DrawText("About", screenWidth / 2 - 150, screenHeight / 2 + 50, 30, menuSelection == 2 ? YELLOW : WHITE);
    DrawText("Games", screenWidth / 2 - 150, screenHeight / 2 + 100, 30, menuSelection == 3 ? YELLOW : WHITE);
    DrawText("Exit", screenWidth / 2 - 150, screenHeight / 2 + 150, 30, menuSelection == 4 ? YELLOW : WHITE);
}

void DrawSettings(int screenWidth, int screenHeight) {
    DrawText("Settings", screenWidth / 2 - 100, screenHeight / 2 - 200, 40, PURPLE);
    DrawText("This simulation demonstrates particle motion in a quantum-inspired environment.", 
             screenWidth / 2 - 400, screenHeight / 2 - 100, 20, WHITE);
    DrawText("Particles bounce off walls and interact dynamically.", 
             screenWidth / 2 - 400, screenHeight / 2 - 60, 20, WHITE);
    DrawText("Press BACKSPACE to return to the menu.", 
             screenWidth / 2 - 400, screenHeight / 2 + 100, 20, YELLOW);
}

enum QuantumPrinciple {
    SUPERPOSITION,
    UNCERTAINTY,
    ENTANGLEMENT,
    WAVE_PARTICLE_DUALITY,
    CHAOS
};

struct Principle {
    std::string name;
    std::string description;
    std::string equation;
    QuantumPrinciple type;
};

void DrawPrinciple(const Principle& principle, int screenWidth, int screenHeight) {
    DrawText(("Principle: " + principle.name).c_str(), screenWidth / 2 - 300, screenHeight / 2 - 200, 30, PURPLE);
    DrawText(("Description: " + principle.description).c_str(), screenWidth / 2 - 300, screenHeight / 2 - 150, 20, WHITE);
    DrawText(("Equation: " + principle.equation).c_str(), screenWidth / 2 - 300, screenHeight / 2 - 100, 20, YELLOW);
    DrawText("Press BACKSPACE to return to the menu", screenWidth / 2 - 300, screenHeight / 2 + 100, 20, WHITE);
}

void DrawInteractivePrinciple(const Principle& principle, const std::vector<Particle>& particles, int screenWidth, int screenHeight) {
    DrawText(("Principle: " + principle.name).c_str(), 10, 10, 30, PURPLE);
    DrawText(("Description: " + principle.description).c_str(), 10, 50, 20, WHITE);
    DrawText("Equation:", 10, 90, 20, YELLOW);
    DrawText(principle.equation.c_str(), 100, 90, 20, GREEN);
    for (const auto& particle : particles) {
        DrawCircleV(particle.position, particle.radius, particle.color);
        DrawLine(particle.position.x, particle.position.y, screenWidth / 2, screenHeight / 2, Fade(WHITE, 0.2f));
    }
    DrawText("Press BACKSPACE to return to the menu", 10, screenHeight - 30, 20, WHITE);
}

void DrawQuantumMenu(int screenWidth, int screenHeight, int menuSelection) {
    DrawText("QUANTUM PARTICLE SIMULATION", screenWidth / 2 - 400, screenHeight / 2 - 300, 40, GREEN);
    DrawText(">> Start Simulation", screenWidth / 2 - 200, screenHeight / 2 - 100, 30, menuSelection == 0 ? YELLOW : GREEN);
    DrawText(">> Settings", screenWidth / 2 - 200, screenHeight / 2 - 50, 30, menuSelection == 1 ? YELLOW : GREEN);
    DrawText(">> Exit", screenWidth / 2 - 200, screenHeight / 2, 30, menuSelection == 2 ? YELLOW : GREEN);
    for (int i = 0; i < screenHeight; i += 20) {
        DrawText("|", std::rand() % screenWidth, i, 10, Fade(GREEN, 0.3f));
    }
}

void DrawInteractivePrinciple(const Principle& principle, const std::vector<Particle>& particles, int screenWidth, int screenHeight, float time) {
    DrawText(("Principle: " + principle.name).c_str(), 10, 10, 30, GREEN);
    DrawText(("Description: " + principle.description).c_str(), 10, 50, 20, WHITE);
    int equationLength = principle.equation.length();
    int visibleChars = static_cast<int>(time * 10) % (equationLength + 1);
    std::string animatedEquation = principle.equation.substr(0, visibleChars);
    DrawText("Equation:", 10, 90, 20, YELLOW);
    DrawText(animatedEquation.c_str(), 100, 90, 20, GREEN);
    for (const auto& particle : particles) {
        DrawCircleV(particle.position, particle.radius, particle.color);
        DrawLine(particle.position.x, particle.position.y, screenWidth / 2, screenHeight / 2, Fade(WHITE, 0.2f));
    }
    DrawText("Press BACKSPACE to return to the menu", 10, screenHeight - 30, 20, WHITE);
}

void DrawEnhancedMenu(int screenWidth, int screenHeight, int menuSelection, float time) {
    float scale = 1.0f + 0.1f * sin(time * 2.0f);
    int titleFontSize = static_cast<int>(60 * scale);
    DrawText("QUANTUM PARTICLE SIMULATION", screenWidth / 2 - MeasureText("QUANTUM PARTICLE SIMULATION", titleFontSize) / 2, screenHeight / 2 - 300, titleFontSize, PURPLE);
    const int menuStartY = screenHeight / 2 - 100;
    const int menuSpacing = 60;
    const char* menuOptions[] = {
        "Start Simulation",
        "Settings",
        "About",
        "Games",
        "Exit"
    };
    for (int i = 0; i < 5; i++) {
        Color optionColor = menuSelection == i ? YELLOW : WHITE;
        DrawText(menuOptions[i], screenWidth / 2 - MeasureText(menuOptions[i], 40) / 2, menuStartY + i * menuSpacing, 40, optionColor);
    }
    for (int i = 0; i < screenHeight; i += 30) {
        DrawText("|", std::rand() % screenWidth, i, 10, Fade(PURPLE, 0.1f));
    }
    DrawText("Use UP/DOWN to navigate, ENTER to select", screenWidth / 2 - 200, screenHeight - 50, 20, GRAY);
}

void DrawEnhancedSettings(int screenWidth, int screenHeight) {
    DrawText("Settings", screenWidth / 2 - 100, screenHeight / 2 - 300, 50, PURPLE);
    DrawText("This simulation demonstrates quantum principles:", screenWidth / 2 - 400, screenHeight / 2 - 200, 20, WHITE);
    DrawText("- Superposition: Particles exist in multiple states.", screenWidth / 2 - 400, screenHeight / 2 - 160, 20, WHITE);
    DrawText("- Uncertainty: Position and momentum cannot both be known.", screenWidth / 2 - 400, screenHeight / 2 - 120, 20, WHITE);
    DrawText("- Entanglement: Particles are correlated over distances.", screenWidth / 2 - 400, screenHeight / 2 - 80, 20, WHITE);
    DrawText("- Wave-Particle Duality: Particles behave as waves and particles.", screenWidth / 2 - 400, screenHeight / 2 - 40, 20, WHITE);
    DrawText("Press BACKSPACE to return to the menu.", screenWidth / 2 - 400, screenHeight / 2 + 200, 20, YELLOW);
}

void UpdateInteractiveParticles(std::vector<Particle>& particles, int screenWidth, int screenHeight) {
    for (auto& particle : particles) {
        particle.position.x += particle.velocity.x;
        particle.position.y += particle.velocity.y;
        if (particle.position.x <= 0 || particle.position.x >= screenWidth) {
            particle.velocity.x *= -1;
            particle.color = {static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), 255};
        }
        if (particle.position.y <= 0 || particle.position.y >= screenHeight) {
            particle.velocity.y *= -1;
            particle.color = {static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), 255};
        }
        Vector2 center = {static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2)};
        Vector2 direction = {center.x - particle.position.x, center.y - particle.position.y};
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance > 0) {
            direction.x /= distance;
            direction.y /= distance;
            particle.velocity.x += direction.x * 0.05f;
            particle.velocity.y += direction.y * 0.05f;
        }
    }
}

void UpdateParticlesByPrinciple(std::vector<Particle>& particles, QuantumPrinciple principle, int screenWidth, int screenHeight) {
    for (auto& particle : particles) {
        switch (principle) {
            case SUPERPOSITION:
                if (std::rand() % 100 < 2) {
                    particle.position = {static_cast<float>(std::rand() % screenWidth), static_cast<float>(std::rand() % screenHeight)};
                }
                break;
            case UNCERTAINTY:
                particle.velocity.x += static_cast<float>((std::rand() % 200 - 100) / 100.0f) * 0.1f;
                particle.velocity.y += static_cast<float>((std::rand() % 200 - 100) / 100.0f) * 0.1f;
                break;
            case ENTANGLEMENT:
                if (&particle != &particles[0]) {
                    particle.position = particles[0].position;
                }
                break;
            case WAVE_PARTICLE_DUALITY:
                particle.position.y += sin(particle.position.x * 0.05f) * 2.0f;
                break;
            case CHAOS:
                particle.velocity.x += static_cast<float>((std::rand() % 200 - 100) / 100.0f) * 0.5f;
                particle.velocity.y += static_cast<float>((std::rand() % 200 - 100) / 100.0f) * 0.5f;
                particle.color = {static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), 255};
                break;
        }
        particle.position.x += particle.velocity.x;
        particle.position.y += particle.velocity.y;
        if (particle.position.x <= 0 || particle.position.x >= screenWidth) {
            particle.velocity.x *= -1;
        }
        if (particle.position.y <= 0 || particle.position.y >= screenHeight) {
            particle.velocity.y *= -1;
        }
    }
}

enum SettingsOption {
    TOGGLE_FULLSCREEN,
    CHANGE_PARTICLE_COUNT,
    BACK_TO_MENU
};

void DrawSettingsMenu(int screenWidth, int screenHeight, int settingsSelection, bool isFullscreen, int particleCount) {
    DrawText("Settings", screenWidth / 2 - 100, screenHeight / 2 - 300, 50, PURPLE);
    DrawText("Toggle Fullscreen", screenWidth / 2 - 200, screenHeight / 2 - 100, 30, settingsSelection == TOGGLE_FULLSCREEN ? YELLOW : WHITE);
    DrawText(isFullscreen ? "[ON]" : "[OFF]", screenWidth / 2 + 200, screenHeight / 2 - 100, 30, GREEN);
    DrawText("Change Particle Count", screenWidth / 2 - 200, screenHeight / 2 - 50, 30, settingsSelection == CHANGE_PARTICLE_COUNT ? YELLOW : WHITE);
    DrawText(std::to_string(particleCount).c_str(), screenWidth / 2 + 200, screenHeight / 2 - 50, 30, GREEN);
    DrawText("Back to Menu", screenWidth / 2 - 200, screenHeight / 2, 30, settingsSelection == BACK_TO_MENU ? YELLOW : WHITE);
}

void AddUniqueFeaturesToParticles(std::vector<Particle>& particles, int screenWidth, int screenHeight) {
    for (auto& particle : particles) {
        DrawCircleV(particle.position, particle.radius + 2, Fade(particle.color, 0.3f));
        DrawCircleV(particle.position, particle.radius, particle.color);
        DrawLine(particle.position.x, particle.position.y, particle.position.x - particle.velocity.x * 10, particle.position.y - particle.velocity.y * 10, Fade(WHITE, 0.2f));
    }
}

void DrawEnhancedAboutMenu(int screenWidth, int screenHeight) {
    DrawText("About", screenWidth / 2 - 100, screenHeight / 2 - 300, 50, PURPLE);
    DrawText("Quantum Particle Simulation", screenWidth / 2 - 300, screenHeight / 2 - 200, 30, WHITE);
    DrawText("Created to demonstrate quantum mechanics principles.", screenWidth / 2 - 300, screenHeight / 2 - 150, 20, WHITE);
    DrawText("Features include interactive particles and dynamic visuals.", screenWidth / 2 - 300, screenHeight / 2 - 120, 20, WHITE);
    DrawText("Explore concepts like Superposition, Uncertainty, and more.", screenWidth / 2 - 300, screenHeight / 2 - 90, 20, WHITE);
    DrawText("Press BACKSPACE to return to the menu.", screenWidth / 2 - 300, screenHeight / 2 + 200, 20, YELLOW);
}

void DrawGamesMenu(int screenWidth, int screenHeight, int gamesSelection) {
    DrawText("Games", screenWidth / 2 - 100, screenHeight / 2 - 300, 50, PURPLE);
    DrawText("Quantum Dodge", screenWidth / 2 - 200, screenHeight / 2 - 100, 30, gamesSelection == 0 ? YELLOW : WHITE);
    DrawText("Formula Quiz", screenWidth / 2 - 200, screenHeight / 2 - 50, 30, gamesSelection == 1 ? YELLOW : WHITE);
    DrawText("Back to Menu", screenWidth / 2 - 200, screenHeight / 2, 30, gamesSelection == 2 ? YELLOW : WHITE);
}

void QuantumDodgeGame(int screenWidth, int screenHeight, bool& exitGame) {
    static Vector2 player = {screenWidth / 2.0f, static_cast<float>(screenHeight - 50)};
    static std::vector<Particle> obstacles;
    static float spawnTimer = 0.0f;
    static int score = 0;
    spawnTimer += GetFrameTime();
    if (spawnTimer > 1.0f) {
        spawnTimer = 0.0f;
        Particle obstacle = {
            {static_cast<float>(std::rand() % screenWidth), 0},
            {0, static_cast<float>(std::rand() % 100 + 100) / 100.0f},
            {static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), 255},
            static_cast<float>(std::rand() % 10 + 10)
        };
        obstacles.push_back(obstacle);
    }
    if (IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= 300 * GetFrameTime();
    if (IsKeyDown(KEY_RIGHT) && player.x < screenWidth) player.x += 300 * GetFrameTime();
    DrawCircleV(player, 20, Fade(GREEN, 0.5f));
    DrawCircleV(player, 15, GREEN);
    for (auto& obstacle : obstacles) {
        obstacle.position.y += obstacle.velocity.y;
        if (std::rand() % 100 < 5) {
            obstacle.position.x += static_cast<float>((std::rand() % 200 - 100) / 100.0f);
        }
    }
    for (const auto& obstacle : obstacles) {
        if (CheckCollisionCircles(player, 15, obstacle.position, obstacle.radius)) {
            exitGame = true;
        }
    }
    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                                    [&](const Particle& obstacle) { return obstacle.position.y > screenHeight; }),
                    obstacles.end());
    score += obstacles.size();
    for (const auto& obstacle : obstacles) {
        DrawCircleV(obstacle.position, obstacle.radius, obstacle.color);
    }
    DrawText("Quantum Dodge", screenWidth / 2 - 150, 10, 30, PURPLE);
    DrawText(("Score: " + std::to_string(score)).c_str(), 10, 10, 20, WHITE);
    DrawText("Use LEFT/RIGHT to move. Avoid obstacles!", 10, screenHeight - 30, 20, WHITE);
}

void FormulaQuizGame(int screenWidth, int screenHeight, bool& exitGame) {
    static std::vector<std::pair<std::string, std::string>> questions = {
        {"What is the formula for Superposition?", "Ψ = Σ cₙ |n⟩"},
        {"What is the formula for Uncertainty Principle?", "delta(x · delta(p ≥ planks red constant / 2"},
        {"What is the formula for Wave-Particle Duality?", "lamda = h / p"}
    };
    static int currentQuestion = 0;
    static bool showAnswer = false;
    if (IsKeyPressed(KEY_ENTER)) {
        showAnswer = true;
    } else if (IsKeyPressed(KEY_RIGHT)) {
        currentQuestion = (currentQuestion + 1) % questions.size();
        showAnswer = false;
    } else if (IsKeyPressed(KEY_LEFT)) {
        currentQuestion = (currentQuestion - 1 + questions.size()) % questions.size();
        showAnswer = false;
    } else if (IsKeyPressed(KEY_BACKSPACE)) {
        exitGame = true;
    }
    ClearBackground(BLACK);
    DrawText("Formula Quiz", screenWidth / 2 - 150, 10, 30, PURPLE);
    DrawText(("Question: " + questions[currentQuestion].first).c_str(), 10, 100, 20, WHITE);
    if (showAnswer) {
        DrawText(("Answer: " + questions[currentQuestion].second).c_str(), 10, 150, 20, GREEN);
    } else {
        DrawText("Press ENTER to show the answer", 10, 150, 20, YELLOW);
    }
    DrawText("Use LEFT/RIGHT to navigate questions", 10, screenHeight - 50, 20, WHITE);
    DrawText("Press BACKSPACE to return to the menu", 10, screenHeight - 30, 20, WHITE);
}

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Quantum Particle Simulation");
    ToggleFullscreen();
    std::srand(std::time(nullptr));
    int particleCount = 100;
    std::vector<Particle> particles;
    for (int i = 0; i < particleCount; i++) {
        Particle particle = {
            {static_cast<float>(std::rand() % screenWidth), static_cast<float>(std::rand() % screenHeight)},
            {static_cast<float>((std::rand() % 200 - 100) / 100.0f), static_cast<float>((std::rand() % 200 - 100) / 100.0f)},
            {static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), 255},
            static_cast<float>(std::rand() % 5 + 5)
        };
        particles.push_back(particle);
    }
    SetTargetFPS(60);
    GameState gameState = MENU;
    int menuSelection = 0;
    std::vector<Principle> principles = {
        {"Superposition", "A particle can exist in multiple states simultaneously.", "‎ psi = sum c_n |n>", SUPERPOSITION},
        {"Uncertainty Principle", "You cannot simultaneously know the exact position and momentum of a particle.", "‎ dx * dp >= h / (4*pi)", UNCERTAINTY},
        {"Entanglement", "Particles can be correlated regardless of distance.", "No specific equation", ENTANGLEMENT},
        {"Wave-Particle Duality", "Particles exhibit both wave and particle properties.", "‎ lambda = h / p", WAVE_PARTICLE_DUALITY},
        {"Chaos", "Particles move chaotically with random velocity and color changes.", "No specific equation", CHAOS}
    };
    QuantumPrinciple currentPrinciple = SUPERPOSITION;
    bool showPrinciple = false;
    float time = 0.0f;
    bool isFullscreen = true;
    int settingsSelection = 0;
    int gamesSelection = 0;
    bool exitQuantumDodge = false;
    bool exitFormulaQuiz = false;
    while (!WindowShouldClose()) {
        time += GetFrameTime();
        if (gameState == MENU) {
            if (IsKeyPressed(KEY_DOWN)) menuSelection = (menuSelection + 1) % 5;
            if (IsKeyPressed(KEY_UP)) menuSelection = (menuSelection - 1 + 5) % 5;
            if (IsKeyPressed(KEY_ENTER)) {
                if (menuSelection == 0) {
                    gameState = SIMULATION;
                } else if (menuSelection == 1) {
                    gameState = SETTINGS;
                } else if (menuSelection == 2) {
                    gameState = ABOUT;
                } else if (menuSelection == 3) {
                    gameState = GAMES;
                } else if (menuSelection == 4) {
                    CloseWindow();
                    return 0;
                }
            }
        } else if (gameState == SETTINGS) {
            if (IsKeyPressed(KEY_DOWN)) settingsSelection = (settingsSelection + 1) % 3;
            if (IsKeyPressed(KEY_UP)) settingsSelection = (settingsSelection - 1 + 3) % 3;
            if (IsKeyPressed(KEY_ENTER)) {
                if (settingsSelection == TOGGLE_FULLSCREEN) {
                    isFullscreen = !isFullscreen;
                    ToggleFullscreen();
                } else if (settingsSelection == CHANGE_PARTICLE_COUNT) {
                    particleCount += 50;
                    if (particleCount > 500) particleCount = 50;
                    particles.resize(particleCount);
                } else if (settingsSelection == BACK_TO_MENU) {
                    gameState = MENU;
                }
            }
        } else if (gameState == ABOUT) {
            if (IsKeyPressed(KEY_BACKSPACE)) {
                gameState = MENU;
            }
        } else if (gameState == SIMULATION) {
            if (IsKeyPressed(KEY_BACKSPACE)) {
                gameState = MENU;
            }
            if (IsKeyPressed(KEY_ONE)) {
                currentPrinciple = SUPERPOSITION;
                showPrinciple = true;
            } else if (IsKeyPressed(KEY_TWO)) {
                currentPrinciple = UNCERTAINTY;
                showPrinciple = true;
            } else if (IsKeyPressed(KEY_THREE)) {
                currentPrinciple = ENTANGLEMENT;
                showPrinciple = true;
            } else if (IsKeyPressed(KEY_FOUR)) {
                currentPrinciple = WAVE_PARTICLE_DUALITY;
                showPrinciple = true;
            } else if (IsKeyPressed(KEY_FIVE)) {
                currentPrinciple = CHAOS;
                showPrinciple = true;
            }
            UpdateParticlesByPrinciple(particles, currentPrinciple, screenWidth, screenHeight);
        } else if (gameState == GAMES) {
            if (IsKeyPressed(KEY_DOWN)) gamesSelection = (gamesSelection + 1) % 3;
            if (IsKeyPressed(KEY_UP)) gamesSelection = (gamesSelection - 1 + 3) % 3;
            if (IsKeyPressed(KEY_ENTER)) {
                if (gamesSelection == 0) {
                    gameState = QUANTUM_DODGE;
                } else if (gamesSelection == 1) {
                    gameState = FORMULA_QUIZ;
                } else if (gamesSelection == 2) {
                    gameState = MENU;
                }
            }
        } else if (gameState == QUANTUM_DODGE) {
            QuantumDodgeGame(screenWidth, screenHeight, exitQuantumDodge);
            if (exitQuantumDodge || IsKeyPressed(KEY_BACKSPACE)) {
                gameState = GAMES;
                exitQuantumDodge = false;
            }
        } else if (gameState == FORMULA_QUIZ) {
            FormulaQuizGame(screenWidth, screenHeight, exitFormulaQuiz);
            if (exitFormulaQuiz) {
                gameState = GAMES;
                exitFormulaQuiz = false;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        if (gameState == MENU) {
            DrawEnhancedMenu(screenWidth, screenHeight, menuSelection, time);
        } else if (gameState == SETTINGS) {
            DrawSettingsMenu(screenWidth, screenHeight, settingsSelection, isFullscreen, particleCount);
        } else if (gameState == ABOUT) {
            DrawEnhancedAboutMenu(screenWidth, screenHeight);
        } else if (gameState == SIMULATION) {
            if (showPrinciple) {
                DrawInteractivePrinciple(principles[currentPrinciple], particles, screenWidth, screenHeight);
            } else {
                DrawText("Press 1-5 to explore quantum principles", 10, 10, 20, WHITE);
                AddUniqueFeaturesToParticles(particles, screenWidth, screenHeight);
            }
        } else if (gameState == GAMES) {
            DrawGamesMenu(screenWidth, screenHeight, gamesSelection);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}