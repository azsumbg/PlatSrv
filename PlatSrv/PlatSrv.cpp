#include "pch.h"
#include "platSrv.h"

// EXCEPTION class *********************************

dll::EXCEPTION::EXCEPTION(int what)
{
	_type = what;
}

const wchar_t* dll::EXCEPTION::eGet()const
{
	switch (_type)
	{
	case ERR_PTR:
		return L"Error in BAG main pointer !";
		
	case ERR_INDEX:
		return L"Error in index passed to BAG container !";
		
	case ERR_PARAM:
		return L"Error in parameter passed to BAG container !";
		
	case ERR_UNK:
		return L"Unknown error in BAG container !";
	}

	return L"Unknown error in BAG container !";
}

///////////////////////////////////////////////////

//RANDIT class ************************************

dll::RANDIT::RANDIT()
{
	std::random_device rd{};
	std::seed_seq sq{ rd(),rd(), rd(), rd(), rd(), rd(), rd() };

	twister = new std::mt19937(sq);
}
dll::RANDIT::~RANDIT()
{
	delete twister;
}

int dll::RANDIT::operator()(int min, int max)
{
	if (max <= min)return 0;

	std::uniform_int_distribution distrib(min, max);

	return distrib(*twister);
}
float dll::RANDIT::operator()(float min, float max)
{
	if (max <= min)return 0;

	std::uniform_real_distribution<float> distrib(min, max);

	return distrib(*twister);
}

///////////////////////////////////////////////////

// PROTON class ***********************************

dll::PROTON::PROTON()
{
	start.x = 0;
	start.y = 0;

	_width = 1.0f;
	_height = 1.0f;

	end.x = start.x + _width;
	end.y = start.y + _height;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	_rect.left = start.x;
	_rect.right = end.x;
	_rect.top = start.y;
	_rect.bottom = end.y;
}
dll::PROTON::PROTON(float sx, float sy)
{
	start.x = sx;
	start.y = sy;

	_width = 1.0f;
	_height = 1.0f;

	end.x = start.x + _width;
	end.y = start.y + _height;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	_rect.left = start.x;
	_rect.right = end.x;
	_rect.top = start.y;
	_rect.bottom = end.y;
}
dll::PROTON::PROTON(float sx, float sy, float first_width, float first_height)
{
	start.x = sx;
	start.y = sy;

	_width = first_width;
	_height = first_height;

	end.x = start.x + _width;
	end.y = start.y + _height;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	_rect.left = start.x;
	_rect.right = end.x;
	_rect.top = start.y;
	_rect.bottom = end.y;
}
dll::PROTON::PROTON(D2D1_POINT_2F start_point, float first_width, float first_height)
{
	start = start_point;
	
	_width = first_width;
	_height = first_height;

	end.x = start.x + _width;
	end.y = start.y + _height;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	_rect.left = start.x;
	_rect.right = end.x;
	_rect.top = start.y;
	_rect.bottom = end.y;
}

float dll::PROTON::get_width()const
{
	return _width;
}
float dll::PROTON::get_height()const
{
	return _height;
}

D2D1_RECT_F dll::PROTON::get_rect()const
{
	return _rect;
}

void dll::PROTON::new_width(float new_width)
{
	_width = new_width;
	
	end.x = start.x + _width;
	
	x_rad = _width / 2.0f;
	
	center.x = start.x + x_rad;
	
	_rect.left = start.x;
	_rect.right = end.x;
}
void dll::PROTON::new_height(float new_height)
{
	_height = new_height;

	end.y = start.y + _height;

	y_rad = _height / 2.0f;

	center.y = start.y + y_rad;

	_rect.top = start.y;
	_rect.bottom = end.y;
}
void dll::PROTON::new_dims(float new_width, float new_height)
{
	_width = new_width;
	_height = new_height;

	end.x = start.x + _width;
	end.y = start.y + _height;

	x_rad = _width / 2.0f;
	y_rad = _height / 2.0f;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	_rect.left = start.x;
	_rect.right = end.x;
	_rect.top = start.y;
	_rect.bottom = end.y;
}

