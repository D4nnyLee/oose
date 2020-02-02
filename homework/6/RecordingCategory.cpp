#include <string>
#include "RecordingCategory.h"
#include "Recording.h"

RecordingCategory::RecordingCategory(std::string l, RecordingCategory * super): label(l), supercategory(super) {}

std::string RecordingCategory::getLabel() {
	return label;
}

RecordingCategory * RecordingCategory::getSubcategory(int idx) {
	return subcategory[idx];
}

Recording * RecordingCategory::getRecording(int idx) {
	return recording[idx];
}

int RecordingCategory::getSubcategoryLength() {
	return subcategory.size();
}

int RecordingCategory::getRecordingLength() {
	return recording.size();
}

RecordingCategory * RecordingCategory::addSubcategory(std::string l) {
	RecordingCategory * tmp = new RecordingCategory(l, this);
	subcategory.push_back(tmp);
	return tmp;
}

Recording * RecordingCategory::addRecording(std::string title, std::string artist) {
	Recording * tmp = new Recording(title, artist, this);
	recording.push_back(tmp);
	return tmp;
}
