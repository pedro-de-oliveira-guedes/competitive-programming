#include <bits/stdc++.h>

std::vector<int> slots;
std::vector<int> balls;

int get_min_sum(int slots_count, int balls_count) {
	std::vector<std::vector<int>> dp(balls_count, std::vector<int>(slots_count, INT_MAX));
	for (int slot = 1; slot < slots_count; slot++)
		dp[0][slot] = balls[0] * slots[slot-1] + balls[0] * slots[slot];

	for (int ball = 1; ball < balls_count; ball++) {
		int last_ball_sum = INT_MAX;
		// The first ball is already placed in the first slot, occupying the first and second positions
        // So the second ball can only be placed in the third (i = 2) and fourth (i = 3) positions forward
		for (int slot = 3; slot < slots_count; slot++) {
			last_ball_sum = std::min(last_ball_sum, dp[ball-1][slot-2]);

			if (last_ball_sum != INT_MAX) {
				dp[ball][slot] = last_ball_sum + (balls[ball] * slots[slot-1]) + (balls[ball] * slots[slot]);
			}
		}
	}

	return dp[balls_count-1][slots_count-1];
}

void rotate_roulette(int slots_count) {
	int aux_slot = slots[0], aux_slot2;
	for (int i = 1; i < slots_count; i++) {
		aux_slot2 = slots[i];
		slots[i] = aux_slot;
		aux_slot = aux_slot2;
	}
	slots[0] = aux_slot;
}

int main() {
	int slots_count, balls_count;

	while (std::cin >> slots_count >> balls_count && slots_count != 0 && balls_count != 0) {
		slots.clear();
		slots.resize(slots_count);
		for (int i = 0; i < slots_count; ++i) std::cin >> slots[i];

		balls.clear();
		balls.resize(balls_count);
		for (int i = 0; i < balls_count; ++i) std::cin >> balls[i];

		int min_sum = INT_MAX;
		// It is necessary to simulate the placement of the first ball in each slot,
		// that is what the for loop is doing
		for (int i = 0; i < slots_count; i++) {
			int new_sum = get_min_sum(slots_count, balls_count);
			min_sum = std::min(min_sum, new_sum);
			rotate_roulette(slots_count); // The first slot is now the previous last slot
		}

		std::cout << -min_sum << std::endl;
	}
	return 0;
}
