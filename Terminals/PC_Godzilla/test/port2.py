import tkinter as tk
from tkinter import ttk
import serial.tools.list_ports
import importlib

ORIGINAL_SCRIPT_NAME = "Godzilla_Mobil_2026_test" 

def get_detailed_ports():
    """Erstellt eine Liste mit Klarnamen und ein Mapping auf den Gerätenamen."""
    # include_links=True hilft bei virtuellen/gedoppelten Ports
    found_ports = serial.tools.list_ports.comports(include_links=True)
    
    port_map = {}
    for p in found_ports:
        # Erstellt einen String wie "COM3 - USB Serial Port (FTDI)"
        display_name = f"{p.device} - {p.description}"
        port_map[display_name] = p.device
    
    return port_map

def run_code():
    display_name = port_cb.get()
    if display_name:
        # Hole den echten Port-Namen (COMx) aus dem Mapping
        real_port = port_mapping[display_name]
        print(f"Starte Modul mit Port: {real_port}")
        
        root.destroy()
        
        # Dynamischer Import
        module = importlib.import_module(ORIGINAL_SCRIPT_NAME)
        
        # Übergabe an das Skript (Beispiel: als globale Variable im Zielmodul)
        # module.PORT = real_port 
        # module.main(real_port)

# GUI Setup
root = tk.Tk()
root.title("Port Selektor Pro")
root.geometry("450x180")

tk.Label(root, text="Verfügbare Hardware-Schnittstellen:", font=("Arial", 10, "bold")).pack(pady=10)

# Ports mit Details laden
port_mapping = get_detailed_ports()
display_options = list(port_mapping.keys())

port_cb = ttk.Combobox(root, values=display_options, state="readonly", width=50)
port_cb.pack(pady=5, padx=20)

if display_options:
    port_cb.current(0)
else:
    port_cb.set("Keine Ports gefunden")

tk.Button(root, text="Skript mit Auswahl ausführen", 
          command=run_code, bg="#2E7D32", fg="white", 
          font=("Arial", 10, "bold"), padx=10).pack(pady=20)

root.mainloop()
