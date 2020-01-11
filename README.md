# uterm - a simple terminal

A simple terminal, based on Unix _bash_ terminal.

Developed as a university project for a 'Unix - programming and administering' ('UXP') subject

Prosty terminal, bazujący na Unix'owym terminalu _bash_.

Rozwijany jako projekt akademicki w ramach przedmiotu 'Unix - programowanie i administracja' ('UXP').

**Podstawowe funkcje implementowanego terminala:**
- możliwość uruchamiania zewnętrznych programów w postaci potoku arbitralnej długości
- obsługa poleceń wbudowanych cd, pwd i echo
- możliwość przekierowania wejścia/wyjścia do plików
- obsługa kodu powrotu jako zmiennej shella $?
- obsługa cytowania - pojedyncze zwykłe cudzysłowy
- obsługa zmiennych shella i środowiskowych poprzez konstrukcję export
- obsługa dokumentów wbudowanych (here documents)

**W przypadku wątpliwości przy realizacji, program będzie bazował na shellu _sh/bash._**

**Uproszczony podział na moduły oraz przepływ wykonania programu:**

_Użytkownik wprowadza polecenie_

Moduł analizy polecenia (Lekser -> Parser)

_Przekazanie przetworzonego polecenia_

Moduł kontroli przepływu wykonania (Tworzy procesy i potoki nienazwane)

_Przekazanie pojedynczych poleceń do wykonania_

Moduł wykonawczy (Wykonuje wyodrębnione polecenia)
