#pragma once

const int SIZE = 8;						//������ ������ ����� � �����
const int FIELD_SIZE = 50;				// ������ ���� � ��������
const int BOARD_SIZE = 400;				// ������ ����� � ��������

class Field
{
public:
	bool isFree = true;
	bool isBusyBlack = false;
	bool isBusyWhite = false;
};

