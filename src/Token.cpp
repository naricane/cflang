#include "Token.hpp"
#include <format>

const char*
token_to_string(TokenType type)
{
	switch (type) {
		case TokenType::Number:
			return "Number";
			break;
		case TokenType::Identifier:
			return "Identifier";
			break;
		case TokenType::LeftParen:
			return "LeftParen";
			break;
		case TokenType::RightParen:
			return "RightParen";
			break;
		case TokenType::LeftBrace:
			return "LeftBrace";
			break;
		case TokenType::RightBrace:
			return "RightBrace";
			break;
		case TokenType::Plus:
			return "Plus";
			break;
		case TokenType::Minus:
			return "Minus";
			break;
		case TokenType::Star:
			return "Star";
			break;
		case TokenType::Slash:
			return "Slash";
			break;
		case TokenType::Equal:
			return "Equal";
			break;
		case TokenType::NotEqual:
			return "NotEqual";
			break;
		case TokenType::Less:
			return "Less";
			break;
		case TokenType::Greater:
			return "Greater";
			break;
		case TokenType::LessEqual:
			return "LessEqual";
			break;
		case TokenType::GreaterEqual:
			return "GreaterEqual";
			break;
		case TokenType::Not:
			return "Not";
			break;
		case TokenType::And:
			return "And";
			break;
		case TokenType::Or:
			return "Or";
			break;
		case TokenType::Colon:
			return "Colon";
			break;
		case TokenType::Semicolon:
			return "Semicolon";
			break;
		case TokenType::Pipe:
			return "Pipe";
			break;
		case TokenType::Show:
			return "Show";
			break;
		case TokenType::DoubleShow:
			return "DoubleShow";
			break;
		case TokenType::Ask:
			return "Ask";
			break;
		case TokenType::DoubleAsk:
			return "DoubleAsk";
			break;
		case TokenType::Comma:
			return "Comma";
			break;
		case TokenType::Error:
			return "Error";
			break;
		case TokenType::Eof:
			return "EOF";
			break;
	}
};

std::string
Token::to_string(std::string_view src)
{
	return std::format(
		"{} {} {} {}",
		token_to_string(type),
		span.start,
		span.end,
		src.substr(span.start, span.end - span.start)
	);
};
