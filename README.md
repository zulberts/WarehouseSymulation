### Plan ###
## Klasy podstawowe
Osoba - klasa bazowa dla różnych ról w systemie, takich jak Pracownik, Kierownik, i Klient. Zawiera wspólne atrybuty jak imię i nazwisko.

Pracownik - dziedziczy po Osobie, zawiera informacje o pracownikach, takich jak stanowisko i pensja.

Kierownik - dziedziczy po Pracownik, dodaje funkcje zarządzania, w tym możliwość nadzorowania innych pracowników.

Klient - również dziedziczy po Osoba, dzielimy na OsobaPrywatna i Firma. Klienci mogą kupować produkty.

OsobaPrywatna - dla indywidualnych konsumentów.
Firma - dla klientów biznesowych, może zawierać dodatkowe informacje jak nazwa firmy i numer identyfikacyjny.

## Klasy magazynowe
Produkt - przechowuje informacje o produkcie, takie jak nazwa, cena, ilość, data zakupu i termin ważności.

Magazyn - zarządza listą produktów, przechowywanych jako kolekcja std::vector<std::unique_ptr<Produkt>>.

## Klasy transakcyjne
Transakcja - reprezentuje pojedynczą operację kupna lub sprzedaży, przechowuje informacje o produktach, ilościach, a także o osobach biorących udział w transakcji (np. pracownik wydający towar, klient, ilosc sprzedanego, kupionego towaru).

RejestrTransakcji - zarządza historią wszystkich transakcji.

## Klasy pomocnicze
Dokument - generuje różne rodzaje dokumentów, w tym faktury i paragony zwiazane z transakcjami.

RaportFinansowy - generuje szczegółowe raporty finansowe, w tym wykresy sprzedaży i zakupów pokazujące zyski i straty miesięczne. Raporty uwzględniają również podatki, koszty stałe, takie jak pensje pracowników, i dostarczają informacje o zysku netto.

## Wizualizacja danych
Wykresy - bilans zysków i strat za określony okres. Wykorzystanie biblioteki graficznej (takiej jak Qt) do tworzenia wykresów.

## Użycie technologii i technik
Polimorfizm i dziedziczenie - wykorzystane do konstruowania hierarchii osób z różnymi rolami i funkcjami.
Smart Pointery (unique_ptr) - zapewniają automatyczne zarządzanie pamięcią w klasie Magazyn.
Użycie bibliotek standardowych C++ - takich jak <vector>, <chrono> dla zarządzania kolekcjami i czasem.

