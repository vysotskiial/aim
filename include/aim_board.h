#pragma once
#include <iostream>
#include <vector>

using namespace std;

constexpr int MaxTime = 30;
constexpr int ScrSize = 800;
constexpr int BallMaxSize = 30;
constexpr double GrowthSpeed = 0.5;

class Ball
{
private:
	double size = 1;
	bool is_growing = true;
	int x, y;
public:
	Ball();
	int get_x() const { return x; }
	int get_y() const { return y; }
	int step_into();
	inline bool is_inside(int x, int y);
	double get_size() const { return size; }
	void operator = (const Ball &);
};

class AimBoard
{
private:
	vector<Ball> balls;
	int time_to_new_ball = 0;
public:
	int score = 0;
	void step_into();
	const vector<Ball> &get_balls() { return balls; }
	void react_to_mouse(int mouse_x, int mouse_y);
	void reset();
};
