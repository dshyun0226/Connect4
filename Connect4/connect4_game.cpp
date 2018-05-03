#pragma warning(disable : 4996)

#include<windows.h>
#include<stdio.h>
#include "connect4_heuristic.h"
#include "connect4_rulebase2.h"
#include "connect4_game.h"

int board[10][10], len[10], log[50][2], turn = 1;
int dy[4] = { 0, -1, -1, -1 }, dx[4] = { -1, -1, 0, 1 };

void print_board() {
	for (int i = 7;i >= 1;i--) {
		printf("|");
		for (int j = 1;j <= 7;j++) {
			if (board[j][i] == 0) printf("  |");
			else if (board[j][i] == 1) printf("��|");
			else printf("��|");
		}
		printf("\n");
	}
	printf(" ");
	for (int i = 1;i <= 7;i++) printf(" %d ", i);
	printf("\n\n");
}

void put_piece(int x, bool num) {
	board[x][++len[x]] = num?1:2;
}

void deput_piece(int x) {
	board[x][len[x]--] = 0;
}

int get_unlimit_length_connected(int x, int i) {
	int cnt = 1;
	for (int j = -1;j >= -3;j--) {
		int target_x = x + dx[i] * j, target_y = len[x] + dy[i] * j;
		if (target_x < 1 || target_x>7 || target_y < 1 || target_y>7) break;
		if (board[target_x][target_y] != 0 && board[target_x][target_y] != board[x][len[x]]) break;
		cnt++;
	}
	for (int j = 1;j <= 3;j++) {
		int target_x = x + dx[i] * j, target_y = len[x] + dy[i] * j;
		if (target_x < 1 || target_x>7 || target_y < 1 || target_y>7) break;
		if (board[target_x][target_y] != 0 && board[target_x][target_y] != board[x][len[x]]) break;
		cnt++;
	}
	return cnt;
}

int get_overflow_length_connected(int x, int i) {
	int cnt = 1;
	bool flag = false;
	for (int j = -1;j >= -3;j--) {
		int target_x = x + dx[i] * j, target_y = len[x] + dy[i] * j;
		if (target_x < 1 || target_x>7 || target_y < 1 || target_y>7) break;
		if (board[target_x][target_y] == 0 && !flag) {
			flag = true;
			cnt++;
		}
		else if (board[target_x][target_y] == board[x][len[x]]) cnt++;
		else break;
	}
	flag = false;
	for (int j = 1;j <= 3;j++) {
		int target_x = x + dx[i] * j, target_y = len[x] + dy[i] * j;
		if (target_x < 1 || target_x>7 || target_y < 1 || target_y>7) break;
		if (board[target_x][target_y] == 0 && !flag) {
			flag = true;
			cnt++;
		}
		else if (board[target_x][target_y] == board[x][len[x]]) cnt++;
		else break;
	}
	return cnt;
}

int get_current_length_connected(int x, int i) {
	int cnt = 1;
	for (int j = -1;j >= -3;j--) {
		int target_x = x + dx[i] * j, target_y = len[x] + dy[i] * j;
		if (target_x < 1 || target_x>7 || target_y < 1 || target_y>7 || board[target_x][target_y] != board[x][len[x]]) break;
		cnt++;
	}
	for (int j = 1;j <= 3;j++) {
		int target_x = x + dx[i] * j, target_y = len[x] + dy[i] * j;
		if (target_x < 1 || target_x>7 || target_y < 1 || target_y>7 || board[target_x][target_y] != board[x][len[x]]) break;
		cnt++;
	}
	return cnt;
}

int get_max_length_connected(int x) {
	int maxv = 0;
	for (int i = 0;i < 4;i++) {
		int result = get_current_length_connected(x, i);
		if (maxv < result) maxv = result;
	}
	return maxv;
}

void game_over(int winner) {

	printf("���� ����\n\n");
	print_board();

	if (winner == 1) printf("�� �¸�!");
	else printf("�� �¸�!");
}

int main() {
	int is_first, placeholder;
	printf("���� ���� (����: 1, �İ�: 2) : ");
	scanf("%d", &is_first);

	system("cls");
	if (is_first == 1) {
		printf("\n\n");
		print_board();
		printf("�� ���� ���� ���� �˰��� (Heuristic: 1, RuleBase: 2) : ");
		scanf("%d", &placeholder);

		/* �����̸� ������ 5�� ���� ������ */

		put_piece(5, true);
		system("cls");

		printf("������ ���� ��ġ : 5\n\n");

		/* logging */

		log[turn][0] = 1;
		log[turn++][1] = 5;
	}
	else printf("\n\n");

	while (true) {
		int position;

		/* print basic information */

		print_board();
		printf("�� ��� ���� ���� ��ġ(1~7) : ");
		scanf("%d", &position);
		if (position < 1 || position>7 || len[position] >= 7) {
			system("cls");
			printf("�߸��� ��ġ�� �Է�\n\n");
			continue;
		}

		put_piece(position, false);
		system("cls");

		/* logging */

		log[turn][0] = 2;
		log[turn++][1] = position;

		/* Discriminate that the game is end */

		if (get_max_length_connected(position) >= 4) {
			game_over(2);
			return 0;
		}

		/* print basic information */

		printf("������ ���� ��ġ : %d\n", position);
		printf("\n");
		print_board();

		int algorithm;
		printf("�� ���� ���� ���� �˰��� (Heuristic: 1, RuleBase: 2) : ");
		scanf("%d", &algorithm);


		position = get_position_by_rulebase2();
		// if (algorithm == 1) position = get_position_by_heuristic();
		// else position = get_position_by_rulebase();

		put_piece(position, true);
		system("cls");

		/* logging */

		log[turn][0] = 1;
		log[turn++][1] = position;

		/* Discriminate that the game is end */

		if (get_max_length_connected(position) >= 4) {
			game_over(2);
			return 0;
		}

		/* print basic information */

		printf("������ ���� ��ġ : %d\n\n", position);

	}
	Sleep(3000);
}