#include "cstdlib"
#include "aim_board.h"
#include "math.h"

Ball::Ball()
{
	x = BallMaxSize + rand() % (ScrSize - 2*BallMaxSize);
	y = BallMaxSize + rand() % (ScrSize - 2*BallMaxSize);
}

int Ball::step_into()
{
	if (is_growing) size += GrowthSpeed;
	else size -= GrowthSpeed;

	if (size == BallMaxSize) is_growing = false;

	return size;
}

inline bool Ball::is_inside(int _x, int _y)
{
	return pow(x - _x, 2) + pow(y - _y, 2) <= pow(size, 2);
}

void Ball::operator=(const Ball &other)
{
	x = other.x;
	y = other.y;
	is_growing = other.is_growing;
	size = other.size;
}

void AimBoard::step_into()
{
	if (time_to_new_ball == 0) {
		Ball new_ball;
		balls.push_back(new_ball);
		time_to_new_ball = MaxTime;
	}

	for (auto ball = balls.begin(); ball != balls.end();) {
		if (ball->step_into() == 0) {
			ball = balls.erase(ball);
			score -= 500;
		}
		else ball++;
	}

	time_to_new_ball--;
}

void AimBoard::react_to_mouse(int mouse_x, int mouse_y)
{
	for (auto ball = balls.begin(); ball != balls.end();) {
		if (ball->is_inside(mouse_x, mouse_y)) {
			ball = balls.erase(ball);
			score += 300;
			return;
		}
		else ball++;
	}

	score -= 100;
}

void AimBoard::reset()
{
	time_to_new_ball = 0;
	score = 0;
	balls.clear();
}
