### Plan ###
## Klasy podstawowe
Osoba - klasa bazowa dla różnych ról w systemie, takich jak Pracownik, Kierownik, i Klient. Zawiera wspólne atrybuty jak imię, nazwisko, wiek.

Pracownik - dziedziczy po Osobie, zawiera informacje o pracownikach, takich jak stanowisko, pensja, opinie i staż.

Kierownik - dziedziczy po Pracownik, dodaje funkcje zarządzania, w tym możliwość nadzorowania innych pracowników(zwolnienie, przyjęcie do pracy). Tworzy raporty o wydajności pracy pracowników.

Klient - również dziedziczy po Osoba, dzielimy na OsobaPrywatna i Firma. Klienci mogą kupować produkty. Klient może posiada historię zakupów i możliwość uzyskania rekomendacji produktów na jej podstawie. Może też uzyskiwać zniżki np. po zakupie określonej ilości produktów.

OsobaPrywatna - dla indywidualnych konsumentów. Może posiadać preferencje zakupowe, na tej podstawie sklep może proponować określone produkty.
Firma - dla klientów biznesowych, może zawierać dodatkowe informacje jak nazwa firmy, numer identyfikacyjny i branża.

## Klasy magazynowe
Produkt - przechowuje informacje o produkcie, takie jak nazwa, cena, ilość, data zakupu, termin ważności, wymiary(albo waga), producent(kraj pochodzenia). Można dodać metodę do sprawdzania dostępności.

Magazyn - zarządza listą produktów, przechowywanych jako kolekcja std::vector<std::unique_ptr<Produkt>>. Może zawierać metody do wyszukiwania produktów według różnych kryteriów (nazwa, producent, data ważności).

## Klasy transakcyjne
Transakcja - reprezentuje pojedynczą operację kupna lub sprzedaży, przechowuje informacje o produktach, ilościach, a także o osobach biorących udział w transakcji (np. pracownik wydający towar, klient, ilosc sprzedanego, kupionego towaru). Może zawierać metody do obliczania podatków, rabatów i możliwość anulowania transakcji i zarządzania zwrotami.

RejestrTransakcji - zarządza historią wszystkich transakcji. Można dodać filtry do przeszukiwania historii transakcji (np. w/g daty, klienta, typu transakcji).
Generowanie statystyk i raportów (np. najczęściej sprzedawane produkty).

## Klasy pomocnicze
Dokument - generuje różne rodzaje dokumentów, w tym faktury i paragony zwiazane z transakcjami.
Możliwość zapisu dokumentów, może nawet do różnych formatów (PDF, CSV).

RaportFinansowy - generuje szczegółowe raporty finansowe, w tym wykresy sprzedaży i zakupów pokazujące zyski i straty miesięczne. Raporty uwzględniają również podatki, koszty stałe, takie jak pensje pracowników, i dostarczają informacje o zysku netto.

## Wizualizacja danych
Wykresy - bilans zysków i strat za określony okres. Wykorzystanie biblioteki graficznej (takiej jak Qt) do tworzenia wykresów.
Interaktywne wykresy z możliwością filtrowania danych (np. wybór okresu, kategorii produktów).

## Użycie technologii i technik
Polimorfizm i dziedziczenie - wykorzystane do konstruowania hierarchii osób z różnymi rolami i funkcjami.
Smart Pointery (unique_ptr) - zapewniają automatyczne zarządzanie pamięcią w klasie Magazyn.
Użycie bibliotek standardowych C++ - takich jak <vector>, <chrono> dla zarządzania kolekcjami i czasem.

