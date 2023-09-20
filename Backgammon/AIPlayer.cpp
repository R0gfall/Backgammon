#include "AIPlayer.h"
#include <time.h>

AIPlayer::AIPlayer(PlayerOrderType orderType, AiDifficulty difficulty, IGameStateMachine* stateMachine, Board* board) : IPlayer(orderType, stateMachine, board), _difficulty(difficulty)
{
    Debug::LogInfo("AI player was created");
}

void AIPlayer::OnTurnEnter()
{
    /*switch (_difficulty) {
    case AiDifficulty::Easy:
        printf("1");
    case AiDifficulty::Medium:
        printf("2");
    case AiDifficulty::Hard:
        printf("3");
    }*/
    //printf("3123123123");
    if (!IsAnyTurnsPossible()) {
        NextTurn();
    }
    else if (Dice::IsDouble()) {
        for (int i = 0; i < 4; i++) {
            if (!IsAnyTurnsPossible()) {
                NextTurn();
            }
            auto possibleTurns = CalculatePossibleTurns();
            int rand_cell = rand() % 24;
            auto itr = possibleTurns.find(rand_cell);
            while (itr == possibleTurns.end()) {
                rand_cell = rand() % 24;
                itr = possibleTurns.find(rand_cell);
            }
            int quantity_moves = 0;
            auto value = (itr)->second;
            int rand_move = rand() % value.size();
            auto right_cell = value.front();
            for (auto element : value)
            {
                if (quantity_moves == rand_move) {
                    right_cell = element;
                }
                quantity_moves++;
            }
            printf("From id: %d to id: %d\n", rand_cell, right_cell);
            GameBoard->MoveCheck(rand_cell, right_cell);
        }
    }
    else {
        for (int i = 0; i < 2; i++) {
            if (!IsAnyTurnsPossible()) {
                NextTurn();
            }
            /*auto possibleTurns1 = CalculatePossibleTurns();
            for (int j = 0; j < 24; j++) {
                auto itr1 = possibleTurns1.find(j);
                if (itr1 != possibleTurns1.end())
                {
                    auto key = (itr1)->first;
                    auto value1 = (itr1)->second;

                    for (auto element1 : value1)
                    {
                        printf("%d %d \n", key, element1);
                    }
                }
            }*/
            auto possibleTurns = CalculatePossibleTurns();
            int rand_cell = rand() % 24;
            auto itr = possibleTurns.find(rand_cell);
            while (itr == possibleTurns.end()) {
                rand_cell = rand() % 24;
                itr = possibleTurns.find(rand_cell);
            }
            int quantity_moves = 0;
            auto value = (itr)->second;
            int rand_move = rand() % value.size();
            auto right_cell = value.front();
            for (auto element : value)
            {
                if (quantity_moves == rand_move) {
                    right_cell = element;
                }
                quantity_moves++;
            }
            printf("From id: %d to id: %d \n", rand_cell, right_cell);
            GameBoard->MoveCheck(rand_cell, right_cell);
        }
    }
    NextTurn();
    //// получить все возможные ходы
    //// auto possibleTurns = GameBoard->GetAllPossibleTurns(OrderType);
    //auto possibleTurns = CalculatePossibleTurns();


    //auto itr = possibleTurns.find(1);
    //if (itr != possibleTurns.end())
    //{
    //    auto key = (itr)->first;
    //    auto value = (itr)->second;

    //    for (auto element : value)
    //    {
    //        element;
    //    }
    //}
    //// получить клетку по айди
    //auto cell = GameBoard->GetCellById(0);
    //// свободная клетка или нет
    //cell->IsFree();
    ////CellStatus;
    //// передвинуть пешку с клетки на клетку
    //GameBoard->MoveCheck(0, 1);
    //// передать ход аппоненту
    //NextTurn();
}

