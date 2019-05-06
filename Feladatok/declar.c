int main()
{
    int a; //egész
    int *b; //egészre mutató mutató
    int &&c = 10; //egész referenciája
    int d[1];
    int* &&e = d; //egészek tomjének referenciája
    int *f[1]; //egészre mutató mutatók tömbje
    int *fuggveny(); //egészre mutató mutatót visszaadó függvény
    int (*g)(int); //egészre mutató mutatót visszaadó függvényre mutató mutató
    int (*F) (int, int));//egészet visszaadó és két egészet kapó függvényre mutató mutatót visszaadó, egészet kapó függvény
    int (*(*G) (int)) (int, int);//függvénymutató egy egészet visszaadó és két egészet kapó függvényre mutató mutatót visszaadó, egészet kapó függvényre

    return 0;
}
