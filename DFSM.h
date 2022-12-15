#ifndef DFSM_H
#define DFSM_H
#include <vector>
#include <string>
#include "Lexeme.h"
//��� �������
class DFSM {
private:
	//��������� ���
	enum state {
		start,
		end_id,
		end_intnumber,
		state_3,
		state_dot,
		end_realnum
	};
	//��� �������
	enum symbol {
		letter,
		digit,
		dot,
		error
	};
	//������� ��� ������� ���������
	using trans_matrix = std::vector<std::vector<state>>;
	//������� ��������� ���
	trans_matrix matrix;

	//����������� ���������� ���������
	state getState(const state, const symbol) const;
	//���������� ��� ��������������� ��������
	symbol getEvent(const char) const;

public:
	DFSM();
	//���������� ��� �������
	type_lexeme getTypeLex(const std::string) const;
};
#endif // DFSM_H