void dll::PROTON::set_edges()
{
	
	end.x = start.x + _width;
	end.y = start.y + _height;

	center.x = start.x + x_rad;
	center.y = start.y + y_rad;

	_rect.left = start.x;
	_rect.right = end.x;
	_rect.top = start.y;
	_rect.bottom = end.y;
}

///////////////////////////////////////////////////

// FIELD class ************************************

dll::FIELD::FIELD()
{
	float tx = -50.0f;
	float ty = 0;

	for (int row = 0; row < MAX_FIELD_ROWS; ++row)
	{
		for (int col = 0; row < MAX_FIELD_COLS; ++col)
		{
			FieldArray[row][col].rect.left = tx;
			FieldArray[row][col].rect.top = ty;
			FieldArray[row][col].rect.right = tx + 50.0f;
			FieldArray[row][col].rect.bottom = ty + 50.0f;

			FieldArray[row][col].type = static_cast<tiles>(randerer(0, 4));

			switch (FieldArray[row][col].type)
			{
			case tiles::dirt:
				FieldArray[row][col].delay = 0.2f;
				break;

			case tiles::grass_blue: 
				FieldArray[row][col].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[row][col].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[row][col].delay = 0.3f;
				break;
			}

			tx += 49.0f;
		}

		ty += 49.0f;
	}
}

