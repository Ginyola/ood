#pragma once

#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

typedef boost::filesystem::path Path;
using boost::none;
using boost::optional;

class IParagraph;
class IImage;

/*
Неизменяемый элемент документа
*/
class CConstDocumentItem
{
public:
	// Возвращает указатель на константное изображение, либо nullptr, если элемент не является изображением
	shared_ptr<const IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;
};

/*
Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	shared_ptr<IParagraph> GetParagraph();
};

/* Параграф текста*/
class IElement
{
public:
	virtual ~IElement() = default;
};

class IParagraph : public IElement
{
public:
	virtual string GetText() const = 0;
	virtual void SetText(const string& text) = 0;
};

class CParagraph : public IParagraph
{
public:
	string GetText() const override;
	void SetText(const string& text) override;

private:
	string m_text;
};

/*
Изображение
*/
class IImage : public IElement
{
public:
	// Возвращает путь относительно каталога документа
	virtual Path GetPath() const = 0;
	virtual void SetPath(const Path& text) = 0;

	// Ширина изображения в пикселях
	virtual int GetWidth() const = 0;
	// Высота изображения в пикселях
	virtual int GetHeight() const = 0;

	// Изменяет размер изображения
	virtual void Resize(int width, int height) = 0;
};

class CImage : public IImage
{
public:
	Path GetPath() const override;
	void SetPath(const Path& path) override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

private:
	Path m_path;
	int m_width = 0;
	int m_height = 0;
};

/*
Интерфес документа
*/
class IDocument
{
public:
	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	virtual shared_ptr<IParagraph> InsertParagraph(const string& text,
		optional<size_t> position = none)
		= 0;

	// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	// Параметр path задает путь к вставляемому изображению
	// При вставке изображение должно копироваться в подкаталог images
	// под автоматически сгенерированным именем
	virtual shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = none)
		= 0;

	// Возвращает количество элементов в документе
	virtual size_t GetItemsCount() const = 0;

	// Доступ к элементам изображения
	virtual CConstDocumentItem GetItem(size_t index) const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;

	// Удаляет элемент из документа
	virtual void DeleteItem(size_t index) = 0;

	// Возвращает заголовок документа
	virtual string GetTitle() const = 0;
	// Изменяет заголовок документа
	virtual void SetTitle(const string& title) = 0;

	// Сообщает о доступности операции Undo
	virtual bool CanUndo() const = 0;
	// Отменяет команду редактирования
	virtual void Undo() = 0;

	// Сообщает о доступности операции Redo
	virtual bool CanRedo() const = 0;
	// Выполняет отмененную команду редактирования
	virtual void Redo() = 0;

	// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images
	// пути к изображениям указываются относительно пути к сохраняемому HTML файлу
	virtual void Save(const Path& path) const = 0;

	virtual ~IDocument() = default;
};

class CDocument : public IDocument
{
public:
	shared_ptr<IParagraph> InsertParagraph(const string& text, optional<size_t> position = none) override;
	shared_ptr<IImage> InsertImage(const Path& path, int width, int height, optional<size_t> position = none) override;

	size_t GetItemsCount() const override;

	CConstDocumentItem GetItem(size_t index) const override;
	CDocumentItem GetItem(size_t index) override;

	// Удаляет элемент из документа
	void DeleteItem(size_t index) override;

	string GetTitle() const override;
	virtual void SetTitle(const string& title) override;

private:
	std::vector<shared_ptr<IElement>> m_orderedElements;
	string m_title;
};
