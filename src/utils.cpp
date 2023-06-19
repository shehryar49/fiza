#include <string>
#include "utils.h"

bool packageNameIsValid(const std::string name){
	if (name.size() == 0)
		return false;
	// first character must be alphabet
	char ch = name[0];
	if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z'))
		return false;
	// now rest of characters can should be alphabets and/or digits
	for (int i = 1; i < name.size(); i ++){
		ch = name[i];
		if ((ch < 'a' || ch > 'z') &&
				(ch < 'A' || ch > 'Z') &&
				(ch < '0' || ch > '9'))
			return false;
	}
	return true;
}
