#include "Loan.h"
#include "Recording.h"
#include "RecordingCategory.h"

Recording::Recording(std::string _title, std::string _artist, RecordingCategory * _cateory): title(_title), aritst(_artist), cateory(_cateory) {}

std::string Recording::getTitle() {
	return title;
}

std::string Recording::getArtist() {
	return aritst;
}

RecordingCategory * Recording::getCategory() {
	return cateory;
}

Loan * Recording::getLoan(int idx) {
	return loan[idx];
}

int Recording::getLoanLength() {
	return loan.size();
}