void dll::FIELD::add_tiles(dirs towhere)
{
	switch (towhere)
	{
	case dirs::up:
		for (int row = MAX_FIELD_ROWS - 1; row > 0; --row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col] = FieldArray[row - 1][col];
			}
		}
		for (int col = 0; col < MAX_FIELD_COLS; ++col)
		{
			FieldArray[0][col].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[0][col].rect.left = FieldArray[1][col].rect.left;
			FieldArray[0][col].rect.right = FieldArray[1][col].rect.right;
			FieldArray[0][col].rect.top = FieldArray[1][col].rect.top - 50.0f;
			FieldArray[0][col].rect.bottom = FieldArray[1][col].rect.top;

			switch (FieldArray[0][col].type)
			{
			case tiles::dirt:
				FieldArray[0][col].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[0][col].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[0][col].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[0][col].delay = 0.3f;
				break;
			}
		}
		break;

	case dirs::down:
		for (int row = 0; row < MAX_FIELD_ROWS - 1; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col] = FieldArray[row + 1][col];
			}
		}
		for (int col = 0; col < MAX_FIELD_COLS; ++col)
		{
			FieldArray[MAX_FIELD_ROWS - 1][col].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[MAX_FIELD_ROWS - 1][col].rect.left = FieldArray[MAX_FIELD_ROWS - 2][col].rect.left;
			FieldArray[MAX_FIELD_ROWS - 1][col].rect.right = FieldArray[MAX_FIELD_ROWS - 2][col].rect.right;
			FieldArray[MAX_FIELD_ROWS - 1][col].rect.top = FieldArray[MAX_FIELD_ROWS - 2][col].rect.top - 50.0f;
			FieldArray[MAX_FIELD_ROWS - 1][col].rect.bottom = FieldArray[MAX_FIELD_ROWS - 2][col].rect.top;

			switch (FieldArray[MAX_FIELD_ROWS - 1][col].type)
			{
			case tiles::dirt:
				FieldArray[0][col].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[0][col].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[0][col].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[0][col].delay = 0.3f;
				break;
			}
		}
		break;

	case dirs::left:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = MAX_FIELD_COLS - 1; col > 0; --col)
			{
				FieldArray[row][col] = FieldArray[row][col - 1];
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			FieldArray[row][0].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[row][0].rect.left = FieldArray[row][1].rect.left - 50.0f;
			FieldArray[row][0].rect.right = FieldArray[row][1].rect.left;
			FieldArray[row][0].rect.top = FieldArray[row][1].rect.top;
			FieldArray[row][0].rect.bottom = FieldArray[row][1].rect.bottom;

			switch (FieldArray[row][0].type)
			{
			case tiles::dirt:
				FieldArray[row][0].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[row][0].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[row][0].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[row][0].delay = 0.3f;
				break;
			}
		}
		break;

	case dirs::right:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS - 1; ++col)
			{
				FieldArray[row][col] = FieldArray[row][col + 1];
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			FieldArray[row][MAX_FIELD_COLS - 1].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[row][MAX_FIELD_COLS - 1].rect.left = FieldArray[row][1].rect.left - 50.0f;
			FieldArray[row][MAX_FIELD_COLS - 1].rect.right = FieldArray[row][1].rect.left;
			FieldArray[row][MAX_FIELD_COLS - 1].rect.top = FieldArray[row][1].rect.top;
			FieldArray[row][MAX_FIELD_COLS - 1].rect.bottom = FieldArray[row][1].rect.bottom;

			switch (FieldArray[row][MAX_FIELD_COLS - 1].type)
			{
			case tiles::dirt:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.3f;
				break;
			}
		}
		break;

	case dirs::up_left:
		for (int row = MAX_FIELD_ROWS - 1; row > 0; --row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col] = FieldArray[row - 1][col];
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = MAX_FIELD_COLS - 1; col > 0; --col)
			{
				FieldArray[row][col] = FieldArray[row][col - 1];
			}
		}
		for (int col = 0; col < MAX_FIELD_COLS; ++col)
		{
			FieldArray[0][col].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[0][col].rect.left = FieldArray[1][col].rect.left;
			FieldArray[0][col].rect.right = FieldArray[1][col].rect.right;
			FieldArray[0][col].rect.top = FieldArray[1][col].rect.top - 50.0f;
			FieldArray[0][col].rect.bottom = FieldArray[1][col].rect.top;

			switch (FieldArray[0][col].type)
			{
			case tiles::dirt:
				FieldArray[0][col].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[0][col].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[0][col].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[0][col].delay = 0.3f;
				break;
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			FieldArray[row][0].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[row][0].rect.left = FieldArray[row][1].rect.left - 50.0f;
			FieldArray[row][0].rect.right = FieldArray[row][1].rect.left;
			FieldArray[row][0].rect.top = FieldArray[row][1].rect.top;
			FieldArray[row][0].rect.bottom = FieldArray[row][1].rect.bottom;

			switch (FieldArray[row][0].type)
			{
			case tiles::dirt:
				FieldArray[row][0].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[row][0].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[row][0].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[row][0].delay = 0.3f;
				break;
			}
		}
		break;

	case dirs::up_right:
		for (int row = MAX_FIELD_ROWS - 1; row > 0; --row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col] = FieldArray[row - 1][col];
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS - 1; ++col)
			{
				FieldArray[row][col] = FieldArray[row][col + 1];
			}
		}
		for (int col = 0; col < MAX_FIELD_COLS; ++col)
		{
			FieldArray[0][col].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[0][col].rect.left = FieldArray[1][col].rect.left;
			FieldArray[0][col].rect.right = FieldArray[1][col].rect.right;
			FieldArray[0][col].rect.top = FieldArray[1][col].rect.top - 50.0f;
			FieldArray[0][col].rect.bottom = FieldArray[1][col].rect.top;

			switch (FieldArray[0][col].type)
			{
			case tiles::dirt:
				FieldArray[0][col].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[0][col].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[0][col].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[0][col].delay = 0.3f;
				break;
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			FieldArray[row][MAX_FIELD_COLS - 1].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[row][MAX_FIELD_COLS - 1].rect.left = FieldArray[row][1].rect.left - 50.0f;
			FieldArray[row][MAX_FIELD_COLS - 1].rect.right = FieldArray[row][1].rect.left;
			FieldArray[row][MAX_FIELD_COLS - 1].rect.top = FieldArray[row][1].rect.top;
			FieldArray[row][MAX_FIELD_COLS - 1].rect.bottom = FieldArray[row][1].rect.bottom;

			switch (FieldArray[row][MAX_FIELD_COLS - 1].type)
			{
			case tiles::dirt:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.3f;
				break;
			}
		}
		break;

	case dirs::down_left:
		for (int row = 0; row < MAX_FIELD_ROWS - 1; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col] = FieldArray[row + 1][col];
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = MAX_FIELD_COLS - 1; col > 0; --col)
			{
				FieldArray[row][col] = FieldArray[row][col - 1];
			}
		}
		for (int col = 0; col < MAX_FIELD_COLS; ++col)
		{
			FieldArray[MAX_FIELD_ROWS - 1][col].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[MAX_FIELD_ROWS - 1][col].rect.left = FieldArray[MAX_FIELD_ROWS - 2][col].rect.left;
			FieldArray[MAX_FIELD_ROWS - 1][col].rect.right = FieldArray[MAX_FIELD_ROWS - 2][col].rect.right;
			FieldArray[MAX_FIELD_ROWS - 1][col].rect.top = FieldArray[MAX_FIELD_ROWS - 2][col].rect.top - 50.0f;
			FieldArray[MAX_FIELD_ROWS - 1][col].rect.bottom = FieldArray[MAX_FIELD_ROWS - 2][col].rect.top;

			switch (FieldArray[MAX_FIELD_ROWS - 1][col].type)
			{
			case tiles::dirt:
				FieldArray[0][col].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[0][col].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[0][col].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[0][col].delay = 0.3f;
				break;
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			FieldArray[row][0].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[row][0].rect.left = FieldArray[row][1].rect.left - 50.0f;
			FieldArray[row][0].rect.right = FieldArray[row][1].rect.left;
			FieldArray[row][0].rect.top = FieldArray[row][1].rect.top;
			FieldArray[row][0].rect.bottom = FieldArray[row][1].rect.bottom;

			switch (FieldArray[row][0].type)
			{
			case tiles::dirt:
				FieldArray[row][0].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[row][0].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[row][0].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[row][0].delay = 0.3f;
				break;
			}
		}
		break;

	case dirs::down_right:
		for (int row = 0; row < MAX_FIELD_ROWS - 1; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col] = FieldArray[row + 1][col];
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS - 1; ++col)
			{
				FieldArray[row][col] = FieldArray[row][col + 1];
			}
		}
		for (int col = 0; col < MAX_FIELD_COLS; ++col)
		{
			FieldArray[MAX_FIELD_ROWS - 1][col].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[MAX_FIELD_ROWS - 1][col].rect.left = FieldArray[MAX_FIELD_ROWS - 2][col].rect.left;
			FieldArray[MAX_FIELD_ROWS - 1][col].rect.right = FieldArray[MAX_FIELD_ROWS - 2][col].rect.right;
			FieldArray[MAX_FIELD_ROWS - 1][col].rect.top = FieldArray[MAX_FIELD_ROWS - 2][col].rect.top - 50.0f;
			FieldArray[MAX_FIELD_ROWS - 1][col].rect.bottom = FieldArray[MAX_FIELD_ROWS - 2][col].rect.top;

			switch (FieldArray[MAX_FIELD_ROWS - 1][col].type)
			{
			case tiles::dirt:
				FieldArray[0][col].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[0][col].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[0][col].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[0][col].delay = 0.3f;
				break;
			}
		}
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			FieldArray[row][MAX_FIELD_COLS - 1].type = static_cast<tiles>(randerer(0, 4));

			FieldArray[row][MAX_FIELD_COLS - 1].rect.left = FieldArray[row][1].rect.left - 50.0f;
			FieldArray[row][MAX_FIELD_COLS - 1].rect.right = FieldArray[row][1].rect.left;
			FieldArray[row][MAX_FIELD_COLS - 1].rect.top = FieldArray[row][1].rect.top;
			FieldArray[row][MAX_FIELD_COLS - 1].rect.bottom = FieldArray[row][1].rect.bottom;

			switch (FieldArray[row][MAX_FIELD_COLS - 1].type)
			{
			case tiles::dirt:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.2f;
				break;

			case tiles::grass_blue:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.25f;
				break;

			case tiles::grass_red:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.26f;
				break;

			case tiles::grass_dirt:
				FieldArray[row][MAX_FIELD_COLS - 1].delay = 0.3f;
				break;
			}
		}
		break;
	}
}

