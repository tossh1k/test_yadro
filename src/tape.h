#pragma once
#include "tape_interface.h"
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <regex>
#include <iostream>

struct Config {
	int read_delay = 0;
	int write_delay = 0;
	int rewind_delay = 0;
	int move_delay = 0;
	void setConfig(std::fstream& file);
};

class Tape : public TapeInterface {
	std::fstream file_; 
	int pos_; 
	std::vector<int> tape_data_;
	Config delays_;

public:	
	Tape(const std::string& filename);
	Tape(const std::string& filename, Config config);
	Tape(const Tape& copy);
	~Tape() = default;

	void readFromFile();
	void writeToFile(const std::string& filename);
	int read() override;
	void write(int val) override;
	void moveRight() override;
	void moveLeft() override;
	void rewind() override;
	bool endOfTape() override;
};