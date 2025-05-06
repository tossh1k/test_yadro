#pragma once

class TapeInterface {
public:	
	virtual ~TapeInterface() = default;
	virtual int read() = 0;
	virtual void write(int val) = 0;
	virtual void moveRight() = 0;
	virtual void moveLeft() = 0;
	virtual bool endOfTape() = 0;
	virtual void rewind() = 0;
};