void dll::FIELD::move(float gear, dirs dir)
{
	float my_speed = _speed + gear / 5.0f;

	bool need_up{ false };
	bool need_down{ false };
	bool need_left{ false };
	bool need_right{ false };

	switch (dir)
	{
	case dirs::up:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col].rect.top -= my_speed;
				FieldArray[row][col].rect.bottom -= my_speed;
			}
		}
		if (FieldArray[0][0].rect.top <= 0)add_tiles(dirs::down);
		break;

	case dirs::down:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col].rect.top += my_speed;
				FieldArray[row][col].rect.bottom += my_speed;
			}
		}
		if (FieldArray[MAX_FIELD_ROWS - 1][0].rect.top >= scr_height)add_tiles(dirs::up);
		break;

	case dirs::left:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col].rect.left -= my_speed;
				FieldArray[row][col].rect.right -= my_speed;
			}
		}
		if (FieldArray[0][0].rect.right <= -50.0f)add_tiles(dirs::right);
		break;

	case dirs::right:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col].rect.left += my_speed;
				FieldArray[row][col].rect.right += my_speed;
			}
		}
		if (FieldArray[0][MAX_FIELD_COLS - 1].rect.left >= scr_width + 50.0f)add_tiles(dirs::left);
		break;

	case dirs::up_left:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col].rect.top -= my_speed;
				FieldArray[row][col].rect.bottom -= my_speed;
				FieldArray[row][col].rect.left -= my_speed;
				FieldArray[row][col].rect.right -= my_speed;
			}
		}
		if (FieldArray[0][0].rect.top <= 0)need_down = true;
		if (FieldArray[0][0].rect.right <= -50.0f)need_right = true;
		if (need_down && need_right)add_tiles(dirs::down_right);
		else if (need_down)add_tiles(dirs::down);
		else if (need_right)add_tiles(dirs::right);
		break;

	case dirs::up_right:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col].rect.top -= my_speed;
				FieldArray[row][col].rect.bottom -= my_speed;
				FieldArray[row][col].rect.left += my_speed;
				FieldArray[row][col].rect.right += my_speed;
			}
		}
		if (FieldArray[0][0].rect.top <= 0)need_down = true;
		if (FieldArray[0][MAX_FIELD_COLS - 1].rect.left >= scr_width + 50.0f)need_left = true;
		if (need_down && need_left)add_tiles(dirs::down_left);
		else if (need_down)add_tiles(dirs::down);
		else if (need_left)add_tiles(dirs::left);
		break;
		
	case dirs::down_left:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col].rect.top += my_speed;
				FieldArray[row][col].rect.bottom += my_speed;
				FieldArray[row][col].rect.left -= my_speed;
				FieldArray[row][col].rect.right -= my_speed;
			}
		}
		if (FieldArray[MAX_FIELD_ROWS - 1][0].rect.top >= scr_height)need_up = true;
		if (FieldArray[0][0].rect.right <= -50.0f)need_right = true;
		if (need_up && need_right)add_tiles(dirs::up_right);
		else if (need_up)add_tiles(dirs::up);
		else if (need_right)add_tiles(dirs::right);
		break;

	case dirs::down_right:
		for (int row = 0; row < MAX_FIELD_ROWS; ++row)
		{
			for (int col = 0; col < MAX_FIELD_COLS; ++col)
			{
				FieldArray[row][col].rect.top += my_speed;
				FieldArray[row][col].rect.bottom += my_speed;
				FieldArray[row][col].rect.left += my_speed;
				FieldArray[row][col].rect.right += my_speed;
			}
		}
		if (FieldArray[MAX_FIELD_ROWS - 1][0].rect.top >= scr_height)need_up = true;
		if (FieldArray[0][MAX_FIELD_COLS - 1].rect.left >= scr_width + 50.0f)need_left = true;
		if (need_up && need_left)add_tiles(dirs::up_left);
		else if (need_up)add_tiles(dirs::up);
		else if (need_left)add_tiles(dirs::left);
		break;
	}

}

