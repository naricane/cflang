#pragma once

#include <cstddef>
#include <string>

enum class TokenType
{
	Number,
	Identifier,

	LeftParen,
	RightParen,
	LeftBrace,
	RightBrace,
	Plus,
	Minus,
	Star,
	Slash,
	Equal,
	NotEqual,
	Less,
	Greater,
	LessEqual,
	GreaterEqual,
	Not,
	And,
	Or,
	Colon,
	Semicolon,
	Pipe,
	Show,
	DoubleShow,
	Ask,
	DoubleAsk,
	Comma,

	Error,
	Eof
};

struct Span
{
	size_t start;
	size_t end;
};

struct Token
{
	TokenType type;
	Span span;

	std::string to_string(std::string_view src);
};
