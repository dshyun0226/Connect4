#pragma warning(disable : 4996)

#include<stdio.h>
#include "connect4.h"

int immediate_win(bool flag) {
	for (int i = 0;i < 7;i++) {
		if (len[i] >= 7) continue;
		if (flag) put_my(i);
		else put_opposite(i);
		if (is_win(flag, i)) {
			deput(i);
			return i + 1;
		}
		deput(i);
	}
	return 0;
}

int get_winable_lines(bool flag, int x) {
	int tx = len[x] - 1, ty = x;
	int ans = 0;

	for (int i = 0; i < 4; i++) {
		int cnt = 1;
		for (int j = 1; j < 4; j++) {
			int target_x = tx + dx[i] * j, target_y = ty + dy[i] * j;
			if (target_x < 0 || target_x >= 7 || target_y < 0 || target_y >= 7) break;
			if (flag && board[target_x][target_y] == 'X') break;
			else if (!flag && board[target_x][target_y] == 'O') break;
			else if (cnt++ >= 4) {
				ans++;
				break;
			}
		}
		if (cnt >= 4) continue;
		for (int j = -1; j > -4; j--) {
			int target_x = tx + dx[i] * j, target_y = ty + dy[i] * j;
			if (target_x < 0 || target_x >= 7 || target_y < 0 || target_y >= 7) break;
			if (flag && board[target_x][target_y] == 'X') break;
			else if (!flag && board[target_x][target_y] != 'O') break;
			else if (cnt++ >= 4) {
				ans++;
				break;
			}
		}
	}
	return ans;
}

int reasonable_sum_connect(bool flag, int x) {
	int tx = len[x] - 1, ty = x;
	int res = 0;
	for (int i = 0;i < 4;i++) {
		int cnt = 1;
		for (int j = 1; j < 4; j++) {
			int target_x = tx + dx[i] * j, target_y = ty + dy[i] * j;
			if (target_x < 0 || target_x >= 7 || target_y < 0 || target_y >= 7) break;
			if (flag && board[target_x][target_y] == 'X') break;
			else if (!flag && board[target_x][target_y] == 'O') break;
			cnt++;
		}
		for (int j = -1; j > -4; j--) {
			int target_x = tx + dx[i] * j, target_y = ty + dy[i] * j;
			if (target_x < 0 || target_x >= 7 || target_y < 0 || target_y >= 7) break;
			if (flag && board[target_x][target_y] == 'X') break;
			else if (!flag && board[target_x][target_y] != 'O') break;
			cnt++;
		}

		if(cnt >=4){
			int cnt1 = 1;
			for (int j = 1; j < 4; j++) {
				int target_x = tx + dx[i] * j, target_y = ty + dy[i] * j;
				if (target_x < 0 || target_x >= 7 || target_y < 0 || target_y >= 7) break;
				if (flag && board[target_x][target_y] != 'O') break;
				else if (!flag && board[target_x][target_y] != 'X') break;
				cnt1++;
			}
			for (int j = -1; j > -4; j--) {
				int target_x = tx + dx[i] * j, target_y = ty + dy[i] * j;
				if (target_x < 0 || target_x >= 7 || target_y < 0 || target_y >= 7) break;
				if (flag && board[target_x][target_y] != 'O') break;
				else if (!flag && board[target_x][target_y] != 'X') break;
				cnt1++;
			}
			res += cnt > 4 ? 4 : cnt;
		}
	}
	return res;
}

int rule_base() {
	int score[7] = { 0, };
	if (int result = immediate_win(true)) return result - 1;
	else if (result = immediate_win(false)) return result - 1;
	int maxv = -1, ans = 0, sumv=0;
	for (int i = 0;i < 7;i++) {
		if (len[i] >= 7) continue;

		put_my(i);
		score[i] = get_winable_lines(true, i) + reasonable_sum_connect(true, i);
		if (len[i] < 6) {
			put_opposite(i);
			if (is_win(false, i)) {
				deput(i);
				deput(i);
				score[i] = -1000000;
				continue;
			}
			score[i] -= (get_winable_lines(false, i) + reasonable_sum_connect(false, i))/2;                 //  get_winable_lines(false, i) - reasonable_sum_connect(false, i);   µµ ¼º´ÉÀÌ ±¦Âú°Ô ³ª¿È
			sumv += (get_winable_lines(false, i) + reasonable_sum_connect(false, i))/2;
			deput(i);
		} 
		deput(i);

		put_opposite(i);
		score[i] += get_winable_lines(false, i) + reasonable_sum_connect(false, i);
		deput(i);
	}
	for (int i = 0;i < 7;i++) {
		if (len[i] == 7) continue;
		if (len[i] == 6) score[i] -= sumv / 7;
		if (score[i] > maxv) {
			maxv = score[i];
			ans = i;
		}
	}
	return ans;
}

int main() {
	int pos;
	while (true) {
		pos = input_opposite();
		if (is_win(false, pos)) break;
		pos = rule_base();
		put_my(pos);
		log_my[len_my++] = pos;
		if (is_win(true, pos)) break;
	}
	for (int i = 0;i < len_opposite;i++) printf("%d ", log_opposite[i]);
	for (int i = 0;i < len_my;i++) printf("%d ", log_my[i]);
}