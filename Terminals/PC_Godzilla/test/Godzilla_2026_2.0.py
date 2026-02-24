import tkinter as tk
from tkinter import ttk, messagebox
import serial
import serial.tools.list_ports
import threading
import queue
import pygame
import time


# ==========================================================
# ======================= CONFIG ===========================
# ==========================================================

MODE_CONFIG = {
    "columns": 4,
    "tabs": {

        "Checkin": {
            "labels": [
                "Mensch start", "Mensch grün start", "Mensch gelb start", "Mensch rot start",
                "Mensch jetzt", "Mensch grün jetzt", "Mensch gelb jetzt", "Mensch rot jetzt",
                "Reset"
            ],
            "commands": [
                "h\n", "h1\n", "h2\n", "h3\n",
                "H\n", "H1\n", "H2\n", "H3\n",
                "v\n"
            ],
            "colors": [
                "lightblue", "lightgreen", "lightyellow", "magenta",
                "blue", "green", "yellow", "red",
                "darkblue"
            ]
        },

        "Buchen": {
            "labels": [
                "Update buchen", "Nanoclean", "Dekon", "Lifecleaner",
                "Blutwäsche", "Cleanray", "Drawback", "Redhead"
            ],
            "commands": [
                "b1\n", "b2\n", "b3\n", "b4\n",
                "b5\n", "b6\n", "b7\n", "b8\n"
            ],
            "colors": [
                "blue", "green", "yellow", "red",
                "darkblue", "darkgreen", "gold", "darkred"
            ]
        },

        "Analyse": {
            "labels": [
                "Analyse", "Analyse Ausführlich", "Analyse Nano", "Analyse Dekon",
                "Analyse Life", "Analyse Blood", "Analyse Clean", "Analyse alles"
            ],
            "commands": [
                "a1\n", "%\n", "a2\n", "a3\n",
                "a4\n", "a5\n", "a6\n", "a10\n"
            ],
            "colors": [
                "darkblue", "darkgreen", "gold", "darkred",
                "white", "darkgray", "gray", "grey"
            ]
        },

        "Data": {
            "labels": [
                "Konfig", "Checkinlog lesen", "Buchungslog lesen",
                "Medilog lesen", "Radio ON", "Radio OFF"
            ],
            "commands": [
                "u\n", "f\n", "g\n", "k\n",
                "s\n", "S\n"
            ],
            "colors": [
                "white", "darkgray", "gray",
                "grey", "green", "red"
            ]
        },

        "Manuell": {}
    }
}


MANUAL_PREFIX = {
    "Ray": "r",
    "Uhr": "j",
    "Rechte NBCLD": "o"
}


# ==========================================================
# ==================== SERIAL MANAGER ======================
# ==========================================================

class SerialManager:

    def __init__(self, port, baudrate=57600):
        self.port = port
        self.baudrate = baudrate
        self.queue = queue.Queue()
        self.running = True
        self.ser = None
        self.connect()

        self.thread = threading.Thread(target=self.read_loop, daemon=True)
        self.thread.start()

    def connect(self):
        try:
            self.ser = serial.Serial(self.port, self.baudrate, timeout=1)
        except Exception as e:
            print("Verbindungsfehler:", e)

    def read_loop(self):
        while self.running:
            try:
                if self.ser and self.ser.in_waiting:
                    line = self.ser.readline().decode(errors="ignore").strip()
                    self.queue.put(line)
            except:
                time.sleep(2)
                self.connect()

    def send(self, command):
        try:
            if self.ser and self.ser.is_open:
                self.ser.write(command.encode())
        except Exception as e:
            print("Sendefehler:", e)

    def close(self):
        self.running = False
        if self.ser:
            self.ser.close()


# ==========================================================
# ======================= MAIN GUI =========================
# ==========================================================

