/*Momentane Beobachtungen
 * Aufbau läuft momentan über Spieler-TAG auf MFRC522 und Medi-TAG über PN532
 * Abschluss in der Konfiguration "Spieler-TAG über PN532 und Medi-TAG auf MFRC522" ist noch nicht rund. Sobald durchgelaufen, muss alles an den Anfang.
 * Nochnicht der Fall. Es gibt nur einen kleinen break und dann erkennt der reader erneut den spieler_tag...
 */

/* Änderungen ( diesen Bereich kann man als kurze Info benutzen. Ich notiere hier, was ich später auch ins GIT schreibe)
 *  Funktionen wurden geklont. es gibt nun zwei main-funktionen, jenachdem welche konfiguration gewählt wurde.
 */

/*To Do´s ( immer mit Status und wer es gerade macht notieren)
 *Rauswerfen von unnötigen Funktionen (fertig)
 *Funktionen von MFRC522 für PN532 schreiben und umgekehrt--> PN532 ist stabiler und soll sich um die Spieler-TAGs kümmern (fertig)
 *Erstellen Servosteuerung Wippe (fertig)
 *Erstellen Servosteuerung Anzeige (fertig, vielleicht noch die anzeige und den servo feiner abstimmen)
 *Erstellen Relais-Steuerung (fertig) enthält Servosteuerung Anzeige(im test)
 *
 *Erstellen eines Updates ohne Medikament nach X Sekunden (in Arbeit)
 *    in Main_rayomat1 eingepflegt. Erkennt noch nicht, wenn innerhalb der Wartezeit, der Dongel entfernt wird.    
 *    in Main_rayomat2 eingepflegt. Erkennt  wenn innerhalb der Wartezeit, der Dongel entfernt wird.   
 *    
 *Update: 09.01.2023
 *buzzer_play wurde eingefügt und bildet die grundlage für spätere fehlersignale und auch tastentöne
 *Relais und anzeigeservo eingepflegt
 *Auf Medikamente warte eingebaut. Nach intervall wird dann mit Update weitergemacht
 */
