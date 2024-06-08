### Plan ###
## Klasy Osób Fizycznych
Pliki Person:
Klasa Person - zawiera imie, nazwisko, wiek

Pliki Workers:
Klasa Worker - klasa pochodna klasy Person
zawiera: Stanowisko(enum class), wypłate, liczba w intach doświadczenia(miesiące np), oraz vector opini na temat pracownika

Klasa Manager - klasa pochodna klasy Worker
Zawiera list wskazników pracowników, posiada metody zwolnienia i zatrudnienia pracownika. Ma możliwość generowania raportu o pracowniku, zwraca opinie o pracowniku.

Pliki Customers:
Klasa Customer - klasa pochodna klasy Person

Klasa PrivatePerson - klasa pochodna klasy Customer

Klasa Firm - klasa pochodna klasy Customer

## Klasy Dostarczania produktów do magazunu
Pliki Items: 
Klasa Item: zawiera nazwe produktu, cene, typ(enum class), podatek(wartość 0.00-1.00), oraz z time_t expiryDate, (dodać wage Itemu, oraz Firme która przywiozła item) 
Rozróżniać będziemy Item i Product ponieważ do productu chcemy dodać obsługe poprzez pracowników, oraz nałożenie cen odpowiednich w magazynie

Struct ShipmentDetail: zawiera Item, oraz ile tych itemów przyjechało oraz kiedy przyjechały.

Klasa Product: (chyba trzeba zrobić aby dziedziczyła po Itemie - raczej napewno XD)
zawiera odbierającego Managera ktory sprawdza towar, oraz Workera który rozpakował towar i boola ktory informuje czy produkt zostal sprzedany (sprawdza ile zostało na magazynie jezeli wiecej niz zero to dostepnyu), reszte rzeczy dziedziczy po klasie Item
zawiera metody takie jak ustalenie daty sprzedazy, oraz czy jest dostepny(ta metoda jest nie potrzebna ponieważ to wtedy będzie działało tylko na jeden produkt a w warehouse moze byc takich produktow pełno, więc do warehouse trzeba bedzie dodac taką opcje)

Pliki Shipment:
Klasa Shipment: zawiera liste ShipmentDetail, zawiera ktory menager odebral, ktory worker rozpakowal, oraz deliveryDate, generalnie musi zawierac wszystkie potrzebne dane aby moc automatycznie w klasie Warehouse utworzyc dane typu Product(dodać je do magazynu, sprawdzac nalezy po nazwie np czy wiecej takich rzeczy jest w magazynie o takiej samej nazwie produktu lecz np o innej cenie, zeby w wyszukiwaniu produtku bylo ładne)
metody: totalcost- zwraca ile kosztowala cala dostawa, usunac customerow bo to niepotrzebne, metoda addproduct zmienic na addshipmentdetail, i utowrzyc gettery do wszystkiego, potrzebne beda do tworzenia klasy product (klasa Product powinna miec wyzsza cene niż item)

## Klasy transakcyjne
pliki Transactions: można zmienić nazwe na sell, albo zostawić idk
Klasa Transaction: zawiera liste produktow ktore sprzedajemy, oraz ile ich sprzedajemy oraz workera ktory sprzedal oraz customera do ktorego sprzedajemy
metody: biorac pod uwage discout customera(dlatego calculatediscount nie potrzebne) tworzy kwote za dane produkty, cancel mozna zostawic(pamietac dopisac odpowiednia obsluge tego w klasie warehouse)


TUTAJ REGISTER PRZECZYTAC TO CO JEST W WAREHOUSE
Class TransactionRegister: zawiera liste wszystkich tranzakcji, mysle ze lista na oddzielne cancelledtranzaction jest nie potrzebna wtedy mniej metod do pisania bedzie a do wykresow bedzie trzeba napisac inne funkcje szukajace danych do wykresow

## Klasy drukujace do pliku .txt paragon i fakture
Pliki FileCreation
Klasa Document - zawiera virutalna metode, zmienic tutaj ze drukujemy na podstawie Transaction a nie na podstawie Shipment, (dodac tranzakcje)

class Invoice - dziedziczy po dokumencie, seller to powinien byc worker, a genereate document powinno dostawac tylko argument w jakim pliku ma byc zapisywana, a reszte danych brac z klasy invoice, dlatego Klasa document powinna zawierac jakąś tranzakcje.

class Recepit - generate document powinno dostawac tylko nazwe pliku, aby zapisywac te paragony łatwiej, dane powinna brac z klasy receipt czyli z documentu

## Klasa magazunu
pliki Warehouse
Zawiera liste Produktow, Liste shipmentow ktore dotarly do magazunu, Liste workerow, liste managerow, oraz registertranakcji(wsm ten register tranzakcji można zrobić inaczej po prostu do klasy Warehouse dodać liste tranzakcji i metody z Transactionregistera przeniesc do warehousa) będzie tak łatwiej

zmienic tworzenie klasy ze nic nie potrzeba na start i samemu w mainie wszystko ustawiamy, nalezy dodac odpowiednie gettery i settery do powyzej napisanych list(do listy productow nie trzeba settera bo po dodaniu shipmentu produkty same powinny sie dodawac do listy produktow)

dodać metode tworzenia tranzakcji

usunać niepotrzebne rzeczy

## Wizualizacja danych
Wykresy - bilans zysków i strat za określony okres. Wykorzystanie biblioteki graficznej (takiej jak Qt) do tworzenia wykresów.

## Użycie technologii i technik
Polimorfizm i dziedziczenie - wykorzystane do konstruowania hierarchii osób z różnymi rolami i funkcjami.
Smart Pointery (unique_ptr) - zapewniają automatyczne zarządzanie pamięcią w klasie Magazyn.
Użycie bibliotek standardowych C++ - takich jak vector, chrono dla zarządzania kolekcjami i czasem.