class GodzillaApp:

    def __init__(self, serial_manager):

        self.serial = serial_manager
        self.root = tk.Tk()
        self.root.title("GODZILLA 2.0")
        self.root.geometry("900x650")

        self.create_ui()
        self.process_queue()
        self.play_sound()

        self.root.protocol("WM_DELETE_WINDOW", self.on_close)
        self.root.mainloop()

    # ------------------------------------------------------

    def create_ui(self):

        # Monitor
        monitor_frame = tk.Frame(self.root)
        monitor_frame.pack(fill="both", expand=False, padx=10, pady=10)

        self.output = tk.Text(monitor_frame, height=15)
        self.output.pack(side="left", fill="both", expand=True)

        scrollbar = tk.Scrollbar(monitor_frame, command=self.output.yview)
        scrollbar.pack(side="right", fill="y")
        self.output.config(yscrollcommand=scrollbar.set)

        # Tabs
        self.tab_var = tk.StringVar(value="Checkin")
        tab_frame = tk.Frame(self.root)
        tab_frame.pack(pady=5)

        for tab in MODE_CONFIG["tabs"].keys():
            tk.Radiobutton(
                tab_frame,
                text=tab,
                value=tab,
                variable=self.tab_var,
                indicatoron=False,
                width=14,
                command=self.update_buttons
            ).pack(side="left", padx=4)

        # Button Area
        self.button_frame = tk.Frame(self.root)
        self.button_frame.pack(fill="both", expand=True, padx=10, pady=10)

        self.update_buttons()

    # ------------------------------------------------------

    def update_buttons(self):

        for widget in self.button_frame.winfo_children():
            widget.destroy()

        selected = self.tab_var.get()

        if selected == "Manuell":
            self.create_manual_area()
            return

        tab_data = MODE_CONFIG["tabs"][selected]
        columns = MODE_CONFIG["columns"]

        for i, label in enumerate(tab_data["labels"]):
            row = i // columns
            col = i % columns

            tk.Button(
                self.button_frame,
                text=label,
                bg=tab_data["colors"][i],
                font=("Arial", 11, "bold"),
                command=lambda cmd=tab_data["commands"][i]: self.serial.send(cmd)
            ).grid(row=row, column=col, sticky="nsew", padx=4, pady=4)

        for i in range(columns):
            self.button_frame.grid_columnconfigure(i, weight=1)

    # ------------------------------------------------------

    def create_manual_area(self):

        self.manual_var = tk.StringVar(value="Ray")

        option_frame = tk.Frame(self.button_frame)
        option_frame.grid(row=0, column=0, columnspan=4)

        for option in MANUAL_PREFIX.keys():
            tk.Radiobutton(
                option_frame,
                text=option,
                value=option,
                variable=self.manual_var
            ).pack(side="left", padx=10)

        self.entry = tk.Entry(self.button_frame, font=("Arial", 18), justify="right")
        self.entry.grid(row=1, column=0, columnspan=4, pady=10)

        buttons = [
            '7','8','9',
            '4','5','6',
            '1','2','3',
            '0','Clear','Enter'
        ]

        row = 2
        col = 0

        for b in buttons:

            if b == "Enter":
                action = self.send_manual
            elif b == "Clear":
                action = lambda: self.entry.delete(0, tk.END)
            else:
                action = lambda x=b: self.entry.insert(tk.END, x)

            tk.Button(
                self.button_frame,
                text=b,
                width=10,
                height=2,
                command=action
            ).grid(row=row, column=col, padx=5, pady=5)

            col += 1
            if col > 2:
                col = 0
                row += 1

    # ------------------------------------------------------

    def send_manual(self):
        value = self.entry.get()
        if value:
            prefix = MANUAL_PREFIX[self.manual_var.get()]
            self.serial.send(prefix + value + "\n")
            self.entry.delete(0, tk.END)

    # ------------------------------------------------------

    def process_queue(self):
        while not self.serial.queue.empty():
            line = self.serial.queue.get()
            self.output.insert(tk.END, line + "\n")
            self.output.see(tk.END)
        self.root.after(100, self.process_queue)

    # ------------------------------------------------------

    def play_sound(self):
        try:
            pygame.mixer.init()
            pygame.mixer.music.load("godzilla.wav")
            pygame.mixer.music.play()
        except:
            pass

    # ------------------------------------------------------

    def on_close(self):
        self.serial.close()
        self.root.destroy()


# ==========================================================
# ===================== PORT SELECTOR ======================
# ==========================================================

class PortSelector:

    def __init__(self):

        self.root = tk.Tk()
        self.root.title("Port Selektor Pro")
        self.root.geometry("450x200")

        tk.Label(
            self.root,
            text="Verfügbare Hardware-Schnittstellen:",
            font=("Arial", 10, "bold")
        ).pack(pady=10)

        self.port_map = self.get_ports()

        self.combo = ttk.Combobox(
            self.root,
            values=list(self.port_map.keys()),
            state="readonly",
            width=50
        )
        self.combo.pack(pady=5)

        if self.port_map:
            self.combo.current(0)

        tk.Button(
            self.root,
            text="Start GODZILLA 2.0",
            command=self.start_app,
            bg="#2E7D32",
            fg="white",
            font=("Arial", 10, "bold")
        ).pack(pady=20)

        self.root.mainloop()

    def get_ports(self):
        ports = serial.tools.list_ports.comports(include_links=True)
        return {f"{p.device} - {p.description}": p.device for p in ports}

    def start_app(self):
        selection = self.combo.get()
        if not selection:
            messagebox.showerror("Fehler", "Kein Port gewählt")
            return

        port = self.port_map[selection]
        self.root.destroy()

        serial_manager = SerialManager(port)
        GodzillaApp(serial_manager)


# ==========================================================

if __name__ == "__main__":
    PortSelector()