dll::TILE dll::FIELD::get_tile(int row, int col) const
{
	return FieldArray[row][col];
}

dll::GRID_COORD dll::FIELD::get_coord(float x, float y) const
{
	GRID_COORD ret{ -1, -1 };

	for (int row = 0; row < MAX_FIELD_ROWS; ++row)
	{
		for (int col = 0; col < MAX_FIELD_COLS; ++col)
		{
			if (x >= FieldArray[row][col].rect.left && x <= FieldArray[row][col].rect.right)ret.col = col;
			if (y >= FieldArray[row][col].rect.top && y <= FieldArray[row][col].rect.bottom)ret.row = row;
		
			if (ret.col != -1 && ret.row != -1)break;
		}
	}

	return ret;
}
dll::GRID_COORD dll::FIELD::get_coord(D2D1_POINT_2F point) const
{
	GRID_COORD ret{ -1, -1 };

	for (int row = 0; row < MAX_FIELD_ROWS; ++row)
	{
		for (int col = 0; col < MAX_FIELD_COLS; ++col)
		{
			if (point.x >= FieldArray[row][col].rect.left && point.x <= FieldArray[row][col].rect.right)ret.col = col;
			if (point.y >= FieldArray[row][col].rect.top && point.y <= FieldArray[row][col].rect.bottom)ret.row = row;

			if (ret.col != -1 && ret.row != -1)break;
		}
	}

	return ret;
}