void AIPlayer::OnEndTurnEnter()
{

    //printf("3123123123");
    if (Dice::IsDouble()) {
        short k = 0, _i = 0, flag = 0;
        auto dices = Dice::GetDices();
        for (int i = dices.x; i >= 0; i--) {
            if (GameBoard->TryRemoveCheck(6 + i)) {
                printf("Removed check from cell id: %d\n", i);
                k++;
                flag = 1;
                break;
            }
            else if (GameBoard->TryRemoveCheck(23 - i)) {
                _i = 23 - i;
                printf("Removed check from cell id: %d\n", _i);
                k++;
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            for (int i = dices.x; i >= 0; i--) {
                if (GameBoard->TryRemoveCheck(i)) {
                    printf("Removed check from cell id: %d\n", i);
                    k++;
                    break;
                }
                else if (GameBoard->TryRemoveCheck(23 - i)) {
                    _i = 23 - i;
                    printf("Removed check from cell id: %d\n", _i);
                    k++;
                    break;
                }
            }
        }
        flag = 0;
        for (int i = dices.y; i >= 0; i--) {
            if (GameBoard->TryRemoveCheck(i)) {
                printf("Removed check from cell id: %d\n", i);
                k++;
                flag = 1;
                break;
            }
            else if (GameBoard->TryRemoveCheck(23 - i)) {
                short _i = 23 - i;
                printf("Removed check from cell id: %d\n", _i);
                k++;
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            for (int i = dices.y; i >= 0; i--) {
                if (GameBoard->TryRemoveCheck(i)) {
                    printf("Removed check from cell id: %d\n", i);
                    k++;
                    break;
                }
                else if (GameBoard->TryRemoveCheck(23 - i)) {
                    short _i = 23 - i;
                    printf("Removed check from cell id: %d\n", _i);
                    k++;
                    break;
                }
            }
        }
        for (int i = 0; i < 4 - k; i++) {
            if (!IsAnyTurnsPossible()) {
                NextTurn();
            }
            auto possibleTurns = CalculatePossibleTurns();
            int rand_cell = rand() % 24;
            auto itr = possibleTurns.find(rand_cell);
            while (itr == possibleTurns.end()) {
                rand_cell = rand() % 24;
                itr = possibleTurns.find(rand_cell);
            }
            int quantity_moves = 0;
            auto value = (itr)->second;
            int rand_move = rand() % value.size();
            auto right_cell = value.front();
            for (auto element : value)
            {
                if (quantity_moves == rand_move) {
                    right_cell = element;
                }
                quantity_moves++;
            }
            printf("From id: %d to id: %d\n", rand_cell, right_cell);
            GameBoard->MoveCheck(rand_cell, right_cell);
            if (i != 3 - k) {
                if (GameBoard->TryRemoveCheck(right_cell)) {
                    printf("Removed check from cell id: %d\n", right_cell);
                    i++;
                }
            }
        }
    }
    else {
        short k = 0, _i = 0;
        auto dices = Dice::GetDices();
        for (int i = dices.x; i >= 0; i--) {
            if (GameBoard->TryRemoveCheck(i)) {
                printf("Removed check from cell id: %d\n", i);
                k++;
                break;
            }
            else if (GameBoard->TryRemoveCheck(23 - i)) {
                _i = 23 - i;
                printf("Removed check from cell id: %d\n", _i);
                k++;
                break;
            }
        }
        for (int i = dices.y; i >= 0; i--) {
            if (GameBoard->TryRemoveCheck(i)) {
                printf("Removed check from cell id: %d\n", i);
                k++;
                break;
            }
            else if (GameBoard->TryRemoveCheck(23 - i)) {
                _i = 23 - i;
                printf("Removed check from cell id: %d\n", _i);
                k++;
                break;
            }
        }
        for (int i = 0; i < 2 - k; i++) {
            if (!IsAnyTurnsPossible()) {
                NextTurn();
            }
            auto possibleTurns = CalculatePossibleTurns();
            int rand_cell = rand() % 24;
            auto itr = possibleTurns.find(rand_cell);
            while (itr == possibleTurns.end()) {
                rand_cell = rand() % 24;
                itr = possibleTurns.find(rand_cell);
            }
            int quantity_moves = 0;
            auto value = (itr)->second;
            int rand_move = rand() % value.size();
            auto right_cell = value.front();
            for (auto element : value)
            {
                if (quantity_moves == rand_move) {
                    right_cell = element;
                }
                quantity_moves++;
            }
            printf("From id: %d to id: %d\n", rand_cell, right_cell);
            GameBoard->MoveCheck(rand_cell, right_cell);
            if (i != 1 - k) {
                if (GameBoard->TryRemoveCheck(right_cell)) {
                    printf("Removed check from cell id: %d\n", right_cell);
                    i++;
                }
            }
        }
    }
    NextTurn();

    //auto slov = GameBoard->GetAllPossibleTurns(OrderType);
    //
    //auto dices = Dice::GetDices();
    //Dice::IsDouble();
    ////dices.x;
}

void AIPlayer::OnUpdate()
{
}

void AIPlayer::OnEndUpdate()
{
}

void AIPlayer::OnTurnExit()
{
}
