import tkinter as tk
from tkinter import ttk
import serial.tools.list_ports
import importlib

# Hier deinen Dateinamen OHNE .py eintragen
# Beispiel: Wenn deine Datei 'messung.py' heißt, schreibe 'messung'
ORIGINAL_SCRIPT_NAME = "Godzilla_Mobil_2026_test" 

def run_code():
    selected_port = port_cb.get()
    if selected_port:
        print(f"Starte Modul mit Port: {selected_port}")
        root.destroy() # Schließt das Menü vor dem Start
        
        # Importiert dein Skript dynamisch
        module = importlib.import_module(ORIGINAL_SCRIPT_NAME)
        
        # Falls dein Skript eine Funktion hat, rufst du sie hier auf:
        # module.main(selected_port)
        # Falls dein Skript den Port über eine globale Variable steuert:
         #module.PORT = selected_port

# GUI Setup
root = tk.Tk()
root.title("Port Selektor")
root.geometry("350x150")

tk.Label(root, text="Wähle den COM-Port für das Skript:", font=("Arial", 10)).pack(pady=10)

# Ports automatisch erkennen
ports = [p.device for p in serial.tools.list_ports.comports()]
port_cb = ttk.Combobox(root, values=ports, state="readonly")
port_cb.pack(pady=5)
if ports: port_cb.current(0)

tk.Button(root, text="Skript mit Auswahl ausführen", command=run_code, bg="#4CAF50", fg="white").pack(pady=15)

root.mainloop()
