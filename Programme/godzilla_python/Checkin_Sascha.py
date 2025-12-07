import tkinter as tk
import serial
import threading
from tkinter import PhotoImage
from tkinter import messagebox
import pygame  # Hinzugefügt für die Soundwiedergabe

mode=1


# Definieren der Listen global

if mode ==0:
        max_columns = 1
        value_mode="Start"
        liste = ["Start"]

        listeA = ["Wähle Mode erst"]
        nachrichtA = ["\n"]

        farbenA = ["yellow"]

if mode ==1:
        max_columns = 3
        value_mode="Checkin"
        liste = ["Checkin","Analyse", "Data"]

        listeA = [ "Mensch start"
                  ,"Mensch jetzt"
                  ,"reset"]
        listeC = [ "Analyse"
                  ,"Analyse Ausführlich"
                  ,"Analyse komplett"]
        listeD = [ "Konfig"
                  ,"Checkinlog"
                  ,"Buchungslog"]

        
        nachrichtA = ["h\n","H\n","v\n"]
        farbenA = ["green", "yellow", "red"]

        listeB = []
        nachrichtB = []
        farbenB = []

        nachrichtC = ["a1\n", "%\n", "a10\n"]
        farbenC = ["darkblue", "darkgreen", "darkred"]

        
        nachrichtD = ["u\n", "f\n", "g\n"]
        farbenD = ["white", "darkgray", "gray"]

        listeE=[]
        nachrichtE = []
        farbenE = []

if mode ==2:
        max_columns = 4
        value_mode="Buchen"
        liste = ["Checkin", "Buchen", "Analyse", "Data", "Manuell"]

        listeA = ["Mensch start", "Mensch grün start", "Mensch gelb start", "Mensch rot start",
          "Mensch jetzt", "Mensch grün jetzt", "Mensch gelb jetzt", "Mensch rot jetzt", "reset"]
        nachrichtA = ["h\n", "h1\n", "h2\n", "h3\n", "H\n", "H1\n", "H2\n", "H3\n", "v\n"]

        farbenA = ["lightblue", "lightgreen", "lightyellow", "magenta", "blue", "green", "yellow", "red", "darkblue"]

        listeB = ["update buchen", "Nanoclean", "Dekon", "Lifecleaner", "Blutwaesche", "Cleanray", "drawback"]
        nachrichtB = ["b1\n", "b2\n", "b3\n", "b4\n", "b5\n", "b6\n", "b7\n"]
        farbenB = ["blue", "green", "yellow", "red", "darkblue", "darkgreen", "gold", "darkred"]

        listeC = ["Analyse", "Analyse Ausführlich", "Analyse Nano", "Analyse Dekon", "Analyse Life", "Analyse Blood", "Analyse Clean", "Analyse alles"]
        nachrichtC = ["a1\n", "%\n", "a2\n", "a3\n", "a4\n", "a5\n", "a6\n", "a10\n"]
        farbenC = ["darkblue", "darkgreen", "gold", "darkred", "white", "darkgray", "gray", "grey"]

        listeD = ["Konfig", "Checkinlog lesen", "Buchungslog lesen", "Medilog lesen"]
        nachrichtD = ["u\n", "f\n", "g\n", "k\n"]
        farbenD = ["white", "darkgray", "gray", "grey"]

        listeE=['Ray', 'Uhr', 'Rechte NBCLD']
        nachrichtE = ["r", "j", "o"]
        farbenE = ["lightgray","lightgray","lightgray","lightgray","lightgray","lightgray","lightgray","green","yellow","red","lightgray"]      

    


# Serielle Verbindung (stellen Sie sicher, dass COM-Port und Baudrate korrekt sind)
ser = serial.Serial('COM4', 57600, timeout=1)

# Funktion zum Senden von Daten über die serielle Verbindung
def send_command(command):
    output_text.delete("1.0", tk.END)
    ser.write(command.encode())  # Daten an das serielle Gerät senden

