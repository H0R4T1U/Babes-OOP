#pragma once
#include "Disciplina.h"
#include "../Repository/Repo.h"

class UndoAction
{
public:
	// metoda pur virtuala pentru executarea operatiei de undo
	virtual void doUndo() = 0;

	// destructorul clasei
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction
{
	// masina adaugata
	Disciplina addedDisciplina;

	// repository-ul de masini
	AbstractRepo& repo;

public:
	// constructorul clasei
	UndoAdd(AbstractRepo& repo, const  Disciplina& d) : repo{ repo }, addedDisciplina{ d } {}

	// metoda pentru executarea operatiei de undo
	void doUndo() override
	{
		const __int64_t position = repo.find(addedDisciplina.getDenumire());
		repo.remove(position);
	}
};

class UndoRemove : public UndoAction
{
	// masina stearsa
	Disciplina deletedDisciplina;

	// repository-ul de masini
	AbstractRepo& repo;

public:
	// constructorul clasei
	UndoRemove(AbstractRepo& repo, const  Disciplina& d) : repo{ repo }, deletedDisciplina{ d } {}

	// metoda pentru executarea operatiei de undo
	void doUndo() override
	{
		repo.store(deletedDisciplina);
	}
};

class UndoModify : public UndoAction
{
	// masina modificata
	Disciplina oldDisciplina;
	Disciplina newDisciplina;

	// repository-ul de masini
	AbstractRepo& repo;

public:
	// constructorul clasei
	UndoModify(AbstractRepo& repo, const  Disciplina& oldD, const Disciplina& newD) : repo{ repo }, oldDisciplina{ oldD }, newDisciplina{ newD } {}

	// metoda pentru executarea operatiei de undo
	void doUndo() override
	{
		const __int64_t position = repo.find(newDisciplina.getDenumire());
		repo.modify(position, oldDisciplina);
	}
};