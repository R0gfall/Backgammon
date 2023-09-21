#pragma once

#include "Board.h"

#include "IGameStateMachine.h"

//Абстрактный класс игрока
//Содержит общие методы и зависимости
class IPlayer
{
public:
	//Конструктор 
	IPlayer(PlayerOrderType type, IGameStateMachine* stateMachine, Board* board);
	//Виртуальный деструктор, так как класс абстрактный
	virtual ~IPlayer() { }

	//Метод, который вызывается когда ход переходит данному игроку (не все шашки в доме)
	virtual void OnTurnEnter() = 0;
	//Метод, который вызывается когда ход переходит данному игроку (все шашки в доме)
	virtual void OnEndTurnEnter() = 0;
	//Метод, обновления (не все шашки в доме)
	virtual void OnUpdate() {}
	//Метод, обновления (все шашки в доме)
	virtual void OnEndUpdate() {}
	//Метод, который вызывается перед передачей хода следующему игроку
	virtual void OnTurnExit() {}

	virtual void Draw(Window* window);

	//Проверка, сделан ли первый ход
	bool IsFirstTurnMade() { return GameBoard->IsFirstTurnMade(OrderType); }
	//Проверка, находится ли игрок в финальной стадии (все шашки в доме)
	bool IsOnEndStage() { return GameBoard->IsOnEndStage(OrderType); }
	//Проверка, находится ли игрок в финальной стадии (все шашки в доме) 
	bool IsOnEndStage(PlayerOrderType orderType) { return GameBoard->IsOnEndStage(orderType); }

	//Для тестов
	void DebugSetEndStage(bool value);

	//Вызывает метод CalculateCellId через GameBoard (сделано для уменьшения длины строчки кода))
	short CalculateCellId(short fromId, short turnValue);

	//Возвращает возможные ходы для данного игрока
	PossibleTurns CalculatePossibleTurns();
	PossibleTurns CalculatePossibleTurns(bool shouldLog);
	//Проверка, есть ли возможные ходы
	bool IsAnyTurnsPossible();
	bool IsAnyTurnsPossible(bool shouldLog);

	//Вызывает метод GetChecksOut через GameBoard (сделано для уменьшения длины строчки кода))
	char GetChecksOut() { return GameBoard->GetChecksOut(OrderType); }

protected:
	//Метод передачи хода следующему игроку или завершения игры
	void NextTurn();

	//Указатель на доску
	Board* GameBoard;
	//Очередность хода данного игрока
	PlayerOrderType OrderType;
	//Указатель на интерфейс машины состояний
	IGameStateMachine* StateMachine;

private:
	//Обновление текста сброшенных шашек со стола
	void UpdateChecksOutText();

	sf::Font _font;
	sf::Text _checksOutText;
};