# Funktion zum Überwachen des seriellen Ports und Anzeigen der Daten
def serial_monitor():
    while True:
        if ser.in_waiting > 0:  # Wenn Daten vom seriellen Gerät empfangen wurden
            line = ser.readline().decode('utf-8').strip()  # Eine Zeile lesen und dekodieren
            output_text.insert(tk.END, line + '\n')  # Daten in das Textfeld einfügen
            output_text.yview(tk.END)  # Automatisch zum Ende scrollen

# Funktion zum Starten des seriellen Monitor-Threads
def start_serial_monitor():
    monitor_thread = threading.Thread(target=serial_monitor, daemon=True)  # Daemon-Thread
    monitor_thread.start()

# Funktion zum Hinzufügen eines Hintergrundbildes
def add_background_image():
    bg_image = PhotoImage(file="background.png")  # Pfad zum Bild anpassen

    # Label für das Hintergrundbild erstellen
    bg_label = tk.Label(root, image=bg_image)
    bg_label.place(relwidth=1, relheight=1)  # Hintergrundbild über die gesamte Fenstergröße legen

    # Das Bild im Label setzen, damit es nicht verloren geht
    bg_label.image = bg_image

# Funktion zum Erstellen der Radio-Buttons nebeneinander
def create_radio_buttons(frame):
    for i, text in enumerate(liste):
        radio_button = tk.Radiobutton(frame, text=text, value=text, variable=radio_var,
                                      command=lambda: update_buttons(),  font=("Arial", 20)) #bg="lightgray",
        radio_button.grid(row=0, column=i, padx=5, pady=5, sticky="w", ipadx=5, ipady=5)

# Funktion zum Erstellen der Eingabefelder und des Numblocks
def create_numblock_and_input(frame):
    global entry_display
    numblock = ['7', '8', '9','Enter','4', '5', '6', '0','1', '2', '3','Clear']
    button_colors= farbenE
    # Erstelle Eingabefeld für die Anzeige der Zahlen
    entry_display = tk.Entry(frame, font=("Arial", 20), width=20, justify="right")
    entry_display.grid(row=0, column=0, columnspan=5, padx=10, pady=10)

    # Erstelle Buttons für den Numblock
    row = 2
    col = 0
    color_index =0
    for button in numblock:
        if button == 'Enter':
            btn = tk.Button(frame, text=button, width=10, height=2, font=("Arial", 10), 
                            command=lambda: enter_pressed())  # Übergabe der Funktion enter_pressed
        elif button == 'Clear':
            btn = tk.Button(frame, text=button, width=10, height=2, font=("Arial", 10), command=clear_pressed)
        else:
            btn = tk.Button(frame, text=button,bg=button_colors[color_index], width=10, height=2, font=("Arial", 10), command=lambda num=button: num_pressed(num))
            color_index += 1
        btn.grid(row=row, column=col, padx=5, pady=5)
        col += 1
        if col > 3:
            col = 0
            row += 1

# Funktionen für die Numblock-Interaktionen
def enter_pressed():
    # Hole den aktuellen Wert aus dem Eingabefeld
    eingegebene_zahlen = entry_display.get()
    
    # Überprüfe, welcher Radio-Button in der "Manuell"-Sektion ausgewählt wurde
    selected_option = radio_var_A_B_C.get()  # Wert des A/B/C Radio-Buttons
    
    # Erstelle die Nachricht basierend auf der Auswahl
    if selected_option == "Ray":
        nachricht = nachrichtE[0] + eingegebene_zahlen + "\n"
        entry_display.delete(0, tk.END)
    elif selected_option == "Uhr":
        nachricht = nachrichtE[1] + eingegebene_zahlen + "\n"
        entry_display.delete(0, tk.END)
    elif selected_option == "Rechte NBCLD":
        nachricht = nachrichtE[2] + eingegebene_zahlen + "\n"
        entry_display.delete(0, tk.END)
    else:
        nachricht = ""  # Falls keine Auswahl getroffen wurde
        entry_display.delete(0, tk.END)
    
    if nachricht:
        send_command(nachricht)  # Sende die Nachricht an die serielle Verbindung
    else:
        print("Keine gültige Auswahl getroffen oder keine Nachricht erstellt.")

