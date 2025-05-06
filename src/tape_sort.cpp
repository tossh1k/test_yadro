#include "tape_sort.h"
#include <cstdio>

extern Config conf;

void TapeSort::writeToRAM(Tape& inp) {
	for (int i = 0; i < ram_ && !inp.endOfTape(); ++i) {
		int val = inp.read();
		ram_data_.push_back(val);
		inp.moveRight();
	}
}

void TapeSort::ramSort() {
	std::sort(ram_data_.begin(), ram_data_.end());
}

void TapeSort::writeToTmp() {
	tmp_count_++;
	std::string tmp_file = "../tmp/tmp_" + std::to_string(tmp_count_) + ".txt";
	Tape tape(tmp_file, conf);
	tmp_tapes_.push_back(tape);
	for (auto i : ram_data_) {
		tmp_tapes_.back().write(i);
		tmp_tapes_.back().moveRight();
	}

	tmp_tapes_.back().writeToFile(tmp_file);
	tmp_tapes_.back().rewind();
	ram_data_.resize(0);
}

Tape TapeSort::mergeTmp(Tape& vec1, Tape& vec2) {
	merge_++;
	std::string tmp_merge = "../tmp/tmp_merge_" + std::to_string(merge_) + ".txt";
	Tape merged(tmp_merge, conf);

	while (!vec1.endOfTape() && !vec2.endOfTape()) {
		ram_data_.push_back(vec1.read());
		if (ram_data_.back() < vec2.read()) {
			int val = vec1.read();
			vec1.moveRight();
			merged.write(val);
			merged.moveRight();
		}
		else {
			int val = vec2.read();
			vec2.moveRight();
			merged.write(val);
			merged.moveRight();
		}
	}
	while (!vec1.endOfTape()) {
		int val = vec1.read();
		vec1.moveRight();
		merged.write(val);
		merged.moveRight();
	}
	while (!vec2.endOfTape()) {
		int val = vec2.read();
		vec2.moveRight();
		merged.write(val);
		merged.moveRight();
	}

	merged.writeToFile(tmp_merge);
	ram_data_.resize(0);
	merged.rewind();
	return merged;
}

Tape TapeSort::mergeAll(const std::vector<Tape>& arr, int l, int r) {
	if (l == r) {
		return arr[l];
	}
	if (l - r == 1) {
		return mergeTmp(tmp_tapes_[l], tmp_tapes_[r]);
	}

	int mid = (l + r) / 2;

	Tape v1 = mergeAll(arr, l, mid);
	Tape v2 = mergeAll(arr, mid + 1, r);

	return mergeTmp(v1, v2);
}

void TapeSort::tapeSort(Tape& inp, const std::string& outp) {
	createDirForTmp();

	while (!inp.endOfTape()) {
		writeToRAM(inp);
		ramSort();
		writeToTmp();
	}
	
	mergeAll(tmp_tapes_, 0, tmp_tapes_.size() - 1);
	std::string s = "../tmp/tmp_merge_" + std::to_string(merge_) + ".txt";
	int ex = std::rename(s.c_str(), outp.c_str());
}

void TapeSort::createDirForTmp() {
	if (!std::filesystem::exists("../tmp"))
		std::filesystem::create_directories("../tmp");
	else {
		std::filesystem::remove_all("../tmp");
		std::filesystem::create_directories("../tmp");
	}
}