///////////////////////////////////////////////////

// HERO class ************************************

dll::HERO::HERO(float _sx, float _sy) :PROTON{ _sx,_sy, 85.0f, 80.0f } {};
void dll::HERO::set_path(float targ_x, float targ_y)
{
	move_sx = start.x;
	move_sy = start.y;
	move_ex = targ_x;
	move_ey = targ_y;

	hor_dir = false;
	ver_dir = false;

	if (move_sx == move_ex || (move_ex > move_sx && move_ex <= end.x))
	{
		ver_dir = true;
		return;
	}
	if (move_sy == move_ey || (move_ey > move_sy && move_ey <= end.y))
	{
		hor_dir = true;
		return;
	}

	slope = (move_ey - move_sy) / (move_ex - move_sx);
	intercept = start.y - slope * start.x;
}

float dll::HERO::get_target_x()const
{
	return move_ex;
}
float dll::HERO::get_target_y()const
{
	return move_ey;
}

int dll::HERO::get_frame()
{
	--frame_delay;
	if (frame_delay <= 0)
	{
		frame_delay = max_frame_delay;
		++frame;
		if (frame > max_frames)frame = 0;
	}

	return frame;
}

void dll::HERO::move(float gear)
{
	float my_speed = _speed + gear / 10.0f;

	if (hor_dir)
	{
		if (move_sx > move_ex)
		{
			if (start.x - my_speed >= 0)
			{
				start.x -= my_speed;
				set_edges();
			}
			if (start.x < 0)
			{
				start.x = 0;
				set_edges();
			}
		}
		else if (move_sx < move_ex)
		{
			if (end.x + my_speed <= scr_width)
			{
				start.x += my_speed;
				set_edges();
			}
			if (end.x > scr_width)
			{
				end.x = scr_width;
				start.x = end.x - _width;
				set_edges();
			}
		}
	}
	else if (ver_dir)
	{
		if (move_sy > move_ey)
		{
			if (start.y - my_speed >= sky)
			{
				start.y -= my_speed;
				set_edges();
			}
			if (start.y < sky)
			{
				start.y = sky;
				set_edges();
			}
		}
		else if (move_sy < move_ey)
		{
			if (end.y + my_speed <= ground)
			{
				start.y += my_speed;
				set_edges();
			}
			if (end.y > ground)
			{
				end.y = ground;
				start.y = end.y - _height;
				set_edges();
			}
		}
	}
	else
	{
		if (move_sx > move_ex)
		{
			if (start.x - my_speed >= 0)
			{
				start.x -= my_speed;
				start.y = start.x * slope + intercept;
				set_edges();
			}
			if (start.x < 0)
			{
				start.x = 0;
				set_edges();
			}
		}
		else if (move_sx < move_ex)
		{
			if (end.x + my_speed <= scr_width)
			{
				start.x += my_speed;
				start.y = start.x * slope + intercept;
				set_edges();
			}
			if (end.x > scr_width)
			{
				end.x = scr_width;
				start.x = end.x - _width;
				set_edges();
			}
		}

		if (start.y < sky)
		{
			start.y = sky;
			set_edges();
		}
		if (end.y > ground)
		{
			end.y = ground;
			start.y = end.y - _height;
			set_edges();
		}
	}
}

