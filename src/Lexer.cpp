#include "Lexer.hpp"
#include "Token.hpp"
#include <unordered_map>

struct LexerState
{
	size_t pos = 0;
	std::string_view src;

	LexerState(std::string_view src)
		: src(src)
	{
	}
};

static const std::unordered_map<std::string, TokenType> keywords = {
	{ "or", TokenType::Or },
	{ "and", TokenType::And },
};

bool
is_alpha(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool
is_numeric(char c)
{
	return c >= '0' && c <= '9';
}

bool
is_alphanumeric(char c)
{
	return is_alpha(c) || is_numeric(c);
}

void
advance(LexerState& st)
{
	st.pos++;
}

char
current_char(const LexerState& st)
{
	if (st.pos < st.src.size() - 1) {
		return st.src[st.pos];
	} else {
		return '\0';
	}
}

bool
matches(const LexerState& st, char c)
{
	return c == st.src[st.pos + 1];
}

bool
skip_whitespace_and_comment(LexerState& st)
{
	switch (current_char(st)) {
		case ' ':
		case '\n':
		case '\t':
			advance(st);
			return true;
		case '-':
			if (matches(st, '-')) {
				advance(st);
				while (current_char(st) != '\n') {
					advance(st);
				}
				return true;
			} else {
				return false;
			}
	}
	return false;
}

Token
one(LexerState& st, TokenType type)
{
	Span span = { st.pos, st.pos + 1 };
	advance(st);
	return Token{ type, span };
}

Token
one_or_two(LexerState& st, TokenType type, char c2, TokenType type2)
{
	Span span;
	span.start = st.pos;

	advance(st);
	if (current_char(st) == c2) {
		advance(st);
		span.end = st.pos;
		return Token{ type2, span };
	} else {
		span.end = st.pos;
		return Token{ type, span };
	}
}

Token
one_or_two(LexerState& st, TokenType type, char c2, TokenType type2, char c3, TokenType type3)
{
	Span span;
	span.start = st.pos;

	advance(st);
	if (current_char(st) == c2) {
		advance(st);
		span.end = st.pos;
		return Token{ type2, span };
	} else if (current_char(st) == c3) {
		advance(st);
		span.end = st.pos;
		return Token{ type3, span };
	} else {
		span.end = st.pos;
		return Token{ type, span };
	}
}

Token
identifier_or_keyword(LexerState& st)
{
	Span span;
	span.start = st.pos;
	while (is_alpha(current_char(st))) {
		advance(st);
	}
	span.end = st.pos;

	auto it = keywords.find(st.src.substr(span.start, span.end - span.start).data());
	Token token;
	if (it != keywords.end()) {
		token = { it->second, span };
	} else {
		token = { TokenType::Identifier, span };
	}

	return token;
}

Token
number(LexerState& st)
{
	Span span;
	span.start = st.pos;
	while (is_numeric(current_char(st))) {
		advance(st);
	}

	if (current_char(st) == '.') {
		advance(st);

		if (!is_numeric(current_char(st))) {
			span.end = st.pos;
			return Token{ TokenType::Error, span };
		}

		while (is_numeric(current_char(st))) {
			advance(st);
		}
	}

	if (current_char(st) == 'e' || current_char(st) == 'E') {
		advance(st);

		if (current_char(st) == '-') {
			advance(st);
		}

		if (!is_numeric(current_char(st))) {
			span.end = st.pos;
			return Token{ TokenType::Error, span };
		}

		while (is_numeric(current_char(st))) {
			advance(st);
		}
	}

	span.end = st.pos;
	return Token{ TokenType::Number, span };
}

Token
next_token(LexerState& st)
{
	Token token;

	switch (current_char(st)) {
		case '(':
			token = one(st, TokenType::LeftParen);
			break;
		case ')':
			token = one(st, TokenType::RightParen);
			break;
		case '{':
			token = one(st, TokenType::LeftBrace);
			break;
		case '}':
			token = one(st, TokenType::RightBrace);
			break;
		case ':':
			token = one(st, TokenType::Colon);
			break;
		case ';':
			token = one(st, TokenType::Semicolon);
			break;
		case '<':
			token = one_or_two(
				st, TokenType::Less, '=', TokenType::LessEqual, '>', TokenType::NotEqual
			);
			break;
		case '>':
			token = one_or_two(st, TokenType::Greater, '=', TokenType::GreaterEqual);
			break;
		case '~':
			token = one(st, TokenType::Not);
			break;
		case '|':
			token = one(st, TokenType::Pipe);
			break;
		case '+':
			token = one(st, TokenType::Plus);
			break;
		case '-':
			token = one(st, TokenType::Minus);
			break;
		case '*':
			token = one(st, TokenType::Star);
			break;
		case '/':
			token = one(st, TokenType::Slash);
			break;
		case ',':
			token = one(st, TokenType::Comma);
			break;
		case '!':
			token = one_or_two(st, TokenType::Show, '!', TokenType::DoubleShow);
			break;
		case '?':
			token = one_or_two(st, TokenType::Ask, '?', TokenType::DoubleAsk);
			break;
		case '=':
			token = one(st, TokenType::Equal);
			break;
		case '\0':
			token = { TokenType::Eof, { st.pos, st.pos } };
			break;
		default:
			if (is_alpha(current_char(st))) {
				token = identifier_or_keyword(st);
			} else if (is_numeric(current_char(st))) {
				token = number(st);
			} else {
				token = one(st, TokenType::Error);
			}
			break;
	}

	return token;
}

std::vector<Token>
lex(std::string_view src)
{
	LexerState state(src);
	std::vector<Token> tokens;

	while (true) {
		while (skip_whitespace_and_comment(state))
			;

		Token token = next_token(state);
		tokens.push_back(token);

		if (token.type == TokenType::Eof) {
			break;
		}
	}

	return tokens;
}
