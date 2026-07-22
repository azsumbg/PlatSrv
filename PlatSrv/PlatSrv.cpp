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