def num_pressed(num):
    current_text = entry_display.get()  # Hole den aktuellen Text im Eingabefeld
    new_text = current_text + num  # Hänge die gedrückte Zahl an den Text an
    entry_display.delete(0, tk.END)  # Lösche den aktuellen Text
    entry_display.insert(tk.END, new_text)  # Füge den neuen Text ein

def clear_pressed():
    entry_display.delete(0, tk.END)  # Lösche das Eingabefeld

# Funktion zum Erstellen der Radio-Buttons A, B, C
def create_radio_buttons_A_B_C(frame):
    global radio_var_A_B_C  # Globale Variable für radio_var_A_B_C
    radio_frame_A_B_C = tk.Frame(frame)
    radio_frame_A_B_C.grid(row=1, column=0, columnspan=3, padx=10, pady=10, sticky="nsew")  # A/B/C in der Mitte
    radio_var_A_B_C = tk.StringVar(value="Ray")  # Standard auf A setzen

    for i, option in enumerate(listeE):  # A, B, C Radio-Buttons erstellen
        radio_button = tk.Radiobutton(radio_frame_A_B_C, text=option, value=option, variable=radio_var_A_B_C,  font=("Arial", 15)) #bg="lightgray",
        radio_button.grid(row=0, column=i, padx=10, pady=10, sticky="w", ipadx=5, ipady=5)

# Funktion zum Erstellen und Aktualisieren der Buttons basierend auf der Auswahl
def update_buttons():
    global data_frame  # Declare data_frame as global so we can initialize it once

    # Stelle sicher, dass data_frame nur einmal erstellt wird
    if not 'data_frame' in globals():
        data_frame = tk.Frame(root)

    # Lösche alte Widgets
    for widget in button_frame.winfo_children():
        widget.grid_forget()  # Entfernt die bestehenden Buttons

    selected_option = radio_var.get()
    if selected_option == "Checkin":
        button_list = listeA
        button_colors = farbenA
        button_commands = nachrichtA
    elif selected_option == "Buchen":
        button_list = listeB
        button_colors = farbenB
        button_commands = nachrichtB
    elif selected_option == "Analyse":
        button_list = listeC
        button_colors = farbenC
        button_commands = nachrichtC
    elif selected_option == "Data":
        button_list = listeD
        button_colors = farbenD
        button_commands = nachrichtD
    elif selected_option == "Manuell":
        button_list=[]
           
        # Erstelle Numblock und Eingabefeld sowie A/B/C Radiobuttons, wenn "Manuell" ausgewählt ist
        data_frame.grid(row=2, column=0, columnspan=3, padx=10, pady=10)  # Zeige den Data-Bereich an
        create_numblock_and_input(data_frame)
        
        radio_var_A_B_C = tk.StringVar(value="Ray")
        create_radio_buttons_A_B_C(data_frame)
    else:
        return

    # Dynamisch Buttons erstellen und anordnen
    total_buttons = len(button_list)
    
    # Berechnen der benötigten Zeilen und Spalten für das Grid
    
    rows = (total_buttons + max_columns - 1) // max_columns  # Zeilenanzahl berechnen
    cols = min(total_buttons, max_columns)  # Maximale Spaltenanzahl ist 4

    # Dynamisch Buttons erstellen und anordnen
    for i in range(total_buttons):
        row = i // max_columns  # Zeilenberechnung
        col = i % max_columns   # Spaltenberechnung
        button = tk.Button(button_frame, text=button_list[i], command=lambda cmd=button_commands[i]: send_command(cmd),
                           bg=button_colors[i], font=("Arial", 15,"bold"))  # Schriftgröße auf 10 setzen (50% kleiner)
        button.grid(row=row, column=col, padx=5, pady=5, sticky="nsew")

    # Layout für flexible Größen der Buttons
    for i in range(rows):
        button_frame.grid_rowconfigure(i, weight=1, uniform="equal")
    for i in range(cols):  # Maximale Spaltenanzahl
        button_frame.grid_columnconfigure(i, weight=1, uniform="equal")

    # Aktivieren oder Deaktivieren des Numblocks und der Radio Buttons A/B/C je nach Auswahl
    if selected_option == "Manuell":
        # Nur dann sichtbar und aktiv
        radio_var_A_B_C = tk.StringVar(value="Ray")
        data_frame.grid(row=2, column=0, columnspan=3, padx=10, pady=10)  # Zeige den Data-Bereich an
        create_radio_buttons_A_B_C(data_frame)
    else:
        data_frame.grid_forget()  # Verstecke den Data-Bereich


