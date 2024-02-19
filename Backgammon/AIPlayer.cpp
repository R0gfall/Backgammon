#include "AIPlayer.h"
#include <time.h>

struct list_move {
    char array_of_moves[8];
    struct list_move* p_next_list;
};

struct list_move* start_list_move = NULL;

void nm_24_16(int(&array)[24]) {
    //èçìåíåíèÿ íà÷àëüíîé ïîçèöèè äîñêè
    for (int j = 0; j < 16; j++) {
        array[0] = 15; //1 = ÷åðíûå
        array[12] = -15; //2 = áåëûå
    }

    //for (int j = 0; j < 16; j++) {
    //	//array[2][j] = 1;
    //	array[14] = 2;

    //}
}

void print_out(int(&array)[24][16]) {
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

int grade_for_game_1(int(&array)[24]) {
    //Ïîäñ÷åò øàøåê ÒÎËÜÊÎ äëÿ îöåíêè ñèòóàöèè â èãðå ÁÅÇ Ó×ÅÒÀ ÊÎÍÖÀ ÈÃÐÛ
    //Ïóíêò 1, ïîäïóíêò À â îò÷åòå

    int first_player_points = 0, second_player_points = 0;

    for (int i = 0; i < 24; i++) {
        if (array[i] >= 1) {
            first_player_points += i * array[i];
        }
        else if (array[i] <= -1) {
            if (i >= 12) {
                second_player_points += (i - 12) * (-array[i]);
            }
            else {
                second_player_points += (i + 12) * (-array[i]);
            }
        }
    }

    //printf("%d\n%d\n", first_player_points, second_player_points);
    //printf("\n%d\n%d\n", first_player_points, second_player_points);
    return first_player_points - second_player_points;

}

int grade_for_game_2(int(&array)[24]) {

    //Íóæíî ðåøèòü îöåíêó äëÿ ïîëåé!

    // !!! FOR 1 PLAYER:
    //0-5 - *2 point
    //6-11 - *4 point
    //12-17 - *6 point
    //18-23 - *8 point

    // !!! FOR 2 PLAYER:
    //0-5 - *6 point
    //6-11 - *8 point
    //12-17 - *4 point
    //18-23 - *2 point

    int first_player_points = 0, second_player_points = 0;

    for (int i = 0; i < 24; i++) {

        if (array[i] >= 1) {
            if (0 <= i && i <= 5) {
                first_player_points += 2 + 0;
            }
            else if (6 <= i && i <= 11) {
                first_player_points += 2 + 2;
            }
            else if (12 <= i && i <= 17) {
                first_player_points += 2 + 4;
            }
            else if (18 <= i && i <= 23) {
                first_player_points += 2 + 6;
            }
        }
        else if (array[i] <= -1) {
            if (0 <= i && i <= 5) {
                second_player_points += 4 + 2;
            }
            else if (6 <= i && i <= 11) {
                second_player_points += 6 + 2;
            }
            else if (12 <= i && i <= 17) {
                second_player_points += 0 + 2;
            }
            else if (18 <= i && i <= 23) {
                second_player_points += 2 + 2;
            }
        }
    }
    //printf("\n%d\n%d\n", first_player_points, second_player_points);
    //printf("%d\n%d\n", first_player_points, second_player_points);
    return first_player_points - second_player_points;

}

void random_dice(int* dice) {
    //Ðàíäîìíûé áðîñîê êóáèêîâ
    srand(time(NULL));
    dice[0] = rand() % 5 + 1;
    dice[1] = rand() % 5 + 1;
}

int  get_all_possible_moves(int(&array)[24], short dice_x, short dice_y, short enterPlayer) {
    // TODO
    int number_of_moves = 0;
    int array_temp[24];
    int rollback[6];
    if (dice_x > dice_y) {
        short dice_temp;
        dice_temp = dice_y;
        dice_y = dice_x;
        dice_x = dice_temp;
    }
    for (int i = 0; i < 24; i++) {
        array_temp[i] = array[i];
        //printf("%d \n", array_temp[i]);
    }
    if (enterPlayer == 1) {
        if (dice_x == dice_y) {
            for (int i = 0; i < 24 - dice_x; i++) {
                if (array_temp[i] >= 1 && array_temp[i + dice_x] >= 0) {
                    rollback[0] = i;
                    rollback[1] = i + dice_x;
                    array_temp[i] --;
                    array_temp[i + dice_x] ++;
                    for (int j = 1; j < 24 - dice_x; j++) {
                        if (array_temp[j] >= 1 && array_temp[j + dice_x] >= 0) {
                            rollback[2] = j;
                            rollback[3] = j + dice_x;
                            array_temp[j] --;
                            array_temp[j + dice_x] ++;
                            for (int k = 1; k < 24 - dice_x; k++) {
                                if (array_temp[k] >= 1 && array_temp[k + dice_x] >= 0) {
                                    rollback[4] = k;
                                    rollback[5] = k + dice_x;
                                    array_temp[k] --;
                                    array_temp[k + dice_x] ++;
                                    for (int l = 1; l < 24 - dice_x; l++) {
                                        if (array_temp[l] >= 1 && array_temp[l + dice_x] >= 0) {
                                            struct list_move* new_list = (struct list_move*)malloc(sizeof(struct list_move));
                                            new_list->array_of_moves[0] = rollback[0];
                                            new_list->array_of_moves[1] = rollback[1];
                                            new_list->array_of_moves[2] = rollback[2];
                                            new_list->array_of_moves[3] = rollback[3];
                                            new_list->array_of_moves[4] = rollback[4];
                                            new_list->array_of_moves[5] = rollback[5];
                                            new_list->array_of_moves[6] = l;
                                            new_list->array_of_moves[7] = l + dice_x;;
                                            new_list->p_next_list = start_list_move;
                                            start_list_move = new_list;
                                            number_of_moves++;
                                            return number_of_moves;
                                        }
                                    }
                                    array_temp[rollback[4]]++;
                                    array_temp[rollback[5]]--;
                                }
                            }
                            array_temp[rollback[2]]++;
                            array_temp[rollback[3]]--;
                        }
                    }
                    array_temp[rollback[0]]++;
                    array_temp[rollback[1]]--;
                }
            }
        }
        else {
            for (int i = 0; i < 24 - dice_y; i++) {
                if (array_temp[i] >= 1 && array_temp[i + dice_y] >= 0) {
                    rollback[0] = i;
                    rollback[1] = i + dice_y;
                    array_temp[i] --;
                    array_temp[i + dice_y] ++;
                    for (int j = 1; j < 24 - dice_x; j++) {
                        if (array_temp[j] >= 1 && array_temp[j + dice_x] >= 0) {
                            struct list_move* new_list = (struct list_move*)malloc(sizeof(struct list_move));
                            new_list->array_of_moves[0] = rollback[0];
                            new_list->array_of_moves[1] = rollback[1];
                            new_list->array_of_moves[2] = j;
                            new_list->array_of_moves[3] = j + dice_x;
                            new_list->array_of_moves[4] = -1;
                            new_list->array_of_moves[5] = -1;
                            new_list->array_of_moves[6] = -1;
                            new_list->array_of_moves[7] = -1;
                            new_list->p_next_list = start_list_move;
                            start_list_move = new_list;
                            number_of_moves++;
                        }
                    }
                    array_temp[rollback[0]]++;
                    array_temp[rollback[1]]--;
                }
            }
            for (int i = 0; i < 24 - dice_x; i++) {
                if (array_temp[i] >= 1 && array_temp[i + dice_x] >= 0) {
                    rollback[0] = i;
                    rollback[1] = i + dice_x;
                    array_temp[i] --;
                    array_temp[i + dice_x] ++;
                    for (int j = 1; j < 24 - dice_y; j++) {
                        if (array_temp[j] >= 1 && array_temp[j + dice_y] >= 0) {
                            struct list_move* new_list = (struct list_move*)malloc(sizeof(struct list_move));
                            new_list->array_of_moves[0] = rollback[0];
                            new_list->array_of_moves[1] = rollback[1];
                            new_list->array_of_moves[2] = j;
                            new_list->array_of_moves[3] = j + dice_y;
                            new_list->array_of_moves[4] = -1;
                            new_list->array_of_moves[5] = -1;
                            new_list->array_of_moves[6] = -1;
                            new_list->array_of_moves[7] = -1;
                            new_list->p_next_list = start_list_move;
                            start_list_move = new_list;
                            number_of_moves++;
                        }
                    }
                    array_temp[rollback[0]]++;
                    array_temp[rollback[1]]--;
                }
            }
        }
    }
    else {
        if (dice_x == dice_y) {
            for (int i = 0; i < 24 - dice_x; i++) {
                if (array_temp[(12 + i) % 24] <= -1 && array_temp[(12 + i + dice_x) % 24] <= 0) {
                    rollback[0] = (12 + i) % 24;
                    rollback[1] = (12 + i + dice_x) % 24;
                    array_temp[(12 + i) % 24] ++;
                    array_temp[(12 + i + dice_x) % 24] --;
                    for (int j = 1; j < 24 - dice_x; j++) {
                        if (array_temp[(12 + j) % 24] <= -1 && array_temp[(12 + j + dice_x) % 24] <= 0) {
                            rollback[2] = (12 + j) % 24;
                            rollback[3] = (12 + j + dice_x) % 24;
                            array_temp[(12 + j) % 24] ++;
                            array_temp[(12 + j + dice_x) % 24] --;
                            for (int k = 1; k < 24 - dice_x; k++) {
                                if (array_temp[(12 + k) % 24] <= -1 && array_temp[(12 + k + dice_x) % 24] <= 0) {
                                    rollback[4] = (12 + k) % 24;
                                    rollback[5] = (12 + k + dice_x) % 24;
                                    array_temp[(12 + k) % 24] ++;
                                    array_temp[(12 + k + dice_x) % 24] --;
                                    for (int l = 1; l < 24 - dice_x; l++) {
                                        if (array_temp[(12 + l) % 24] <= -1 && array_temp[(12 + l + dice_x) % 24] <= 0) {
                                            struct list_move* new_list = (struct list_move*)malloc(sizeof(struct list_move));
                                            new_list->array_of_moves[0] = rollback[0];
                                            new_list->array_of_moves[1] = rollback[1];
                                            new_list->array_of_moves[2] = rollback[2];
                                            new_list->array_of_moves[3] = rollback[3];
                                            new_list->array_of_moves[4] = rollback[4];
                                            new_list->array_of_moves[5] = rollback[5];
                                            new_list->array_of_moves[6] = (12 + l) % 24;
                                            new_list->array_of_moves[7] = (12 + l + dice_x) % 24;;
                                            new_list->p_next_list = start_list_move;
                                            start_list_move = new_list;
                                            number_of_moves++;
                                            return number_of_moves;
                                        }
                                    }
                                    array_temp[rollback[4]]--;
                                    array_temp[rollback[5]]++;
                                }
                            }
                            array_temp[rollback[2]]--;
                            array_temp[rollback[3]]++;
                        }
                    }
                    array_temp[rollback[0]]--;
                    array_temp[rollback[1]]++;
                }
            }
        }
        else {
            for (int i = 0; i < 24 - dice_y; i++) {
                if (array_temp[(12 + i) % 24] <= -1 && array_temp[(12 + i + dice_y) % 24] <= 0) {
                    rollback[0] = (12 + i) % 24;
                    rollback[1] = (12 + i + dice_y) % 24;
                    array_temp[(12 + i) % 24] ++;
                    array_temp[(12 + i + dice_y) % 24] --;
                    for (int j = 1; j < 24 - dice_x; j++) {
                        //printf("\n%d \n%d\n", array_temp[(12 + j) % 24], array_temp[(12 + j + dice_x) % 24]);
                        if (array_temp[(12 + j) % 24] <= -1 && array_temp[(12 + j + dice_x) % 24] <= 0) {
                            struct list_move* new_list = (struct list_move*)malloc(sizeof(struct list_move));
                            new_list->array_of_moves[0] = rollback[0];
                            new_list->array_of_moves[1] = rollback[1];
                            new_list->array_of_moves[2] = (12 + j) % 24;
                            new_list->array_of_moves[3] = (12 + j + dice_x) % 24;
                            new_list->array_of_moves[4] = -1;
                            new_list->array_of_moves[5] = -1;
                            new_list->array_of_moves[6] = -1;
                            new_list->array_of_moves[7] = -1;
                            new_list->p_next_list = start_list_move;
                            start_list_move = new_list;
                            number_of_moves++;
                        }
                    }
                    array_temp[rollback[0]]--;
                    array_temp[rollback[1]]++;
                }
            }
            for (int i = 0; i < 24 - dice_x; i++) {
                if (array_temp[(12 + i) % 24] <= -1 && array_temp[(12 + i + dice_x) % 24] <= 0) {
                    rollback[0] = (12 + i) % 24;
                    rollback[1] = (12 + i + dice_x) % 24;
                    array_temp[(12 + i) % 24] ++;
                    array_temp[(12 + i + dice_x) % 24] --;
                    for (int j = 1; j < 24 - dice_y; j++) {
                        if (array_temp[(12 + j) % 24] <= -1 && array_temp[(12 + j + dice_y) % 24] <= 0) {
                            struct list_move* new_list = (struct list_move*)malloc(sizeof(struct list_move));
                            new_list->array_of_moves[0] = rollback[0];
                            new_list->array_of_moves[1] = rollback[1];
                            new_list->array_of_moves[2] = (12 + j) % 24;
                            new_list->array_of_moves[3] = (12 + j + dice_y) % 24;
                            new_list->array_of_moves[4] = -1;
                            new_list->array_of_moves[5] = -1;
                            new_list->array_of_moves[6] = -1;
                            new_list->array_of_moves[7] = -1;
                            new_list->p_next_list = start_list_move;
                            start_list_move = new_list;
                            number_of_moves++;
                        }
                    }
                    array_temp[rollback[0]]--;
                    array_temp[rollback[1]]++;
                }
            }
        }
    }
    return number_of_moves;
}

double grade_of_position(int(&array)[24], short depht, short enterPlayer) {
    int rollback[8];
    int array_temp[24];
    double all_grade = 0;
    int quantity_of_grade = 1;
    for (int i = 0; i < 24; i++) {
        array_temp[i] = array[i];
    }
    for (int i = 1; i < 7; i++) {
        for (int j = 1; j < 7; j++) {
            int number_of_moves = 0;
            if (enterPlayer == 1) {
                number_of_moves = get_all_possible_moves(array_temp, i, j, 1);
            }
            else {
                number_of_moves = get_all_possible_moves(array_temp, i, j, 2);
            }
            //printf("%d 12312312312321312\n", number_of_moves);
            for (int k = 0; k < number_of_moves; k++) {
                //printf("3123123123 jopas\n");
                struct list_move* rollback_start = start_list_move;
                int quantity_of_array_of_moves = 0;
                for (int l = 0; l < 8; l += 2) {
                    //TODO ïðàâèëüíûé ëè if
                    //printf("%d \n", start_list_move->array_of_moves[l] >= 0);
                    if (start_list_move->array_of_moves[l] >= 0 && start_list_move->array_of_moves[l] <= 23 && start_list_move->array_of_moves[l] != start_list_move->array_of_moves[l + 1]) {
                        //printf("3123123123 jopassss99999999\n");
                        rollback[l] = start_list_move->array_of_moves[l];
                        rollback[l + 1] = start_list_move->array_of_moves[l + 1];
                        if (enterPlayer == 1) {
                            array_temp[start_list_move->array_of_moves[l]]--;
                            array_temp[start_list_move->array_of_moves[l + 1]]++;
                        }
                        else {
                            array_temp[start_list_move->array_of_moves[l]]++;
                            array_temp[start_list_move->array_of_moves[l + 1]]--;
                        }
                        quantity_of_array_of_moves += 2;
                    }
                    else {
                        break;
                    }
                }
                //printf("%d \n", quantity_of_array_of_moves);
                start_list_move = start_list_move->p_next_list;
                free(rollback_start);
                //printf("3123123123 jopassss77777777\n");
                rollback_start = start_list_move;
                //printf("3123123123 jopassss77777777\n");
                if (enterPlayer == 1 && depht == 1) {
                    //долго
                    //all_grade += grade_of_position(array_temp, depht + 1, 2);
                    // быстро
                    all_grade += grade_for_game_1(array_temp) + grade_for_game_2(array_temp);
                    quantity_of_grade++;
                }
                else if (enterPlayer == 2 && depht == 1) {
                    //printf("3123123123 jopassss8888888\n");
                    //долго
                    //all_grade += grade_of_position(array_temp, depht + 1, 1);
                    // быстро
                    all_grade += grade_for_game_1(array_temp) + grade_for_game_2(array_temp);
                    //printf("%f \n", all_grade);
                    quantity_of_grade++;
                }
                else {
                    all_grade += grade_for_game_1(array_temp) + grade_for_game_2(array_temp);
                    quantity_of_grade++;
                }
                if (enterPlayer == 1) {
                    for (int l = 0; l < quantity_of_array_of_moves; l += 2) {
                        array_temp[rollback[l]] ++;
                        array_temp[rollback[l + 1]] --;
                    }
                }
                else {
                    for (int l = 0; l < quantity_of_array_of_moves; l += 2) {
                        array_temp[rollback[l]] --;
                        array_temp[rollback[l + 1]] ++;
                    }
                }
                //printf("3123123123 jopa\n");
            }
            // âñå íîðì
            //ñóêà ïèçäåö íóæíî ñäåëàòü ÷òîáû îíè õîäû èç ðàçíûõ íå áðàëè
        }
    }
    //printf("%f \n", all_grade / (double)quantity_of_grade);
    return all_grade / (double)quantity_of_grade;
}

int* algoritm(int(&backgrammon)[24], short dice_x, short dice_y, short enterPlayer) {

    //ïåðåäàâàåìûå ïàðàìåòðû: äîñêà boad(backgrammon), dice_x, dice_y, enterPlayer - 1 - áåëûé 2 - ÷åðíûé
    int grade = 0;
    /*int backgrammon[24];
    for (int i = 0; i < 24; i++) {
        backgrammon[i] = 0;
    }*/

    //Äîáàâèòü enterPlayer
    //int enterPlayer = 1;
    /*backgrammon[0] = 9;
    backgrammon[4] = 2;
    backgrammon[8] = 3;
    backgrammon[13] = 1;
    backgrammon[12] = -8;
    backgrammon[14] = -5;
    backgrammon[15] = -1;
    backgrammon[23] = -1;
    backgrammon[22] = 0;*/
    //backgrammon[0] = 15;
    //backgrammon[12] = -15;
    //nm_24_16(backgrammon); // Ïîñòàíîâêà øàøåê

    //printf("\n%d 1241241414184141089249\n", grade_for_game_2(backgrammon) + grade_for_game_1(backgrammon));
    //äóáëèêàò äîñêè
    int temp_backgrammon[24];
    for (int i = 0; i < 24; i++) {
        temp_backgrammon[i] = 0;
    }
    for (int i = 0; i < 24; i++) {
        temp_backgrammon[i] = backgrammon[i];
    }

    short dice[2] = { dice_x, dice_y }; // ×èñëà ñ áðîñêà êóáèêà	
    char moves_and_grade[10000][8];
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 8; j++) {
            moves_and_grade[i][j] = -1;
        }
    }
    float grade_of_moves[10000];
    int quantity_moves, quantity_grades = 0;
    quantity_moves = get_all_possible_moves(backgrammon, dice[0], dice[1], enterPlayer);
    printf("%d do it \n", quantity_moves);
    for (int i = 0; i < quantity_moves; i++) {
        struct list_move* rollback_start = start_list_move;
        int quantity_of_array_of_moves = 0;
        for (int j = 0; j < 8; j += 2) {
            if (start_list_move->array_of_moves[j] >= 0 && start_list_move->array_of_moves[j] <= 23 && start_list_move->array_of_moves[j] != start_list_move->array_of_moves[j + 1]) {
                moves_and_grade[i][j] = start_list_move->array_of_moves[j];
                moves_and_grade[i][j + 1] = start_list_move->array_of_moves[j + 1];
                //printf("Move %d %d \n", moves_and_grade[i][j], moves_and_grade[i][j + 1]);
                if (enterPlayer == 1) {
                    temp_backgrammon[start_list_move->array_of_moves[j]]--;
                    temp_backgrammon[start_list_move->array_of_moves[j + 1]]++;
                }
                else {
                    temp_backgrammon[start_list_move->array_of_moves[j]]++;
                    temp_backgrammon[start_list_move->array_of_moves[j + 1]]--;
                }
                quantity_of_array_of_moves += 2;
            }
            else {
                break;
            }
        }
        start_list_move = start_list_move->p_next_list;
        free(rollback_start);
        rollback_start = start_list_move;
        if (enterPlayer == 1) {
            //printf("ass\n");
            grade_of_moves[i] = grade_of_position(temp_backgrammon, 1, 2);
            //printf("ass\n");
        }
        else {
            grade_of_moves[i] = grade_of_position(temp_backgrammon, 1, 1);
        }
        //printf("asssssssssss\n");
        if (enterPlayer == 1) {
            for (int j = 0; j < quantity_of_array_of_moves; j += 2) {
                temp_backgrammon[moves_and_grade[i][j]] ++;
                temp_backgrammon[moves_and_grade[i][j + 1]] --;
            }
        }
        else {
            for (int j = 0; j < quantity_of_array_of_moves; j += 2) {
                temp_backgrammon[moves_and_grade[i][j]] --;
                temp_backgrammon[moves_and_grade[i][j + 1]] ++;
            }
        }
        //printf("asssssssssss\n");
        //printf("%d\n", quantity_grades);
        quantity_grades++;
    }
    int j = 0;
    double max_grade = grade_of_moves[0];
    int* best_move = new int[8];
    while (moves_and_grade[0][j] != -1 && j < 8) {
        best_move[j] = moves_and_grade[0][j];
        j++;
    }
    /*for (int i = 0; i < 8; i++) {
        best_move[i] = -1;
    }*/
    //Âûâîä âñåõ õîäîâ
   /* for (int i = 0; i < quantity_grades; i++) {
        printf("Grade: %f \n", grade_of_moves[i]);
        j = 0;
        bool flag = false;
        if (max_grade <= grade_of_moves[i]) {
            max_grade = grade_of_moves[i];
            for (int i = 0; i < 8; i++) {
                best_move[i] = -1;
            }
            flag = true;
        }
        printf("MOVES: ");
        while (moves_and_grade[i][j] != -1 && j < 8) {
            if (flag) {
                best_move[j] = moves_and_grade[i][j];
            }
            printf("%d ", moves_and_grade[i][j]);
            j++;
        }
        printf("\n");
    }*/
    if (enterPlayer == 1) {
        for (int i = 0; i < quantity_grades; i++) {
            j = 0;
            bool flag = false;
            if (max_grade <= grade_of_moves[i]) {
                max_grade = grade_of_moves[i];
                for (int i = 0; i < 8; i++) {
                    best_move[i] = -1;
                }
                flag = true;
            }
            if (flag) {
                while (moves_and_grade[i][j] != -1 && j < 8) {
                    best_move[j] = moves_and_grade[i][j];
                    j++;
                }
            }
        }
    }
    else {
        for (int i = 0; i < quantity_grades; i++) {
            j = 0;
            bool flag = false;
            if (max_grade >= grade_of_moves[i]) {
                max_grade = grade_of_moves[i];
                for (int i = 0; i < 8; i++) {
                    best_move[i] = -1;
                }
                flag = true;
            }
            if (flag) {
                while (moves_and_grade[i][j] != -1 && j < 8) {
                    best_move[j] = moves_and_grade[i][j];
                    j++;
                }
            }
        }
    }
    j = 0;
    printf("BEST\n");
    while (best_move[j] != -1 && j < 8) {
        printf("\n%d %d\n", best_move[j], best_move[j + 1]);
        j += 2;
    }

    return best_move;

    //grade_for_game_1(backgrammon); // Îöåíêà òåêóùåé ñèòóàöèè

    //grade = grade_for_game_2(backgrammon) + grade_for_game_1(backgrammon);
    //printf("%d\n", grade);

}

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
    //printf("%d \n", OrderType);
    int j = 0;
    auto dices = Dice::GetDices();
    if (!IsAnyTurnsPossible(AI_SHOULD_LOG)) {
        NextTurn();
        return;
    }
    switch (_difficulty) {

    case (AiDifficulty::Hard):
        int board[24];
        for (int i = 0; i < 24; i++) {
            auto cell_curr = GameBoard->GetCellById(i);
            board[i] = int(cell_curr->GetChecksAmout());
            if (cell_curr->GetStatus() == CellStatus::SecondPlayer) {
                board[i] = -board[i];
            }
        }
        int* move;
        if (OrderType == PlayerOrderType::FirstPlayer) {
            move = algoritm(board, dices.x, dices.y, 1);
        }
        else {
            move = algoritm(board, dices.x, dices.y, 2);
        }
        j = 0;
        printf("MOVES: ");
        while (move[j] != -1 && j < 8) {
            printf("%d %d", move[j], move[j + 1]);
            GameBoard->MoveCheck(move[j], move[j + 1]);
            j += 2;
        }
        delete move;
        printf("\n");
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
                if (!IsAnyTurnsPossible(AI_SHOULD_LOG)) {
                    NextTurn();
                    return;
                }
                short quantity_before_23 = 0, quantity_after_23 = 0, q_b = 0, q_a = 0;
                int q_b_23[100], q_a_23[100];
                possibleTurns = CalculatePossibleTurns(AI_SHOULD_LOG);
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
                    //Áûëî
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
                    //Áûëî
                    //printf("From id: %d to id: %d \n", q_a_23[0], q_a_23[1]);
                    //GameBoard->MoveCheck(q_a_23[0], q_a_23[1]);
                    //Ìîæåò áûòü
                    printf("From id: %d to id: %d \n", q_b_23[0], q_b_23[1]);
                    GameBoard->MoveCheck(q_b_23[0], q_b_23[1]);
                }
                else if (q_b == 0 && q_a != 0) {
                    printf("Third");
                    printf("From id: %d to id: %d \n", q_a_23[0], q_a_23[1]);
                    GameBoard->MoveCheck(q_a_23[0], q_a_23[1]);
                }
                else {
                    if (!IsAnyTurnsPossible(AI_SHOULD_LOG)) {
                        NextTurn();
                        return;
                    }
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
            //TODO êîëè÷åñòâî äî 23 è êîëè÷åñòâî ïîñëå 23 è ïðèíàäëåæèò ëè êëåòêà øàøêå
        }
        else {
            //TODO ïðè ñõîäå ñ áàøíè ëó÷øå õîäèòü íà íå çàíÿòóþ êëåòêó
            int k = 0;
            auto possibleTurns = CalculatePossibleTurns(AI_SHOULD_LOG);
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
                if (!IsAnyTurnsPossible(AI_SHOULD_LOG)) {
                    NextTurn();
                    return;
                }
                short quantity_before_23 = 0, quantity_after_23 = 0, q_b = 0, q_a = 0;
                int q_b_23[100], q_a_23[100];
                possibleTurns = CalculatePossibleTurns(AI_SHOULD_LOG);
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
                    //Áûëî
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
                    //Áûëî
                    //printf("From id: %d to id: %d \n", q_a_23[0], q_a_23[1]);
                    //GameBoard->MoveCheck(q_a_23[0], q_a_23[1]);
                    //Ìîæåò áûòü
                    printf("From id: %d to id: %d \n", q_b_23[0], q_b_23[1]);
                    GameBoard->MoveCheck(q_b_23[0], q_b_23[1]);
                }
                else if (q_b == 0 && q_a != 0) {
                    printf("Third");
                    printf("From id: %d to id: %d \n", q_a_23[0], q_a_23[1]);
                    GameBoard->MoveCheck(q_a_23[0], q_a_23[1]);
                }
                else {
                    if (!IsAnyTurnsPossible(AI_SHOULD_LOG)) {
                        NextTurn();
                        return;
                    }
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
    //// ïîëó÷èòü âñå âîçìîæíûå õîäû
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
    //// ïîëó÷èòü êëåòêó ïî àéäè
    //auto cell = GameBoard->GetCellById(0);
    //// ñâîáîäíàÿ êëåòêà èëè íåò
    //cell->IsFree();
    ////CellStatus;
    //// ïåðåäâèíóòü ïåøêó ñ êëåòêè íà êëåòêó
    //GameBoard->MoveCheck(0, 1);
    //// ïåðåäàòü õîä àïïîíåíòó
    //NextTurn();
}

