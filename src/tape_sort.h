#pragma once
#include "tape.h"
#include <algorithm>
#include <filesystem>

class TapeSort {
	const int ram_;
	int tmp_count_ = 0;
	int merge_ = 0;
	std::vector<int> ram_data_;
	std::vector<Tape> tmp_tapes_;
	
	void writeToRAM(Tape& inp);
	void ramSort();
	void writeToTmp();
	Tape mergeAll(const std::vector<Tape>& arr, int l, int r);
	Tape mergeTmp(Tape& vec1, Tape& vec2);
	void createDirForTmp();

public:
	TapeSort(int ram) : ram_(ram) {}
	void tapeSort(Tape& inp, const std::string& outp);
};