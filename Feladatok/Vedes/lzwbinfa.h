#ifndef LZWBINFA
#define LZWBINFA

#include <iostream>

class LZWBinFa
{
public:
    /* Szemben a bináris keresőfánkkal (BinFa osztály)
     http://progpater.blog.hu/2011/04/12/imadni_fogjak_a_c_t_egy_emberkent_tiszta_szivbol_3
     itt (LZWBinFa osztály) a fa gyökere nem pointer, hanem a '/' betüt tartalmazó objektum,
     lásd majd a védett tagok között lent: Csomopont gyoker;
     A fa viszont már pointer, mindig az épülő LZW-fánk azon csomópontjára mutat, amit az
     input feldolgozása során az LZW algoritmus logikája diktál:
     http://progpater.blog.hu/2011/02/19/gyonyor_a_tomor
     Ez a konstruktor annyit csinál, hogy a fa mutatót ráállítja a gyökérre. (Mert ugye
     laboron, blogon, előadásban tisztáztuk, hogy a tartalmazott tagok, most "Csomopont gyoker"
     konstruktora előbb lefut, mint a tagot tartalmazó LZWBinFa osztály konstruktora, éppen a
     következő, azaz a fa=&gyoker OK.)
   */
    LZWBinFa ():fa (&gyoker)
    {
    }
    ~LZWBinFa ()
    {
        szabadit (gyoker.egyesGyermek ());
        szabadit (gyoker.nullasGyermek ());
    }

    /* Tagfüggvényként túlterheljük a << operátort, ezzel a célunk, hogy felkeltsük a
     hallgató érdeklődését, mert ekkor így nyomhatjuk a fába az inputot: binFa << b; ahol a b
     egy '0' vagy '1'-es betű.
     Mivel tagfüggvény, így van rá "értelmezve" az aktuális (this "rejtett paraméterként"
     kapott ) példány, azaz annak a fának amibe éppen be akarjuk nyomni a b betűt a tagjai
     (pl.: "fa", "gyoker") használhatóak a függvényben.
     A függvénybe programoztuk az LZW fa építésének algoritmusát tk.:
     http://progpater.blog.hu/2011/02/19/gyonyor_a_tomor
     a b formális param az a betű, amit éppen be kell nyomni a fába.
     
     a binFa << b (ahol a b majd a végén látszik, hogy már az '1' vagy a '0') azt jelenti
     tagfüggvényként, hogy binFa.operator<<(b) (globálisként így festene: operator<<(binFa, b) )
     */
    void operator<< (char b)
    {
        // Mit kell betenni éppen, '0'-t?
        if (b == '0')
        {
            /* Van '0'-s gyermeke az aktuális csomópontnak?
           megkérdezzük Tőle, a "fa" mutató éppen reá mutat */
            if (!fa->nullasGyermek ())	// ha nincs, hát akkor csinálunk
            {
                // elkészítjük, azaz páldányosítunk a '0' betű akt. parammal
                Csomopont *uj = new Csomopont ('0');
                // az aktuális csomópontnak, ahol állunk azt üzenjük, hogy
                // jegyezze már be magának, hogy nullás gyereke mostantól van
                // küldjük is Neki a gyerek címét:
                fa->ujNullasGyermek (uj);
                // és visszaállunk a gyökérre (mert ezt diktálja az alg.)
                fa = &gyoker;
            }
            else			// ha van, arra rálépünk
            {
                // azaz a "fa" pointer már majd a szóban forgó gyermekre mutat:
                fa = fa->nullasGyermek ();
            }
        }
        // Mit kell betenni éppen, vagy '1'-et?
        else
        {
            if (!fa->egyesGyermek ())
            {
                Csomopont *uj = new Csomopont ('1');
                fa->ujEgyesGyermek (uj);
                fa = &gyoker;
            }
            else
            {
                fa = fa->egyesGyermek ();
            }
        }
    }
    /* A bejárással kapcsolatos függvényeink (túlterhelt kiir-ók, atlag, ratlag stb.) rekurzívak,
     tk. a rekurzív fabejárást valósítják meg (lásd a 3. előadás "Fabejárás" c. fóliáját és társait)
     (Ha a rekurzív függvénnyel általában gondod van => K&R könyv megfelelő része: a 3. ea. izometrikus
     részében ezt "letáncoltuk" :) és külön idéztük a K&R álláspontját :)
   */
    void kiir (void)
    {
        // Sokkal elegánsabb lenne (és más, a bevezetésben nem kibontandó reentráns kérdések miatt is, mert
        // ugye ha most két helyről hívják meg az objektum ilyen függvényeit, tahát ha kétszer kezd futni az
        // objektum kiir() fgv.-e pl., az komoly hiba, mert elromlana a mélység... tehát a mostani megoldásunk
        // nem reentráns) ha nem használnánk a C verzióban globális változókat, a C++ változatban példánytagot a
        // mélység kezelésére: http://progpater.blog.hu/2011/03/05/there_is_no_spoon
        melyseg = 0;
        // ha nem mondta meg a hívó az üzenetben, hogy hova írjuk ki a fát, akkor a
        // sztenderd out-ra nyomjuk
        kiir (&gyoker, std::cout);
    }
    /* már nem használjuk, tartalmát a dtor hívja
  void szabadit (void)
  {
    szabadit (gyoker.egyesGyermek ());
    szabadit (gyoker.nullasGyermek ());
    // magát a gyökeret nem szabadítjuk, hiszen azt nem mi foglaltuk a szabad tárban (halmon).
  }
  */

