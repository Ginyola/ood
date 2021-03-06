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
������������ ������� ���������
*/
class CConstDocumentItem
{
public:
	// ���������� ��������� �� ����������� �����������, ���� nullptr, ���� ������� �� �������� ������������
	shared_ptr<const IImage> GetImage() const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;
};

/*
������� ���������. ��������� �������� ������ � ����������� ��� ���������
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	shared_ptr<IParagraph> GetParagraph();
};

/* �������� ������*/

class IParagraph
{
public:
	virtual ~IParagraph() = default;
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
�����������
*/
class IImage
{
public:
	virtual ~IImage() = default;
	// ���������� ���� ������������ �������� ���������
	virtual Path GetPath() const = 0;

	// ������ ����������� � ��������
	virtual int GetWidth() const = 0;
	// ������ ����������� � ��������
	virtual int GetHeight() const = 0;

	// �������� ������ �����������
	virtual void Resize(int width, int height) = 0;
};

class CImage : public IImage
{
public:
	Path GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

private:
	Path m_path;
	int m_width = 0;
	int m_height = 0;
};

/*
�������� ���������
*/
class IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	virtual shared_ptr<IParagraph> InsertParagraph(const string& text,
		optional<size_t> position = none)
		= 0;

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images
	// ��� ������������� ��������������� ������
	virtual shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = none)
		= 0;

	// ���������� ���������� ��������� � ���������
	virtual size_t GetItemsCount() const = 0;

	// ������ � ��������� �����������
	virtual CConstDocumentItem GetItem(size_t index) const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;

	// ������� ������� �� ���������
	virtual void DeleteItem(size_t index) = 0;

	// ���������� ��������� ���������
	virtual string GetTitle() const = 0;
	// �������� ��������� ���������
	virtual void SetTitle(const string& title) = 0;

	// �������� � ����������� �������� Undo
	virtual bool CanUndo() const = 0;
	// �������� ������� ��������������
	virtual void Undo() = 0;

	// �������� � ����������� �������� Redo
	virtual bool CanRedo() const = 0;
	// ��������� ���������� ������� ��������������
	virtual void Redo() = 0;

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
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

	// ������� ������� �� ���������
	void DeleteItem(size_t index) override;

	string GetTitle() const override;
	virtual void SetTitle(const string& title) override;

private:
	string m_title;
};
