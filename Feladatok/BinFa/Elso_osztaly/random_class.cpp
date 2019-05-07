#include <iostream>
#include <cstdlib>	
#include <cmath>	
#include <ctime>	

using namespace std;

class Random
{

	public:

		Random();

		~Random(){} 

		double get();
	private:

		bool exist;
		double value;

};


Random::Random() 
{
	exist = false;
	srand (time(NULL));
};


double Random::get() 
{
	if (!exist)
	{
		double u1, u2, v1, v2, w;

		do
		{
			u1 = rand () / (RAND_MAX + 1.0);
			u2 = rand () / (RAND_MAX + 1.0);
			v1 = 2 * u1 - 1;
			v2 = 2 * u2 - 1;
			w = v1 * v1 + v2 * v2;
		    }
		while (w > 1);

		double r = sqrt ((-2 * log (w)) / w);

		value = r * v2; 
		exist = !exist;

		return r * v1;
	}
	
	else
	{
		exist = !exist;
		return value;
	}
};    

int main() 
{

	Random rnd;

	for (int i = 0; i < 2; ++i) cout << rnd.get() << endl;

}