#pragma once

const int SIZE = 8;						//размер строки доски в полях
const int FIELD_SIZE = 50;				// размер поля в пикселях
const int BOARD_SIZE = 400;				// размер доски в пикселях

class Field
{
public:
	bool isFree = true;
	bool isBusyBlack = false;
	bool isBusyWhite = false;
};

