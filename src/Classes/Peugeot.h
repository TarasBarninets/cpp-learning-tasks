#pragma once
#include "Car.h"

class Peugeot : public Car
{
public:
	Peugeot(unsigned char fuel_level);
	~Peugeot();

	bool start_engine() override;
	bool stop_engine() override;;
	void set_gear(unsigned char gear) override;
	void set_parking_break(bool value) override;
	void accelerate() override;
	void put_break() override;
	void add_fuel(unsigned char value) override;
	bool is_accaptable_for_usage() override;
};

