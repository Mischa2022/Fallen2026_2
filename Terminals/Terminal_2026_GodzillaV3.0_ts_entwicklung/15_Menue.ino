
int print_menu(){
//Serial.println(F("c+Konfig = Konfigueberarbeiten"));
Serial.println(F("Optionen"));
Serial.println(F(""));
Serial.println(F("TERMINAL--------------------------"));
Serial.println(F("u aktuelle Konfig ausgeben "));
Serial.println(F("j Uhr stellen Seriell "));
Serial.println(F("f Checkinlog lesen"));
Serial.println(F("g Buchungslog lesen"));
Serial.println(F("k Medilog lesen"));
Serial.println(F("= Medilogs loeschen"));
Serial.println(F("{ Checkinlogs loeschen"));
Serial.println(F("} Buchungslogs loeschen"));
Serial.println(F(""));
Serial.println(F("DONGEL--------------------------"));
Serial.println(F("Checkin: 1=random gruen,2=random gelb,3=random rot"));
Serial.println(F("h+ Checkin Mensch ab Constart"));
Serial.println(F("H+ Checkin Mensch ab jetzt"));
Serial.println(F("v reset"));
Serial.println(F(""));
Serial.println(F("ANALYSE-------------------------"));
Serial.println(F("% Analyse ausfuehrlich"));
Serial.println(F("a+ wert Analyse "));
Serial.println(F(" 1 nur spieler infos ohne medi"));
Serial.println(F(" 2 Nur Nanoclean infos"));
Serial.println(F(" 3 Nur Dekon infos"));
Serial.println(F(" 4 Nur Lifecleaner infos"));
Serial.println(F(" 5 Nur Blutwaesche infos"));
Serial.println(F(" 6 Nur Cleanray infos"));
Serial.println(F(" 10 alle infos"));
Serial.println(F(""));
Serial.println(F("MEDIKATION----------------------"));
Serial.println(F("b+Wert Einnahme Medikament mit kontrolle tages/-Conmaximum wie ray-o-mat"));
Serial.println(F("1 update buchen")); 
Serial.println(F("2 Nanoclean    "));
Serial.println(F("3 Dekon        "));
Serial.println(F("4 Lifecleaner  "));
Serial.println(F("5 Blutwaesche  "));
Serial.println(F("6 Cleanray     "));
Serial.println(F("7 drawback     "));
Serial.println(F(""));
Serial.println(F("MANIPULATION--------------------"));
Serial.println(F("p korrektur von zeiten "));
Serial.println(F("m+Wert Typus aendern "));
Serial.println(F("100   = Mensch"));
Serial.println(F("360   = Mutant"));
Serial.println(F("r+ Wert  Raywert aendern  "));
Serial.println(F("1 random Gruen")); 
Serial.println(F("2 random Gelb"));
Serial.println(F("3 random Rot "));
Serial.println(F(">3 Raywert  "));
Serial.println(F("zbs r400000= raywert 400"));
Serial.println(F("l+ Stunden  Lifecleaner schreiben  "));
Serial.println(F("zbs l4= Lifecleaner fuer 4 Stunden"));
Serial.println(F(""));
Serial.println(F("RECHTE--------------------------"));
Serial.println(F("o+Wert Rechte fuer Medibuchungen"));
Serial.println(F("10000  = Nanoclean"));//
Serial.println(F("1000   = Blutwaesche"));//
Serial.println(F("100    = Cleanray"));//
Serial.println(F("10     = Lifecleaner"));//
Serial.println(F("1      = Dekon"));//
Serial.println(F("zbs 10001= Nanoclean+Dekon"));//
}


//*****************************************************************************************//
