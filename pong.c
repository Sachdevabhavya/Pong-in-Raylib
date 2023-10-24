#include "raylib.h"

int main()
{
    float screenWidth = 800;
    float screenHeight = 450;

    float pad1pos = screenHeight / 3;
    float pad2pos = screenHeight / 3;

    int player1Score = 0;
    int player2Score = 0;

    int squareSize = 5;

    Vector2 ballPosition = {400, 113};
    Vector2 ballSpeed = {5.0f, 4.0f};
    float ballRadius = 20;

    bool hasBounced = false;

    InitWindow(screenWidth, screenHeight, "PONG!!");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        // Paddle rects
        Rectangle pad1 = {20, pad1pos, 20, screenHeight / 6};
        Rectangle pad2 = {760, pad2pos, 20, screenHeight / 6};

        Rectangle ballRect = {
            .x = ballPosition.x - ballRadius,
            .y = ballPosition.y - ballRadius,
            .width = ballRadius * 2,
            .height = ballRadius * 2};

        // Paddle 1 movement
        if (IsKeyDown(KEY_S))
            pad1pos += 10;
        if (IsKeyDown(KEY_W))
            pad1pos -= 10;
        if (pad1pos <= 0)
            pad1pos = 5;
        if (pad1pos >= 375)
            pad1pos = 370;

        // Paddle 2 movement
        if (IsKeyDown(KEY_DOWN))
            pad2pos += 10;
        if (IsKeyDown(KEY_UP))
            pad2pos -= 10;
        if (pad2pos <= 0)
            pad2pos = 5;
        if (pad2pos >= 375)
            pad2pos = 370;

        // ball movement
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        ballRect.x = ballPosition.x - ballRadius;
        ballRect.y = ballPosition.y - ballRadius;

        // Check collision with y-axis
        if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius))
        {
            ballSpeed.y *= -1.0f;
        }

        if (hasBounced != true)
        {
            // Check collision with paddle 1
            if (CheckCollisionCircleRec(ballPosition, ballRadius, pad1))
            {
                ballSpeed.x *= -1.0f;
                hasBounced = true;
            }

            // Check collision with paddle 2
            if (CheckCollisionCircleRec(ballPosition, ballRadius, pad2))
            {
                ballSpeed.x *= -1.0f;
                hasBounced = true;
            }
        }

        if (ballRect.x >= GetRenderWidth())
        {
            player1Score++;
            ballPosition.x = 400;
            ballPosition.y = 113;
        }

        if (ballRect.x <= 0)
        {
            player2Score++;
            ballPosition.x = 400;
            ballPosition.y = 113;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        // paddles 1 and two
        DrawRectangle(20, pad1pos, 20, screenHeight / 6, RAYWHITE);
        DrawRectangle(760, pad2pos, 20, screenHeight / 6, RAYWHITE);

        // score 1 and 2
        DrawText(TextFormat("%i", player1Score), 160, 12, 50, RAYWHITE);
        DrawText(TextFormat("%i", player2Score), 640, 12, 50, RAYWHITE);

        // Middle Dotted Line
        for (int i = 0; i < screenHeight; i += squareSize * 2)
        {
            Rectangle rect = {(float)(screenWidth / 2 - squareSize / 2), (float)i, (float)squareSize, (float)squareSize};
            DrawRectangleRec(rect, RAYWHITE);
        }

        DrawCircleV(ballPosition, (float)ballRadius, WHITE);
        DrawFPS(10, 10);

        hasBounced = false;
        EndDrawing();
    }

    CloseWindow();

    return 0;
}