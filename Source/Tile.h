#pragma once
class Tile
{
public:
	Tile();
	~Tile();

	double getPotential();
	void setPotential(double value);

private:
	double potential;
};