void dll::HERO::set_view_angle()
{
	float oppos = abs(move_ex - move_sx);
	float adj = abs(move_ey - move_sy);

	float ret = static_cast<float>(atan2(oppos, adj) * 180.0f / 3.14f);

	if (move_ey < move_sy)
	{
		if (ver_dir)ret = 0;
		else if (move_ex > move_sx)ret = 90.0f - ret;
		else if (move_ex < move_sx)ret = ret + 270.0f;
	}
	else if (move_ey > move_sy)
	{
		if (ver_dir)ret = 180.0f;
		else if (move_ex > move_sx)ret = 90.0f + ret;
		else if (move_ex < move_sx)ret = 180.0f - ret;
	}
	else
	{
		if (move_sx >= move_ex)ret = 90.0f;
		else ret = 270.0f;
	}

}

void dll::HERO::Release()
{
	delete this;
}

dll::HERO* dll::HERO::create(float sx, float sy)
{
	return new HERO(sx, sy);
}

//////////////////////////////////////////////////

// SHOT class ***********************************

dll::SHOT::SHOT(float _sx, float _sy, float _ex, float _ey) :PROTON(_sx, _sy, 6.0f, 10.0f)
{
	move_sx = start.x;
	move_sy = start.y;
	move_ex = _ex;
	move_ey = _ex;

	hor_dir = false;
	ver_dir = false;

	if (move_sx == move_ex || (move_ex > move_sx && move_ex <= end.x))
	{
		ver_dir = true;
		return;
	}
	if (move_sy == move_ey || (move_ey > move_sy && move_ey <= end.y))
	{
		hor_dir = true;
		return;
	}

	slope = (move_ey - move_sy) / (move_ex - move_sx);
	intercept = start.y - slope * start.x;
}

bool dll::SHOT::move(float gear)
{
	float my_speed = speed + gear / 10.0f;

	if (hor_dir)
	{
		if (move_sx > move_ex)
		{
			if (start.x - my_speed >= 0)
			{
				start.x -= my_speed;
				set_edges();
			}
			else return false;
		}
		else if (move_sx < move_ex)
		{
			if (end.x + my_speed <= scr_width)
			{
				start.x += my_speed;
				set_edges();
			}
			else return false;
		}
		else return false;
	}
	else if (ver_dir)
	{
		if (move_sy > move_ey)
		{
			if (start.y - my_speed >= sky)
			{
				start.y -= my_speed;
				set_edges();
			}
			else return false;
		}
		else if (move_sy < move_ey)
		{
			if (end.y + my_speed <= ground)
			{
				start.y += my_speed;
				set_edges();
			}
			else return false;
		}
		else return false;
	}
	else
	{
		if (move_sx > move_ex)
		{
			if (start.x - my_speed >= 0)
			{
				start.x -= my_speed;
				start.y = start.x * slope + intercept;
				set_edges();
			}
			else return false;
		}
		else if (move_sx < move_ex)
		{
			if (end.x + my_speed <= scr_width)
			{
				start.x += my_speed;
				start.y = start.x * slope + intercept;
				set_edges();
			}
			else return false;
		}
		else return false;
	}

	if (start.x <= 0 || end.x >= scr_width || start.y <= sky || end.y >= ground)return false;

	return true;
}

void dll::SHOT::Release()
{
	delete this;
}

dll::SHOT* dll::SHOT::create(float sx, float sy, float ex, float ey)
{
	return new SHOT(sx, sy, ex, ey);
}

