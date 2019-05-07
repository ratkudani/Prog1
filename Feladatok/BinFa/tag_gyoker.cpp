#include <iostream>

class LZWTree
{
public:
    LZWTree (): fa(&gyoker){}

    ~LZWTree ()
    {
        szabadit (gyoker.egyesGyermek ());
        szabadit (gyoker.nullasGyermek ());
    }

    void operator<<(char b)
    {
        if (b == '0')
        {

            if (!fa->nullasGyermek ())
            {
                Node *uj = new Node ('0');
                fa->ujNullasGyermek (uj);
                fa = &gyoker;
            }
            else
            {
                fa = fa->nullasGyermek ();
            }
        }
        else
        {
            if (!fa->egyesGyermek ())
            {
                Node *uj = new Node ('1');
                fa->ujEgyesGyermek (uj);
                fa = &gyoker;
            }
            else
            {
                fa = fa->egyesGyermek ();
            }
        }
    }
    void kiir (void)
    {
        melyseg = 0;
        kiir (&gyoker);
    }
    void szabadit (void)
    {
        szabadit (gyoker.jobbEgy);
        szabadit (gyoker.balNulla);
    }

private:

    class Node
    {
    public:
        Node (char b = '/'):betu (b), balNulla (0), jobbEgy (0) {};
        ~Node () {};
        Node *nullasGyermek () {
            return balNulla;
        }
        Node *egyesGyermek ()
        {
            return jobbEgy;
        }
        void ujNullasGyermek (Node * gy)
        {
            balNulla = gy;
        }
        void ujEgyesGyermek (Node * gy)
        {
            jobbEgy = gy;
        }
        
    private:
        friend class LZWTree;
        char betu;
        Node *balNulla;
        Node *jobbEgy;
        Node (const Node &);
        Node & operator=(const Node &);
    };

    Node gyoker;
    Node *fa;
    int melyseg;

    LZWTree (const LZWTree &);
    LZWTree & operator=(const LZWTree &);

    void kiir (Node* elem)
    {
        if (elem != NULL)
        {
            ++melyseg;
            kiir (elem->jobbEgy);

            for (int i = 0; i < melyseg; ++i)
                std::cout << "---";
            std::cout << elem->betu << "(" << melyseg - 1 << ")" << std::endl;
            kiir (elem->balNulla);
            --melyseg;
        }
    }
    void szabadit (Node * elem)
    {
        if (elem != NULL)
        {
            szabadit (elem->jobbEgy);
            szabadit (elem->balNulla);
            delete elem;
        }
    }

};

int
main ()
{
    char b;
    LZWTree binFa;

    while (std::cin >> b)
    {
        binFa << b;
    }

    binFa.kiir ();
    binFa.szabadit ();

    return 0;
}