    /* A változatosság kedvéért ezeket az osztálydefiníció (class LZWBinFa {...};) után definiáljuk,
     hogy kénytelen légy az LZWBinFa és a :: hatókör operátorral minősítve definiálni :) l. lentebb */
    int getMelyseg (void);
    double getAtlag (void);
    double getSzoras (void);

    /* Vágyunk, hogy a felépített LZW fát ki tudjuk nyomni ilyenformán: std::cout << binFa;
     de mivel a << operátor is a sztenderd névtérben van, de a using namespace std-t elvből
     nem használjuk bevezető kurzusban, így ez a konstrukció csak az argfüggő névfeloldás miatt
     fordul le (B&L könyv 185. o. teteje) ám itt nem az a lényeg, hanem, hogy a cout ostream
     osztálybeli, így abban az osztályban kéne módosítani, hogy tudjon kiírni LZWBinFa osztálybelieket...
     e helyett a globális << operátort terheljük túl,
     
     a kiFile << binFa azt jelenti, hogy
     
      - tagfüggvényként: kiFile.operator<<(binFa) de ehhez a kiFile valamilyen
      std::ostream stream osztály forrásába kellene beleírni ezt a tagfüggvényt,
      amely ismeri a mi LZW binfánkat...
      
      - globális függvényként: operator<<(kiFile, binFa) és pont ez látszik a következő sorban:
     */
    friend std::ostream & operator<< (std::ostream & os, LZWBinFa & bf)
    {
        bf.kiir (os);
        return os;
    }
    void kiir (std::ostream & os)
    {
        melyseg = 0;
        kiir (&gyoker, os);
    }

private:
    //Ez a csomopont.h helye

    /* Mindig a fa "LZW algoritmus logikája szerinti aktuális" csomópontjára mutat */
    Csomopont *fa;
    // technikai
    int melyseg, atlagosszeg, atlagdb;
    double szorasosszeg;
    // szokásosan: nocopyable
    LZWBinFa (const LZWBinFa &);
    LZWBinFa & operator= (const LZWBinFa &);

    /* Kiírja a csomópontot az os csatornára. A rekurzió kapcsán lásd a korábbi K&R-es utalást... */
    void kiir (Csomopont * elem, std::ostream & os)
    {
        // Nem létező csomóponttal nem foglalkozunk... azaz ez a rekurzió leállítása
        if (elem != NULL)
        {
            ++melyseg;
            kiir (elem->egyesGyermek (), os);
            // ez a postorder bejáráshoz képest
            // 1-el nagyobb mélység, ezért -1
            for (int i = 0; i < melyseg; ++i)
                os << "---";
            os << elem->getBetu () << "(" << melyseg - 1 << ")" << std::endl;
            kiir (elem->nullasGyermek (), os);
            --melyseg;
        }
    }
    void szabadit (Csomopont * elem)
    {
        // Nem létező csomóponttal nem foglalkozunk... azaz ez a rekurzió leállítása
        if (elem != NULL)
        {
            szabadit (elem->egyesGyermek ());
            szabadit (elem->nullasGyermek ());
            // ha a csomópont mindkét gyermekét felszabadítottuk
            // azután szabadítjuk magát a csomópontot:
            delete elem;
        }
    }

protected:			// ha esetleg egyszer majd kiterjesztjük az osztályt, mert
    // akarunk benne valami újdonságot csinálni, vagy meglévő tevékenységet máshogy... stb.
    // akkor ezek látszanak majd a gyerek osztályban is

    /* A fában tagként benne van egy csomópont, ez erősen ki van tüntetve, Ő a gyökér: */
    Csomopont gyoker;
    int maxMelyseg;
    double atlag, szoras;

    void rmelyseg (Csomopont * elem);
    void ratlag (Csomopont * elem);
    void rszoras (Csomopont * elem);

};

#endif