/////////////////////////////////////////////////

// OBSTACLES class ******************************

dll::OBSTACLE::OBSTACLE(obstacles _type, float _sx, float _sy) :PROTON(_sx, _sy, 32.0f, 32.0f)
{
	type = _type;
	
	if (type == obstacles::rock)new_dims(100.0f, 100.0f);
}
	
bool dll::OBSTACLE::move(float gear, dirs dir)
{
	float my_speed = _speed + gear / 5.0f;

	switch (dir)
	{
	case dirs::up:
		start.y -= my_speed;
		set_edges();
		if (end.y <= 0)return false;
		break;

	case dirs::down:
		start.y += my_speed;
		set_edges();
		if (start.y >= scr_height)return false;
		break;

	case dirs::left:
		start.x -= my_speed;
		set_edges();
		if (end.x <= -50.0f)return false;
		break;

	case dirs::right:
		start.x += my_speed;
		set_edges();
		if (start.x >= scr_height + 50.0f)return false;
		break;

	case dirs::up_left:
		start.y -= my_speed;
		start.x -= my_speed;
		set_edges();
		if (end.x <= -50.0f || end.y <= 0)return false;
		break;

	case dirs::up_right:
		start.y -= my_speed;
		start.x += my_speed;
		set_edges();
		if (start.x >= scr_height + 50.0f || end.y <= 0)return false;
		break;

	case dirs::down_left:
		start.y += my_speed;
		start.x -= my_speed;
		set_edges();
		if (end.x <= -50.0f || start.y >= scr_height)return false;
		break;

	case dirs::down_right:
		start.y += my_speed;
		start.x -= my_speed;
		set_edges();
		if (start.x >= scr_height + 50.0f || start.y >= scr_height)return false;
		break;
	}

	return true;
}
void dll::OBSTACLE::Release()
{
	delete this;
}

dll::OBSTACLE* dll::OBSTACLE::create(obstacles my_type, float sx, float sy)
{
	return new OBSTACLE(my_type, sx, sy);
}

/////////////////////////////////////////////////






// FUNCTIONS *******************************

bool dll::Intersect(D2D1_RECT_F first, D2D1_RECT_F second)
{
	if (!(first.left >= second.right || first.right <= second.left
		|| first.top >= second.bottom || first.bottom <= second.top))return true;

	return false;
}
bool dll::Intersect(D2D1_POINT_2F first_center, D2D1_POINT_2F second_center, float first_xrad, float second_xrad,
	float first_yrad, float second_yrad)
{
	if (fabs(second_center.x - first_center.x) <= first_xrad + second_xrad
		&& fabs(second_center.y - first_center.y) <= first_yrad + second_yrad)return true;

	return false;
}

float dll::Distance(D2D1_POINT_2F first, D2D1_POINT_2F second)
{
	float a = ((float)(pow(fabs(second.x - first.x), 2)));
	float b = ((float)(pow(fabs(second.y - first.y), 2)));

	return (float)(sqrt(a + b));
}

void dll::Sort(BAG<D2D1_POINT_2F>& Bag, D2D1_POINT_2F ref)
{
	if (Bag.size() < 2)return;
	else
	{
		bool ok = false;
		
		while (!ok)
		{
			ok = true;

			for (size_t count = 0; count < Bag.size() - 1; ++count)
			{
				if (Distance(Bag[count], ref) > Distance(Bag[count + 1], ref))
				{
					D2D1_POINT_2F temp = Bag[count];
					Bag[count] = Bag[count + 1];
					Bag[count + 1] = Bag[count];
					ok = false;
				}
			}
		}
	}
}

bool dll::Point_on_line(D2D1_POINT_2F start_line, D2D1_POINT_2F end_line, D2D1_POINT_2F check_point)
{
	float start_to_point{ Distance(start_line, check_point) };
	float end_to_point{ Distance(end_line, check_point) };
	float line_lenght{ Distance(start_line,end_line) + LINE_EPSILON };

	return(line_lenght == start_to_point + end_to_point);
}