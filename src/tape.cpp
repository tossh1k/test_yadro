#include "tape.h"

extern Config conf;

Tape::Tape(const std::string& filename) {
	pos_ = 0;
	file_.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
	if (file_.is_open())
		readFromFile();
}

Tape::Tape(const std::string& filename, Config config) {
	pos_ = 0;
	file_.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
	if (file_)
		readFromFile();
	delays_ = config;
}

Tape::Tape(const Tape& copy) : pos_(copy.pos_), tape_data_(copy.tape_data_) {}

void Tape::readFromFile() {
	int elem;
	while (file_ >> elem) {
		tape_data_.push_back(elem);
	}
	file_.close();
}

void Tape::writeToFile(const std::string& filename) {
	file_.open(filename, std::fstream::out | std::fstream::app);
	for (int i = 0; i < tape_data_.size(); ++i) {
		file_ << tape_data_[i] << '\n';
	}
}


int Tape::read() {
	std::this_thread::sleep_for(std::chrono::milliseconds(delays_.read_delay));
	return tape_data_[pos_];
}

void Tape::write(int val) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delays_.write_delay));
	if (pos_ >= tape_data_.size()) {
		tape_data_.push_back(val);
	}
	else {
		tape_data_[pos_] = val;
	}
}

void Tape::moveRight() {
	std::this_thread::sleep_for(std::chrono::milliseconds(delays_.move_delay));
	pos_++;
}

void Tape::moveLeft() {
	std::this_thread::sleep_for(std::chrono::milliseconds(delays_.move_delay));
	pos_--;
}

void Tape::rewind() {
	std::this_thread::sleep_for(std::chrono::milliseconds(delays_.rewind_delay));
	pos_ = 0;
}

bool Tape::endOfTape() {
	return pos_ >= tape_data_.size();
}

void Config::setConfig(std::fstream& file) {
	std::regex ms{ "[1-9][0-9]+$" };
	std::string line;
	std::getline(file, line);
	std::smatch sm;
	std::regex_search(line, sm, ms);
	int read = std::stoi(sm[0]);
	conf.read_delay = read;

	std::getline(file, line);
	std::regex_search(line, sm, ms);
	int write = std::stoi(sm[0]);
	conf.write_delay = write;

	std::getline(file, line);
	std::regex_search(line, sm, ms);
	int rewind = std::stoi(sm[0]);
	conf.rewind_delay = rewind;

	std::getline(file, line);
	std::regex_search(line, sm, ms);
	int move = std::stoi(sm[0]);
	conf.move_delay = move;
}