#pragma once

class Tile {
public:
	Tile();
	~Tile();

	double getPotential() const { return potential; }
	void setPotential(double potential);

private:
	double _potential;
};
