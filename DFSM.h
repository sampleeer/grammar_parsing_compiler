#ifndef DFSM_H
#define DFSM_H
#include <vector>
#include <string>
#include "Lexeme.h"
//Тип лексемы
class DFSM {
private:
	//Состояния ДКА
	enum state {
		start,
		end_id,
		end_intnumber,
		state_3,
		state_dot,
		end_realnum
	};
	//Тип символа
	enum symbol {
		letter,
		digit,
		dot,
		error
	};
	//Обертка для матрицы переходов
	using trans_matrix = std::vector<std::vector<state>>;
	//Матрица переходов дка
	trans_matrix matrix;

	//Определение следующего состояния
	state getState(const state, const symbol) const;
	//Возвращает тип обрабатываемого значения
	symbol getEvent(const char) const;

public:
	DFSM();
	//Возвращает тип лексемы
	type_lexeme getTypeLex(const std::string) const;
};
#endif // DFSM_H

