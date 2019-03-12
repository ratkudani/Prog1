int* getReactorPointer(int* reactorArray);
typedef int(*R)(int,int);
int getTrueReactorState(int a, int b);
R getReactorState(int);

int main()
{

	//egész
	int chernobyl = 1986;

	//egészre mutató mutató
	int* toChernobyl = &chernobyl;

	//C++ feature
	int& refToChernobyl = chernobyl;

	//egészek tömbje
	int reactorsOfCNPP[4] = {1,2,3,4};

	//egészek tömbjének referenciája
	int (&refToReactors)[4] = reactorsOfCNPP;

	//egészre mutató mutatók tömbje
	int * pointerArray[4];

	//egészre mutató mutatót visszaadó függvény
	int* myReactor = getReactorPointer(reactorsOfCNPP);

	//egészre mutató mutatót visszaadó függvényre mutató mutató
	int* (*pointerFUN)(int*) = getReactorPointer;

	//egészet visszaadó és két egészet kapó függvényre mutató mutatót visszaadó, egészet kapó függvény
	R getTheTrueState = getReactorState(1986);

	return 0;

}
int* getReactorPointer(int* reactorArray)
{
	return reactorArray;
}
int getTrueReactorState(int a, int b)
{
	return -1986;
}

R getReactorState(int wishGranter)
{
	return getTrueReactorState;
}

