### Projekt z Programowania Obiektowego ###
Autorzy:
Albert Skutnik
Sofiya Yedzeika

### Temat Projeku:
W naszym programie zaimplementowane jest pare klas które sumują się w prosty przykładowy program, w którym można obsługiawć prostu magazyn.

### Podział klas:
## Klasy Osób Fizycznych
Klasa Person - stworzona z myślą o pracownikach/menagerach oraz klientach magazunu.

Klasa Worker - klasa pochodna klasy Person
zawiera: Stanowisko(enum class), wypłate, liczba w intach doświadczenia(miesiące np), oraz vector opini na temat pracownika

Klasa Manager - klasa pochodna klasy Worker
Zawiera list wskazników pracowników, posiada metody zwolnienia i zatrudnienia pracownika. Ma możliwość generowania raportu o pracowniku, zwraca opinie o pracowniku.

Klasa Customer - klasa pochodna klasy Person

Klasa PrivatePerson - klasa pochodna klasy Customer

Klasa FirmCustomer - klasa dziedziczy po klasie Customer, klasa różni się od klasy Customer tym że firma posiada jeszcze nazwe firmy, id, oraz kraj pochodzenia.

Klasa Firm - odrębna klasa stworzona na potrzebny składania zamówień do magazunu.

## Klasy Dostarczania produktów do magazunu
Klasa Item: zawiera podstawowe informacje na temat zamawianego produktu.
Na potrzeby projektu tutaj rozróżniamy Item oraz Product ponieważ chcemy aby automatycznie klasy typu Product były konstruowane za pomocą Shipmentu oraz struktury ShipmentDetail.

Struktura ShipmentDetail: zawiera Item oraz ilość itemów, dzięki takiemu rozwiązaniu w Shipmencie możliwość jest na raz złożenia zamówienia na wiele Itemów.

Klasa Product: dziedziczy po itemie

Klasa Shipment: zawiera liste ShipmentDetail, zawiera ktory menager odebral, ktory worker rozpakowal, oraz deliveryDate
Klasa ta służy temu aby przy składaniu zamówienia automatycznie w finalej klasie Warehouse była możliwość automatycznego tworzenia Produktów.

## Klasy transakcyjne
Klasa Transaction: Klasa stworzona z myślą o sprzedaży, użyliśmy tutaj shared_pointera aby była możliwosć decydować pomiędzy PrivatePerson a CustomerFirm.
Ponad to klasa ma możlwiość drukowania pragonu albo faktury w zależności od klienta. W samym drukowaniu paragonów użyliśmy dynamic_casta aby mieć pewność że odpowiednio zostaną wydrukowane dukumenty w zależności od klienta.

## Klasa magazunu
Klasa Warehouse zarządza magazynem poprzez przechowywanie i operowanie na kolekcjach produktów, przesyłek, pracowników, menedżerów oraz transakcji. Zawiera metody umożliwiające dodawanie nowych elementów do magazynu, wyszukiwanie produktów według różnych kryteriów, generowanie dokumentów oraz zarządzanie pracownikami. Dodatkowo, klasa umożliwia zapisywanie i ładowanie danych magazynu z plików JSON oraz tworzenie klientów.

### Użycie technologii i technik
W naszym projekcie użyliśmy między innymi:
- dziedziczenia
- wskaźników/referencji
- shared_pointerów/unique_pointerów
- dynamic_cast
- polimorfizmu
- takich bibliotek jak: nlohmann/json.hpp, ctime oraz wielu innych z STL.
- serializacji i deserializacji JSON
- zarządzania pamięcią za pomocą smart pointerów
- enkapsulacji danych w klasach (protected/private)
- przetestowaliśmy działania metod klas za pomocą GoogleTest


### Wnioski po napisaniu projektu
Implementacja magazynu w C++ przy użyciu zaawansowanych technik, takich jak serializacja JSON, pozwoliła na efektywne przechowywanie i odczytywanie stanu magazynu z plików, co znacznie ułatwia zarządzanie danymi. Generowanie dokumentów tekstowych usprawnia proces dokumentacji i archiwizacji, umożliwiając łatwe tworzenie raportów i zapisów transakcji. Rozbudowana struktura klas zapewnia lepszą organizację kodu, umożliwia łatwe rozszerzanie funkcjonalności oraz pomaga w zarządzaniu złożonością systemu; jednak, w przyszłych projektach, większy nacisk na testowanie jednostkowe oraz obsługę wyjątków może pomóc w identyfikowaniu i eliminowaniu błędów na wczesnym etapie developmentu.

## Rekomendacja na przyszłość
W przyszłych projektach warto skupić się na starannym planowaniu architektury przed rozpoczęciem kodowania, aby lepiej zrozumieć wymagania i struktury danych oraz uniknąć potencjalnych problemów w późniejszych etapach. Dobre przemyślenie planu pisania kodu pomoże w tworzeniu bardziej modułowego i łatwiejszego do utrzymania systemu.