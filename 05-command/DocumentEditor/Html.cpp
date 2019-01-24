#include "Html.h"

shared_ptr<IParagraph> CDocument::InsertParagraph(const string& text, optional<size_t> position)
{
	if (position)
	{
		return nullptr;
	}

	shared_ptr<CParagraph> newParagraph = make_shared<CParagraph>();
	newParagraph->SetText(text);
	
	if (position == static_cast<size_t>(0))
	{
		//m_orderedElements.emplace_back(newParagraph);
	}
	else if(position > static_cast<size_t>(0))
	{
		/*auto it = m_orderedElements.begin();
		advance(it, position.get());
		m_orderedElements.insert(it, newParagraph);*/
	}
	
	return newParagraph;
}

shared_ptr<IImage> CDocument::InsertImage(const Path& path, int width, int height, optional<size_t> position)
{
	return nullptr;
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{

	return CConstDocumentItem();
}

CDocumentItem CDocument::GetItem(size_t index)
{
	return CDocumentItem();
}

string CDocument::GetTitle() const
{
	return m_title;
}

void CDocument::SetTitle(const string& title)
{
	m_title = title;
}


string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const string& text)
{
	m_text = text;
}

Path CImage::GetPath() const
{
	return m_path;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}
