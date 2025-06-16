#pragma once

#include <string>
#include <memory>

enum class AnsiMode {
	Basic,
	Bright,
	Color256,
	RGB
};

struct AnsiColor {
	using Ptr = std::shared_ptr<AnsiColor>;
	AnsiMode mode;
	int value;
	int r, g, b;

	static Ptr Basic(int v) { return Ptr(new AnsiColor{AnsiMode::Basic, v, 0, 0, 0}); }
	static Ptr Bright(int v) { return Ptr(new AnsiColor{AnsiMode::Bright, v, 0, 0, 0}); }
	static Ptr Color256(int v) { return Ptr(new AnsiColor{AnsiMode::Color256, v, 0, 0, 0}); }
	static Ptr RGB(int r, int g, int b) { return Ptr(new AnsiColor{AnsiMode::RGB, 0, r, g, b}); }
};

std::string ToAnsiCode(const AnsiColor::Ptr color, bool isForeground);

std::string AnsiPrint(
	const std::string& text,
	const AnsiColor::Ptr fg = nullptr,
	const AnsiColor::Ptr bg = nullptr,
	bool hi = false,
	bool blink = false
);