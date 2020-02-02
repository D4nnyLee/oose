#ifndef _RECORDINGCATEGORY_H_
#define _RECORDINGCATEGORY_H_

#include <string>
#include <vector>

class Recording;

class RecordingCategory {
    private:
		std::string label;

		std::vector<RecordingCategory*> subcategory;
		RecordingCategory * supercategory;

		std::vector<Recording*> recording;

	public:
		RecordingCategory(std::string, RecordingCategory* = NULL);

		std::string getLabel();
		RecordingCategory * getSubcategory(int);
		Recording * getRecording(int);
		int getSubcategoryLength();
		int getRecordingLength();

		RecordingCategory * addSubcategory(std::string);
		Recording * addRecording(std::string, std::string);
};

#endif
