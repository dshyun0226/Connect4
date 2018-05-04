#include<stdio.h>
#include<Windows.h>
#include "connect4_game.h"
#include "connect4_heuristic.h"

int maxf(int x, int y) {
	if(x > y)return x;
	else return y;
}

void winning_count(int board[][10], int player, int value[]) {

	int cnt, flag;
	int i, j, l;

	for (i = 1; i <= 7; i++) {
		for (j = 1; j <= 7; j++) {
			//����
			flag = cnt = 0;
			for (l = j; l > j - 4 && j > 3; l--) {
				if (board[l][i] != player && board[l][i] != 0) {
					flag = 1;
					break;
				}
				else if (board[l][i] == player) {
					cnt++;
				}
			}
			if (flag == 0) value[cnt]++;
			//����
			flag = cnt = 0;
			for (l = i; l > i - 4 && i > 3; l--) {
				if (board[j][l] != player && board[j][l] != 0) {
					flag = 1;
					break;
				}
				else if (board[j][l] == player) {
					cnt++;
				}
			}
			if (flag == 0) value[cnt]++;
			//������ �Ʒ�
			flag = cnt = 0;
			for (l = 0; l < 4 && i > 3 && j < 5; l++) {
				if (board[j + l][i - l] != player && board[j + l][i - l] != 0) {
					flag = 1;
					break;
				}
				else if (board[j + l][i - l] == player) {
					cnt++;
				}
			}
			if (flag == 0) value[cnt]++;
			//���� �Ʒ�
			flag = cnt = 0;
			for (l = 0; l < 4 && i > 3 && j > 3; l++) {
				if (board[j - l][i - l] != player && board[j - l][i - l] != 0) {
					flag = 1;
					break;
				}
				else if (board[j - l][i - l] == player) {
					cnt++;
				}
			}
			if (flag == 0) value[cnt]++;
		}
	}
}

int win_check(int x, int y, int board[][10]) {

	int i, j, min;

	j = -maxf(-7, -x - 3);
	for (i = maxf(1, x - 3); i <= j; i++) {
		if (board[i][y] * board[i + 1][y] * board[i + 2][y] * board[i + 3][y] == 1) {
			return 1;
		}
		else if (board[i][y] * board[i + 1][y] * board[i + 2][y] * board[i + 3][y] == 16) {
			return 2;
		}
	}
	j = -maxf(-7, -y - 3);
	for (i = maxf(1, y - 3); i <= j; i++) {
		if (board[x][i] * board[x][i + 1] * board[x][i + 2] * board[x][i + 3] == 1) {
			return 1;
		}
		else if (board[x][i] * board[x][i + 1] * board[x][i + 2] * board[x][i + 3] == 16) {
			return 2;
		}
	}
	//������
	min = -maxf(-x, -y);
	for (i = maxf(-3, 1 - min); x + i + 3 < 8 && y + i + 3 < 8; i++) {
		if (board[x + i][y + i] * board[x + i + 1][y + i + 1] * board[x + i + 2][y + i + 2] * board[x + i + 3][y + i + 3] == 1) {
			return 1;
		}
		else if (board[x + i][y + i] * board[x + i + 1][y + i + 1] * board[x + i + 2][y + i + 2] * board[x + i + 3][y + i + 3] == 16) {
			return 2;
		}
	}
	min = -maxf(-(8 - x), -y);
	for (i = maxf(-3, 1 - min); x - i - 3 > 0 && y + i + 3 < 8; i++) {
		if (board[x - i][y + i] * board[x - i - 1][y + i + 1] * board[x - i - 2][y + i + 2] * board[x - i - 3][y + i + 3] == 1) {
			return 1;
		}
		else if (board[x - i][y + i] * board[x - i - 1][y + i + 1] * board[x - i - 2][y + i + 2] * board[x - i - 3][y + i + 3] == 16) {
			return 2;
		}
	}
	return 0;
}

int negamax_tree(int depth, int board[][10], int sign, int alpha, int beta, int *best_x, int put_x, int put_y) {
	int immi_board[10][10] = { 0 };
	int top_x[8] = { 0 };
	int top_y[8] = { 0 };
	int my_value[4] = { 0 };
	int oppo_value[4] = { 0 };
	int value, best_value;
	int child_num = 0;
	int i, j, x, y, winner = 0;

	for (j = 1; j <= 7; j++) {
		for (i = 1; i <= 7; i++) {
			immi_board[j][i] = board[j][i];
			if (immi_board[j][i] == 0) {
				top_x[child_num] = j;
				top_y[child_num] = i;
				child_num++;
				break;
			}
		}
	}

	if (depth == 0) {
		winning_count(immi_board, 1, my_value);
		winning_count(immi_board, 2, oppo_value);
		return sign * (my_value[0] + my_value[1] * 5 + my_value[2] * 10 + my_value[3] * 100
			- oppo_value[0] - oppo_value[1] * 3 - oppo_value[2] * 7 - oppo_value[3] * 100);
	}

	if (put_x != 0 && put_y != 0) {
		winner = win_check(put_x, put_y, board);
		if (winner == 1) {
			return sign * INFI;
		}
		else if (winner == 2) {
			return sign * -INFI;
		}
	}

	best_value = -INFI;
	for (i = 0; i < child_num; i++) {
		x = top_x[i];
		y = top_y[i];
		if (sign == 1) immi_board[x][y] = 1;
		else immi_board[x][y] = 2;
		value = -negamax_tree(depth - 1, immi_board, -sign, -beta, -alpha, best_x, x, y);
		immi_board[x][y] = 0;
		if (best_value < value) {
			best_value = value;
			if (depth == MAXDEPTH) {
				*best_x = x;
			}
		}
		alpha = maxf(alpha, value);
		if (alpha >= beta)
			break;
	}
	return best_value;
	
}

int get_position_by_heuristic() {

	int best_x, negamax_value;

	negamax_value = negamax_tree(MAXDEPTH, board, 1, -INFI, INFI, &best_x, 0, 0);

	return best_x;
}