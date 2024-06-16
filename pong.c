#include <stdio.h>

void print_table(int left_pad, int right_pad, int ball_x, int ball_y);
int modify_ball_x(int x);
int modify_ball_y(int y);
int left_pad_move(int left_pad, char key);
int right_pad_move(int right_pad, char key);
int left_ball_touch(int ball_x, int ball_y, int left_pad);
int right_ball_touch(int ball_x, int ball_y, int right_pad);
void clear();
void game_loop();

int left_pad = 13;
int right_pad = 13;
int ball_x = 12;
int ball_y = 40;
char key;
int dir_x = 1;
int dir_y = 1;
int left_point, right_point;

int main() {
    game_loop();
    return 0;
}

void game_loop() {
    while (key != 'q' && left_point < 21 && right_point < 21) {
        key = getchar();
        clear();
        if (key == 'a' || key == 'z' || key == 'k' || key == 'm' || key == ' ') {
            left_pad = left_pad_move(left_pad, key);
            right_pad = right_pad_move(right_pad, key);
            ball_x = modify_ball_x(ball_x);
            ball_y = modify_ball_y(ball_y);
        }
        if (left_ball_touch(ball_x, ball_y, left_pad) == 1) {
            dir_y = 1;
        }
        if (right_ball_touch(ball_x, ball_y, right_pad) == -1) {
            dir_y = -1;
        }
        if (ball_y == 78) {
            left_point++;
            ball_x = 12;
            ball_y = 40;
            dir_y = -dir_y;
        } else if (ball_y == 1) {
            right_point++;
            ball_x = 12;
            ball_y = 40;
            dir_y = -dir_y;
        }
        print_table(left_pad, right_pad, ball_x, ball_y);
    }
}

int modify_ball_x(int ball_x) {
    if ((ball_x > 23 || ball_x < 3)) {
        dir_x = -dir_x;
    }

    return (ball_x + dir_x);
}

int modify_ball_y(int ball_y) {
    if ((ball_y > 77 || ball_y < 2)) {
        dir_y = -dir_y;
    }

    return (ball_y + dir_y);
}

int left_pad_move(int left_pad, char key) {
    if (key == 'a' && left_pad > 3) {
        --left_pad;
    } else if (key == 'z' && left_pad < 23) {
        ++left_pad;
    }
    return left_pad;
}

int right_pad_move(int right_pad, char key) {
    if (key == 'k' && right_pad > 3) {
        --right_pad;
    } else if (key == 'm' && right_pad < 23) {
        ++right_pad;
    }
    return right_pad;
}

int left_ball_touch(int ball_x, int ball_y, int left_pad) {
    if ((ball_x == left_pad && ball_y == 1) || (ball_x == left_pad - 1 && ball_y == 1) ||
        (ball_x == left_pad + 1 && ball_y == 1)) {
        dir_y = -dir_y;
    }
    return dir_y;
}

int right_ball_touch(int ball_x, int ball_y, int right_pad) {
    if ((ball_x == right_pad && ball_y == 78) || (ball_x == right_pad - 1 && ball_y == 78) ||
        (ball_x == right_pad + 1 && ball_y == 78)) {
        dir_y = -dir_y;
    }
    return dir_y;
}

void print_table(int left_pad, int right_pad, int ball_x, int ball_y) {
    printf("Player 1: %d Player 2: %d \t\n", left_point, right_point);
    for (int height = 1; height < 26 + 1; height++) {  // height - высота поля
        for (int width = 0; width < 80; width++) {     // width - ширина поля
            if (height == 1 || height == 26) {
                printf("-");
            } else if (((width == 1) &&
                        (height == left_pad - 1 || height == left_pad || height == left_pad + 1)) ||
                       ((height == right_pad - 1 || height == right_pad || height == right_pad + 1) &&
                        (width == 80 - 2))) {
                printf("|");
            } else if (width == 39) {
                printf("|");
            } else if (width == 0 || width == 80 - 1) {
                printf("|");
            } else if (height == ball_x && width == ball_y) {  // рождение шарика
                printf("o");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void clear() { printf("\033[0d\033[2j"); }