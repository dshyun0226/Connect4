#pragma warning(disable : 4996)

char board[7][7];
int len[7];

#include<stdio.h>

int dx[4] = { 0, 1, 1, 1 }, dy[4] = { -1, -1, 0, 1 };
int log_opposite[49], log_my[49], len_opposite, len_my;

void print_board() {
	for (int i = 6;i >= 0; i--) {
		for (int j = 0;j < 7;j++) {
			if (board[i][j] != 0) printf("%c", board[i][j]);
			else printf(".");
		}
		printf("\n");
	}
}

int max_connect(bool flag, int x) {
	int tx = len[x] - 1, ty = x;
	int maxv = 0;

	for (int i = 0; i < 4; i++) {
		int cnt = 1;
		for (int j = 1; j < 4; j++) {
			int target_x = tx + dx[i] * j, target_y = ty + dy[i] * j;
			if (target_x < 0 || target_x >= 7 || target_y < 0 || target_y >= 7) break;
			if (flag && board[target_x][target_y] != 'O') break;
			else if (!flag && board[target_x][target_y] != 'X') break;
			cnt++;
		}
		for (int j = -1; j > -4; j--) {
			int target_x = tx + dx[i] * j, target_y = ty + dy[i] * j;
			if (target_x < 0 || target_x >= 7 || target_y < 0 || target_y >= 7) break;
			if (flag && board[target_x][target_y] != 'O') break;
			else if (!flag && board[target_x][target_y] != 'X') break;
			cnt++;
		}
		if (cnt > maxv) maxv = cnt;
	}
	return maxv>4?4:maxv;
}

bool is_win(bool flag, int x) {
	if (max_connect(flag, x) >= 4) return true;
	return false;
}


void put_opposite(int x) {
	board[len[x]++][x] = 'X';
}

int input_opposite() {
	int d;
	while (true) {
		print_board();
		printf("Where to put (0 ~ 6) : ");
		scanf("%d", &d);
		if (len[d] < 7) break;
		printf("Error: Invalid Position \n\n");
	}
	put_opposite(d);
	log_opposite[len_opposite++] = d;
	return d;
}

void put_my(int x) {
	board[len[x]++][x] = 'O';
}

void deput(int x) {
	board[--len[x]][x] = 0;
}