void AIPlayer::OnEndTurnEnter()
{

    printf("3123123123 \n\n\n\n\n");
    int j = 0;
    auto dices = Dice::GetDices();
    /*switch (_difficulty) {
    case (AiDifficulty::Hard):
        int board[24];
        for (int i = 0; i < 24; i++) {
            auto cell_curr = GameBoard->GetCellById(i);
            board[i] = int(cell_curr->GetChecksAmout());
            if (cell_curr->GetStatus() == CellStatus::SecondPlayer) {
                board[i] = -board[i];
            }
        }
        int* move;
        if (OrderType == PlayerOrderType::FirstPlayer) {
            move = algoritm(board, dices.x, dices.y, 1);
        }
        else {
            move = algoritm(board, dices.x, dices.y, 2);
        }
        j = 0;
        while (move[j] != -1 && j < 8) {
            GameBoard->MoveCheck(move[j], move[j + 1]);
            j += 2;
        }
        NextTurn();
        return;

    default:*/
    if (Dice::IsDouble()) {
        for (int j = 0; j < 4; j++) {
            auto possibleTurns = CalculatePossibleTurns(AI_SHOULD_LOG);
            short flag = 1;
            if (OrderType == PlayerOrderType::SecondPlayer) {
                for (int i = 6; i < 12; i++) {
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
            else {
                for (int i = 18; i < 24; i++) {
                    if (possibleTurns.find(i) != possibleTurns.end()) {
                        printf("From id: %d to id: %d\n", i, i + dices.x);
                        GameBoard->MoveCheck(i, i + dices.x);
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    for (int i = 24 - dices.x; i < 24; i++) {
                        if (GameBoard->TryRemoveCheck(i)) {
                            printf("Removed check from cell id: %d\n", i);
                            break;
                        }
                    }
                }
            }
        }
    }
    else {
        auto possibleTurns = CalculatePossibleTurns(AI_SHOULD_LOG);
        short flag = 1;
        switch (dices.x) {
        case 6:
            if (OrderType == PlayerOrderType::SecondPlayer) {
                for (int i = 12 - dices.x; i < 12; i++) {
                    if (GameBoard->TryRemoveCheck(i)) {
                        printf("Removed check from cell id: %d\n", i);
                        break;
                    }
                }
            }
            else {
                for (int i = 24 - dices.x; i < 24; i++) {
                    if (GameBoard->TryRemoveCheck(i)) {
                        printf("Removed check from cell id: %d\n", i);
                        break;
                    }
                }
            }
            break;
        case 5:
        case 4:
            if (OrderType == PlayerOrderType::SecondPlayer) {
                for (int i = 6; i < 12; i++) {
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
            else {
                for (int i = 18; i < 24; i++) {
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
                    for (int i = 24 - dices.x; i < 24; i++) {
                        if (GameBoard->TryRemoveCheck(i)) {
                            printf("Removed check from cell id: %d\n", i);
                            break;
                        }
                    }
                }
            }
            break;
        default:
            if (OrderType == PlayerOrderType::SecondPlayer) {
                if (GameBoard->TryRemoveCheck(12 - dices.x)) {
                    printf("Removed check from cell id: %d\n", 12 - dices.x);
                    break;
                }
                else {
                    for (int i = 6; i < 12; i++) {
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
            }
            else {
                if (GameBoard->TryRemoveCheck(24 - dices.x)) {
                    printf("Removed check from cell id: %d\n", 24 - dices.x);
                    break;
                }
                else {
                    for (int i = 18; i < 24; i++) {
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
                        for (int i = 24 - dices.x; i < 24; i++) {
                            if (GameBoard->TryRemoveCheck(i)) {
                                printf("Removed check from cell id: %d\n", i);
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }
        possibleTurns = CalculatePossibleTurns(AI_SHOULD_LOG);
        flag = 1;
        switch (dices.y) {
        case 6:
            if (OrderType == PlayerOrderType::SecondPlayer) {
                for (int i = 12 - dices.y; i < 12; i++) {
                    if (GameBoard->TryRemoveCheck(i)) {
                        printf("Removed check from cell id: %d\n", i);
                        break;
                    }
                }
            }
            else {
                for (int i = 24 - dices.y; i < 24; i++) {
                    if (GameBoard->TryRemoveCheck(i)) {
                        printf("Removed check from cell id: %d\n", i);
                        break;
                    }
                }
            }
            break;
        case 5:
        case 4:
            if (OrderType == PlayerOrderType::SecondPlayer) {
                for (int i = 6; i < 12; i++) {
                    if (possibleTurns.find(i) != possibleTurns.end()) {
                        printf("From id: %d to id: %d\n", i, i + dices.y);
                        GameBoard->MoveCheck(i, i + dices.y);
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    for (int i = 12 - dices.y; i < 12; i++) {
                        if (GameBoard->TryRemoveCheck(i)) {
                            printf("Removed check from cell id: %d\n", i);
                            break;
                        }
                    }
                }
            }
            else {
                for (int i = 18; i < 24; i++) {
                    if (possibleTurns.find(i) != possibleTurns.end()) {
                        printf("From id: %d to id: %d\n", i, i + dices.y);
                        GameBoard->MoveCheck(i, i + dices.y);
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    for (int i = 24 - dices.y; i < 24; i++) {
                        if (GameBoard->TryRemoveCheck(i)) {
                            printf("Removed check from cell id: %d\n", i);
                            break;
                        }
                    }
                }
            }
            break;
        default:
            if (OrderType == PlayerOrderType::SecondPlayer) {
                if (GameBoard->TryRemoveCheck(12 - dices.y)) {
                    printf("Removed check from cell id: %d\n", 12 - dices.y);
                    break;
                }
                else {
                    for (int i = 6; i < 12; i++) {
                        if (possibleTurns.find(i) != possibleTurns.end()) {
                            printf("From id: %d to id: %d\n", i, i + dices.y);
                            GameBoard->MoveCheck(i, i + dices.y);
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1) {
                        for (int i = 12 - dices.y; i < 12; i++) {
                            if (GameBoard->TryRemoveCheck(i)) {
                                printf("Removed check from cell id: %d\n", i);
                                break;
                            }
                        }
                    }
                }
            }
            else {
                if (GameBoard->TryRemoveCheck(24 - dices.y)) {
                    printf("Removed check from cell id: %d\n", 24 - dices.y);
                    break;
                }
                else {
                    for (int i = 18; i < 24; i++) {
                        if (possibleTurns.find(i) != possibleTurns.end()) {
                            printf("From id: %d to id: %d\n", i, i + dices.y);
                            GameBoard->MoveCheck(i, i + dices.y);
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1) {
                        for (int i = 24 - dices.y; i < 24; i++) {
                            if (GameBoard->TryRemoveCheck(i)) {
                                printf("Removed check from cell id: %d\n", i);
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }

    }
    NextTurn();
    return;

    //}

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