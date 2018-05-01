#pragma once

extern char board[7][7];
extern int len[7];
extern int dx[4], dy[4];
extern int log_opposite[49], log_my[49], len_opposite, len_my;

void print_board();

void put_opposite(int x);

int input_opposite();

void put_my(int x);

void deput(int x);

bool is_win(bool flag, int x);

int max_connect(bool flag, int x);