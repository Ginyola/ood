#pragma once

#include "Html.h"
#include "CHistory.h"
#include "ICommand.h"

class CInsertParagraph : public ICommand
{
public:
	CInsertParagraph(CDocument& document, std::string const& text, optional<size_t> position, CHistory &history)
		: m_document(document)
		, m_history(history)
		, m_text(text)
		, m_position(position)
		{};
	
	void Execute() override
	{

		m_document.InsertParagraph(m_text, m_position);
	}

private:
	CDocument& m_document;
	CHistory& m_history;
	std::string m_text;
	optional<size_t> m_position;
};