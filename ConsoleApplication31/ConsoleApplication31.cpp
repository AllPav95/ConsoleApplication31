#include <iostream>

#include <ctime>
#include <cstdlib>

const int fieldWidth = 5;
const int fieldHeight = 5;

struct Point2D {
    int x;
    int y;

    Point2D() : x(0), y(0) {}

    Point2D(int xVal, int yVal) : x(xVal), y(yVal) {}

    Point2D(const Point2D& other) : x(other.x), y(other.y) {}
};



struct Field {
    char cells[fieldHeight][fieldWidth];
    Point2D star;
    Point2D prize;

    Field() {
        for (int i = 0; i < fieldHeight; ++i) {
            for (int j = 0; j < fieldWidth; ++j) {
                cells[i][j] = '+';
            }
        }
    }


    Field(const Field& other) {
        star = other.star;
        prize = other.prize;
        for (int i = 0; i < fieldHeight; ++i) {
            for (int j = 0; j < fieldWidth; ++j) {
                cells[i][j] = other.cells[i][j];
            }
        }
    }
};

void drawField(const Field& field) {
    for (int i = 0; i < fieldHeight; ++i) {
        for (int j = 0; j < fieldWidth; ++j) {
            char symbol = (field.star.x == j && field.star.y == i) ? '*' : '+';
            if (field.prize.x == j && field.prize.y == i) {
                symbol = 'P'; 
            }
            std::cout << symbol << '+';
        }
        std::cout << std::endl;
    }
}

void placeStar(Field& field, int x, int y) {
    if (x >= 0 && x < fieldWidth && y >= 0 && y < fieldHeight) {
        field.star.x = x;
        field.star.y = y;
    }
}

void placePrize(Field& field, int x, int y) {
    if (x >= 0 && x < fieldWidth && y >= 0 && y < fieldHeight) {
        field.prize.x = x;
        field.prize.y = y;
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int starX = std::rand() % fieldWidth;
    int starY = std::rand() % fieldHeight;
    int prizeX = std::rand() % fieldWidth;
    int prizeY = std::rand() % fieldHeight;


    Field field;
    placeStar(field, starX, starY);
    placePrize(field, prizeX, prizeY);

    while (true) {
        std::system("clear");

        drawField(field);

        std::cout << "WASD to move, Q to quit: ";
        char action;
        std::cin >> action;

        if (action == 'Q' || action == 'q') {
            break;
        }

        int newX = field.star.x;
        int newY = field.star.y;

        switch (action) {
        case 'W':
        case 'w':
            newY--;
            break;
        case 'A':
        case 'a':
            newX--;
            break;
        case 'S':
        case 's':
            newY++;
            break;
        case 'D':
        case 'd':
            newX++;
            break;
        default:
            continue;
        }

        if (newX == field.prize.x && newY == field.prize.y) {
            prizeX = std::rand() % fieldWidth;
            prizeY = std::rand() % fieldHeight;
            placePrize(field, prizeX, prizeY);
        }

        placeStar(field, newX, newY);
    }

    return 0;
}