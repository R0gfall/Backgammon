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
        return;
    }
    switch (_difficulty) {

    case AiDifficulty::Medium:
        if (Dice::IsDouble()) {
            for (int i = 0; i < 4; i++) {
                if (!IsAnyTurnsPossible()) {
                    NextTurn();
                    return;
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
                    return;
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
        return;
    default:
        if (Dice::IsDouble()) {
            int k = 0;
            auto possibleTurns = CalculatePossibleTurns();
            auto itr = possibleTurns.find(12);
            if (itr != possibleTurns.end()) {
                auto value = (itr)->second;
                printf("Head\n");
                printf("From id: %d to id: %d \n", 12, value.front());
                GameBoard->MoveCheck(12, value.front());
                k++;
            }
            if (!IsAnyTurnsPossible()) {
                NextTurn();
                return;
            }
            possibleTurns = CalculatePossibleTurns();
            itr = possibleTurns.find(12);
            if (itr != possibleTurns.end()) {
                auto value = (itr)->second;
                printf("HeadDouble\n");
                printf("From id: %d to id: %d \n", 12, value.front());
                GameBoard->MoveCheck(12, value.front());
                k++;
            }
            for (int j = 0; j < 4 - k; j++) {
                if (!IsAnyTurnsPossible()) {
                    NextTurn();
                    return;
                }
                short quantity_before_23 = 0, quantity_after_23 = 0, q_b = 0, q_a = 0;
                int q_b_23[100], q_a_23[100];
                possibleTurns = CalculatePossibleTurns();
                for (int i = 12; i < 24; i++) {
                    if (possibleTurns.find(i) != possibleTurns.end()) {
                        quantity_before_23++;
                        itr = possibleTurns.find(i);
                        auto value = (itr)->second;
                        for (auto element : value) {
                            if ((GameBoard->GetCellById(element))->IsFree()) {
                                q_b_23[q_b] = i;
                                q_b_23[q_b + 1] = element;
                                q_b += 2;
                            }
                        }
                    }
                }
                for (int i = 0; i < 12; i++) {
                    if (possibleTurns.find(i) != possibleTurns.end()) {
                        quantity_after_23++;
                        itr = possibleTurns.find(i);
                        auto value = (itr)->second;
                        for (auto element : value) {
                            if ((GameBoard->GetCellById(element))->IsFree()) {
                                q_a_23[q_a] = i;
                                q_a_23[q_a + 1] = element;
                                q_a += 2;
                            }
                        }
                    }
                }
                if (quantity_before_23 >= quantity_after_23 && q_b != 0) {
                    printf("First\n");
                    printf("From id: %d to id: %d \n", q_b_23[q_b - 2], q_b_23[q_b - 1]);
                    GameBoard->MoveCheck(q_b_23[q_b - 2], q_b_23[q_b - 1]);
                    //Ѕыло
                    //printf("From id: %d to id: %d \n", q_b_23[0], q_b_23[1]);
                    //GameBoard->MoveCheck(q_b_23[0], q_b_23[1]);
                }
                /*else if (q_a == 0 && q_b != 0) {
                    printf("Second Deleted\n");
                    printf("From id: %d to id: %d \n", q_b_23[q_b - 2], q_b_23[q_b - 1]);
                    GameBoard->MoveCheck(q_b_23[q_b - 2], q_b_23[q_b - 1]);
                }*/
                else if (q_a != 0 && q_b != 0) {
                    printf("Second\n");
                    //Ѕыло
                    //printf("From id: %d to id: %d \n", q_a_23[0], q_a_23[1]);
                    //GameBoard->MoveCheck(q_a_23[0], q_a_23[1]);
                    //ћожет быть
                    printf("From id: %d to id: %d \n", q_b_23[0], q_b_23[1]);
                    GameBoard->MoveCheck(q_b_23[0], q_b_23[1]);
                }
                else if (q_b == 0) {
                    printf("Third");
                    printf("From id: %d to id: %d \n", q_a_23[0], q_a_23[1]);
                    GameBoard->MoveCheck(q_a_23[0], q_a_23[1]);
                }
                else {
                    printf("Else\n");
                    int rand_cell = rand() % 24;
                    itr = possibleTurns.find(rand_cell);
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
            //TODO количество до 23 и количество после 23 и принадлежит ли клетка шашке
        }
        else {
            //TODO при сходе с башни лучше ходить на не зан€тую клетку
            int k = 0;
            auto possibleTurns = CalculatePossibleTurns();
            auto itr = possibleTurns.find(12);
            if (itr != possibleTurns.end()) {
                auto value = (itr)->second;
                printf("Head\n");
                if (((GameBoard->GetCellById(value.back()))->IsFree()) || !((GameBoard->GetCellById(value.front()))->IsFree())) {
                    printf("From id: %d to id: %d \n", 12, value.back());
                    GameBoard->MoveCheck(12, value.back());
                }
                else {
                    printf("From id: %d to id: %d \n", 12, value.front());
                    GameBoard->MoveCheck(12, value.front());
                }
                k++;
            }
            for (int j = 0; j < 2 - k; j++) {
                if (!IsAnyTurnsPossible()) {
                    NextTurn();
                    return;
                }
                short quantity_before_23 = 0, quantity_after_23 = 0, q_b = 0, q_a = 0;
                int q_b_23[100], q_a_23[100];
                possibleTurns = CalculatePossibleTurns();
                for (int i = 12; i < 24; i++) {
                    if (possibleTurns.find(i) != possibleTurns.end()) {
                        quantity_before_23++;
                        itr = possibleTurns.find(i);
                        auto value = (itr)->second;
                        for (auto element : value) {
                            if ((GameBoard->GetCellById(element))->IsFree()) {
                                q_b_23[q_b] = i;
                                q_b_23[q_b + 1] = element;
                                q_b += 2;
                            }
                        }
                    }
                }
                for (int i = 0; i < 12; i++) {
                    if (possibleTurns.find(i) != possibleTurns.end()) {
                        quantity_after_23++;
                        itr = possibleTurns.find(i);
                        auto value = (itr)->second;
                        for (auto element : value) {
                            if ((GameBoard->GetCellById(element))->IsFree()) {
                                q_a_23[q_a] = i;
                                q_a_23[q_a + 1] = element;
                                q_a += 2;
                            }
                        }
                    }
                }
                if (quantity_before_23 >= quantity_after_23 && q_b != 0) {
                    printf("First\n");
                    printf("From id: %d to id: %d \n", q_b_23[q_b - 2], q_b_23[q_b - 1]);
                    GameBoard->MoveCheck(q_b_23[q_b - 2], q_b_23[q_b - 1]);
                    //Ѕыло
                    //printf("From id: %d to id: %d \n", q_b_23[0], q_b_23[1]);
                    //GameBoard->MoveCheck(q_b_23[0], q_b_23[1]);
                }
                /*else if (q_a == 0 && q_b != 0) {
                    printf("Second Deleted\n");
                    printf("From id: %d to id: %d \n", q_b_23[q_b - 2], q_b_23[q_b - 1]);
                    GameBoard->MoveCheck(q_b_23[q_b - 2], q_b_23[q_b - 1]);
                }*/
                else if (q_a != 0 && q_b != 0) {
                    printf("Second\n");
                    //Ѕыло
                    //printf("From id: %d to id: %d \n", q_a_23[0], q_a_23[1]);
                    //GameBoard->MoveCheck(q_a_23[0], q_a_23[1]);
                    //ћожет быть
                    printf("From id: %d to id: %d \n", q_b_23[0], q_b_23[1]);
                    GameBoard->MoveCheck(q_b_23[0], q_b_23[1]);
                }
                else if (q_b == 0) {
                    printf("Third");
                    printf("From id: %d to id: %d \n", q_a_23[0], q_a_23[1]);
                    GameBoard->MoveCheck(q_a_23[0], q_a_23[1]);
                }
                else {
                    printf("Else\n");
                    int rand_cell = rand() % 24;
                    itr = possibleTurns.find(rand_cell);
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
        }
        NextTurn();
        return;
    }
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
    //// свободна€ клетка или нет
    //cell->IsFree();
    ////CellStatus;
    //// передвинуть пешку с клетки на клетку
    //GameBoard->MoveCheck(0, 1);
    //// передать ход аппоненту
    //NextTurn();
}

void AIPlayer::OnEndTurnEnter()
{

    printf("3123123123");
    switch (_difficulty) {
    case AiDifficulty::Easy:

        if (Dice::IsDouble()) {
            short k = 0, _i = 0, flag = 0;
            auto dices = Dice::GetDices();
            for (int i = dices.x; i >= 0; i--) {
                if (GameBoard->TryRemoveCheck(11 - i)) {
                    printf("Removed check from cell id: %d\n", 11 - i);
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
                    if (GameBoard->TryRemoveCheck(11 - i)) {
                        printf("Removed check from cell id: %d\n", 11 - i);
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
                if (GameBoard->TryRemoveCheck(11 - i)) {
                    printf("Removed check from cell id: %d\n", 11 - i);
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
                    if (GameBoard->TryRemoveCheck(11 - i)) {
                        printf("Removed check from cell id: %d\n", 11 - i);
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
                    return;
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
                if (GameBoard->TryRemoveCheck(11 - i)) {
                    printf("Removed check from cell id: %d\n", 11 - i);
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
                if (GameBoard->TryRemoveCheck(11 - i)) {
                    printf("Removed check from cell id: %d\n", 11 - i);
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
                    return;
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
        return;

    default:
        if (Dice::IsDouble()) {
            auto dices = Dice::GetDices();
            for (int j = 0; j < 4; j++) {
                auto possibleTurns = CalculatePossibleTurns();
                short flag = 1;
                for (int i = 6; i < dices.x; i++) {
                    if (possibleTurns.find(i) != possibleTurns.end()) {
                        printf("From id: %d to id: %d\n", i, i + dices.x);
                        GameBoard->MoveCheck(i, i + dices.x);
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    for (int i = 12 - dices.x; i < 12; i++) {
                        if (GameBoard->TryRemoveCheck(i)) {
                            printf("Removed check from cell id: %d\n", i);
                            break;
                        }
                    }
                }
            }
        }
        else {
            auto dices = Dice::GetDices();
            auto possibleTurns = CalculatePossibleTurns();
            short flag = 1;
            switch (dices.x) {
            case 6:
                for (int i = 12 - dices.x; i < 12; i++) {
                    if (GameBoard->TryRemoveCheck(i)) {
                        printf("Removed check from cell id: %d\n", i);
                        break;
                    }
                }
                break;
            case 5:
            case 4:
                for (int i = 6; i < dices.x; i++) {
                    auto itr = possibleTurns.find(i);
                    if (itr != possibleTurns.end()) {
                        auto value = (itr)->second;
                        if (value.front() == i + dices.x || value.back() == i + dices.x) {
                            printf("From id: %d to id: %d\n", i, i + dices.x);
                            GameBoard->MoveCheck(i, i + dices.x);
                            flag = 0;
                            break;
                        }
                    }
                }
                if (flag == 1) {
                    for (int i = 12 - dices.x; i < 12; i++) {
                        if (GameBoard->TryRemoveCheck(i)) {
                            printf("Removed check from cell id: %d\n", i);
                            break;
                        }
                    }
                }
                break;
            default:
                if (GameBoard->TryRemoveCheck(12 - dices.x)) {
                    printf("Removed check from cell id: %d\n", 12 - dices.x);
                    break;
                }
                else {
                    for (int i = 6; i < dices.x; i++) {
                        auto itr = possibleTurns.find(i);
                        if (itr != possibleTurns.end()) {
                            auto value = (itr)->second;
                            if (value.front() == i + dices.x || value.back() == i + dices.x) {
                                printf("From id: %d to id: %d\n", i, i + dices.x);
                                GameBoard->MoveCheck(i, i + dices.x);
                                flag = 0;
                                break;
                            }
                        }
                    }
                    if (flag == 1) {
                        for (int i = 12 - dices.x; i < 12; i++) {
                            if (GameBoard->TryRemoveCheck(i)) {
                                printf("Removed check from cell id: %d\n", i);
                                break;
                            }
                        }
                    }
                }
                break;
            }
            possibleTurns = CalculatePossibleTurns();
            flag = 1;
            switch (dices.y) {
            case 6:
                for (int i = 12 - dices.y; i < 12; i++) {
                    if (GameBoard->TryRemoveCheck(i)) {
                        printf("Removed check from cell id: %d\n", i);
                        break;
                    }
                }
                break;
            case 5:
            case 4:
                for (int i = 6; i < dices.y; i++) {
                    if (possibleTurns.find(i) != possibleTurns.end()) {
                        printf("From id: %d to id: %d\n", i, i + dices.y);
                        GameBoard->MoveCheck(i, i + dices.y);
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    for (int i = 12 - dices.x; i < 12; i++) {
                        if (GameBoard->TryRemoveCheck(i)) {
                            printf("Removed check from cell id: %d\n", i);
                            break;
                        }
                    }
                }
                break;
            default:
                if (GameBoard->TryRemoveCheck(12 - dices.x)) {
                    printf("Removed check from cell id: %d\n", 12 - dices.x);
                    break;
                }
                else {
                    for (int i = 6; i < dices.x; i++) {
                        if (possibleTurns.find(i) != possibleTurns.end()) {
                            printf("From id: %d to id: %d\n", i, i + dices.x);
                            GameBoard->MoveCheck(i, i + dices.x);
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1) {
                        for (int i = 12 - dices.x; i < 12; i++) {
                            if (GameBoard->TryRemoveCheck(i)) {
                                printf("Removed check from cell id: %d\n", i);
                                break;
                            }
                        }
                    }
                }
                break;
            }

        }
        NextTurn();
        return;

    }

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
