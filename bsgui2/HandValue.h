#pragma once

struct HandValue {
	int value;
	bool soft;
	HandValue(int value, bool soft) {
		this->value = value;
		this->soft = soft;
	}
};