# Tkinter-GUI erstellen
def create_gui():
    global output_text, scrollbar, button_frame, radio_frame, radio_var, root
    root = tk.Tk()
    root.title("   GODZILLA   ")
    #root.geometry("1200x920")
    root.geometry("600x500")

    # Füge Hintergrundbild hinzu
    add_background_image()

    # Erstellen eines Frames für den seriellen Monitor
    frame = tk.Frame(root, bg="green")  # Hintergrundfarbe für den Frame
    frame.grid(row=0, column=0, columnspan=3, padx=10, pady=10, sticky="nsew")

    # Textfeld zum Anzeigen der empfangenen Daten
    output_text = tk.Text(frame, width=56, height=15, wrap=tk.WORD, font=("Arial", 10))  # Höhe des seriellen Monitors erhöhen
    output_text.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

    # Bildlaufleiste hinzufügen
    scrollbar = tk.Scrollbar(frame, command=output_text.yview)
    scrollbar.config(width=60)
    scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
    output_text.config(yscrollcommand=scrollbar.set)

    # Erstellen von Frames für die Buttons und die Radio-Buttons
    button_frame = tk.Frame(root)
    button_frame.grid(row=2, column=0, columnspan=3, padx=10, pady=10, sticky="nsew")

    radio_frame = tk.Frame(root)
    radio_frame.grid(row=1, column=0, columnspan=3, padx=10, pady=10, sticky="nsew")

    # Radio-Buttons erstellen
    
    radio_var = tk.StringVar(value=value_mode)  # Default-Wert auf "Buchen"
    create_radio_buttons(radio_frame)

    # Setzen einer festen Größe für den Radio-Button Bereich (keine Skalierung)
    radio_frame.grid_propagate(False)  # Verhindert die automatische Größenänderung des Frames

    # Sicherstellen, dass die Spalten im radio_frame gleichmäßig verteilt werden
    for i in range(len(liste)):
        radio_frame.grid_columnconfigure(i, weight=1, uniform="equal")

    # Starten der Buttons mit der Auswahl "Buchen"
    update_buttons()

    # Starten des seriellen Monitors
    start_serial_monitor()

    # Layout für das Fenster anpassen
    root.grid_rowconfigure(0, weight=2, uniform="equal")  # Serieller Monitor bekommt 2x Gewicht
    root.grid_rowconfigure(1, weight=0, uniform="equal")  # Radio Buttons mit geringem Gewicht
    root.grid_rowconfigure(2, weight=3, uniform="equal")  # Buttons bekommen mehr Gewicht
    root.grid_columnconfigure(0, weight=4, uniform="equal")
    root.grid_columnconfigure(1, weight=5, uniform="equal")
    root.grid_columnconfigure(2, weight=3, uniform="equal")

    root.mainloop()

# Funktion zum Abspielen des Sounds beim Start
def play_startup_sound():
    pygame.mixer.init()  # Initialisiert den Mixer für die Audiowiedergabe
    pygame.mixer.music.load("godzilla.wav")  # Lade eine Audiodatei
    pygame.mixer.music.play()  # Spiele den Sound ab

# Starte die GUI
play_startup_sound()  # Starte den Sound
create_gui()  # Starte die GUI
