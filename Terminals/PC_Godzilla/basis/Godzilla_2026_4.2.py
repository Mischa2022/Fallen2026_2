import tkinter as tk
from tkinter import ttk, messagebox
import serial
import serial.tools.list_ports
import threading
import queue
import pygame
import time
import logging
from PIL import Image, ImageTk

# ==========================================================
# CONFIG
# ==========================================================

APP_TITLE = "GODZILLA 4.0 Professional"
BAUDRATE = 57600
FULLSCREEN = False
COLUMNS = 4

BUTTON_COLORS = {
    "Mensch start":{"bg": "#ffffff", "fg": "black", "hover_bg": "#999999"},
    "Mensch grün start":{"bg": "#00ff00", "fg": "black", "hover_bg": "#008000"},
    "Mensch gelb start":{"bg": "#ffff00", "fg": "black", "hover_bg": "#FFA500"},
    "Mensch rot start":{"bg": "#ff0000", "fg": "black", "hover_bg": "#8B0000"},
    "Mensch jetzt":{"bg": "#999999", "fg": "black", "hover_bg": "#474747"},
    "Mensch grün jetzt":{"bg": "#00ff00", "fg": "black", "hover_bg": "#008000"},
    "Mensch gelb jetzt":{"bg": "#ffff00", "fg": "black", "hover_bg": "#FFA500"},
    "Mensch rot jetzt":{"bg": "#ff0000", "fg": "black", "hover_bg": "#8B0000"},
    "Update buchen":{"bg": "#ffffff", "fg": "black", "hover_bg": "#999999"},
    "Nanoclean":{"bg": "#ffff00", "fg": "black", "hover_bg": "#FFA500"},
    "Dekon":{"bg": "#00ff00", "fg": "black", "hover_bg": "#008000"},
    "Lifecleaner":{"bg": "#009999", "fg": "black", "hover_bg": "#0099ff"},
    "Blutwäsche":{"bg": "#cc0000", "fg": "black", "hover_bg": "#ff0000"},
    "Cleanray":{"bg": "#0033ff", "fg": "white", "hover_bg": "#003399"},
    "Drawback":{"bg": "#000000", "fg": "white", "hover_bg": "#999999"},
    "Redhead":{"bg": "#5A0000", "fg": "white", "hover_bg": "#7B0000"},
    "Analyse":{"bg": "#ffffff", "fg": "black", "hover_bg": "#999999"},
    "Analyse Ausführlich":{"bg": "#ccffff", "fg": "black", "hover_bg": "#ccccff"},
    "Analyse Nano":{"bg": "#ffff00", "fg": "black", "hover_bg": "#FFA500"},
    "Analyse Dekon":{"bg": "#00ff00", "fg": "black", "hover_bg": "#008000"},
    "Analyse Life":{"bg": "#009999", "fg": "black", "hover_bg": "#0099ff"},
    "Analyse Blood":{"bg": "#cc0000", "fg": "black", "hover_bg": "#ff0000"},
    "Analyse Clean":{"bg": "#0033ff", "fg": "white", "hover_bg": "#003399"},
    "Analyse alles":{"bg": "#000000", "fg": "white", "hover_bg": "#999999"},
    "1":{"bg": "#00ff00", "fg": "black", "hover_bg": "#008000"},
    "2":{"bg": "#ffff00", "fg": "black", "hover_bg": "#FFA500"},
    "3":{"bg": "#ff0000", "fg": "black", "hover_bg": "#8B0000"},
    "Clear": {"bg": "#8B0000", "fg": "white", "hover_bg": "#A00000"},
    "default":{"bg": "#999999", "fg": "black", "hover_bg": "#474747"},
    "Reset": {"bg": "#8B0000", "fg": "white", "hover_bg": "#A00000"},
    "Enter": {"bg": "#006400", "fg": "white", "hover_bg": "#008000"},
    "Radio ON": {"bg": "#006400", "fg": "white", "hover_bg": "#008000"},
    "Radio OFF": {"bg": "#5A0000", "fg": "white", "hover_bg": "#7B0000"},
}

TAB_CONFIG = {
    "Checkin": {
        "labels": ["Mensch start","Mensch grün start","Mensch gelb start","Mensch rot start",
                   "Mensch jetzt","Mensch grün jetzt","Mensch gelb jetzt","Mensch rot jetzt","Reset"],
        "commands": ["h\n","h1\n","h2\n","h3\n","H\n","H1\n","H2\n","H3\n","v\n"]
    },
    "Buchen": {
        "labels": ["Update buchen","Nanoclean","Dekon","Lifecleaner",
                   "Blutwäsche","Cleanray","Drawback","Redhead"],
        "commands": ["b1\n","b2\n","b3\n","b4\n","b5\n","b6\n","b7\n","b8\n"]
    },
    "Analyse": {
        "labels": ["Analyse","Analyse Ausführlich","Analyse Nano","Analyse Dekon",
                   "Analyse Life","Analyse Blood","Analyse Clean","Analyse alles"],
        "commands": ["a1\n","%\n","a2\n","a3\n","a4\n","a5\n","a6\n","a10\n"]
    },
    "Data": {
        "labels": ["Konfig","Checkinlog lesen","Buchungslog lesen",
                   "Medilog lesen","Radio ON","Radio OFF"],
        "commands": ["u\n","f\n","g\n","k\n","s\n","S\n"]
    },
    "Manuell": {
        "labels": ["7","8","9","4","5","6","1","2","3","Clear","0","Enter"],
        "commands": []
    }
}

MANUAL_PREFIX = {"Ray": "r","Uhr": "j","Rechte RNBCLD": "o"}

# ==========================================================
# SERIAL
# ==========================================================

class SerialManager:
    def __init__(self, port):
        self.queue = queue.Queue()

        try:
            self.ser = serial.Serial(port, BAUDRATE, timeout=1)
            self.connected = True
        except:
            self.ser = None
            self.connected = False

        threading.Thread(target=self.read_loop, daemon=True).start()

    def read_loop(self):
        while True:
            try:
                if self.ser and self.ser.in_waiting:
                    self.queue.put(self.ser.readline().decode(errors="ignore").strip())
            except:
                pass

    def send(self, cmd):
        try:
            if self.ser:
                self.ser.write(cmd.encode())
        except:
            pass

# ==========================================================
# APP
# ==========================================================

class GodzillaApp:

    def __init__(self, serial):
        self.serial = serial
        self.root = tk.Tk()
        self.root.title(APP_TITLE)
        self.root.geometry("1000x700")

        self.root.grid_rowconfigure(0, weight=3)
        self.root.grid_rowconfigure(1, weight=0)
        self.root.grid_rowconfigure(2, weight=2)
        self.root.grid_columnconfigure(0, weight=1)

        self.tab_var = tk.StringVar(value="Checkin")

        self.create_ui()
        self.process_queue()

        self.root.mainloop()

    # ======================================================
    # UI
    # ======================================================

    def create_ui(self):

        self.output = tk.Text(
            self.root,
            bg="#111111",
            fg="#00FF00"
        )
        self.output.grid(row=0, column=0, sticky="nsew", padx=10, pady=10)

        tab_frame = ttk.Frame(self.root)
        tab_frame.grid(row=1, column=0)

        for tab in TAB_CONFIG:
            ttk.Radiobutton(
                tab_frame,
                text=tab,
                value=tab,
                variable=self.tab_var,
                command=self.update_buttons
            ).pack(side="left")

        self.button_frame = ttk.Frame(self.root)
        self.button_frame.grid(row=2, column=0, sticky="nsew")

        self.update_buttons()

    # ======================================================
    # BUTTONS + MANUELL FIX
    # ======================================================

    def update_buttons(self):

        for w in self.button_frame.winfo_children():
            w.destroy()

        if self.tab_var.get() == "Manuell":
            self.create_manual()
            return

        cfg = TAB_CONFIG[self.tab_var.get()]

        for i, label in enumerate(cfg["labels"]):

            def action(cmd=cfg["commands"][i]):
                self.serial.send(cmd)
                self.output.delete("1.0", tk.END)

            color = BUTTON_COLORS.get(label, BUTTON_COLORS["default"])

            tk.Button(
                self.button_frame,
                text=label,
                command=action,
                bg=color["bg"],
                fg=color["fg"],
                activebackground=color["hover_bg"],
                font=("Arial", 11, "bold")
            ).grid(row=i//COLUMNS, column=i%COLUMNS, sticky="nsew", padx=4, pady=4)

        for i in range(COLUMNS):
            self.button_frame.grid_columnconfigure(i, weight=1)

    # ======================================================
    # NUMPAD (FIXED)
    # ======================================================

    def create_manual(self):

        for w in self.button_frame.winfo_children():
            w.destroy()

        self.manual_var = tk.StringVar(value="Ray")

        prefix = ttk.Frame(self.button_frame)
        prefix.grid(row=0, column=0, columnspan=3)

        for p in MANUAL_PREFIX:
            ttk.Radiobutton(prefix, text=p, value=p, variable=self.manual_var).pack(side="left")

        self.entry = ttk.Entry(self.button_frame, font=("Arial", 18))
        self.entry.grid(row=1, column=0, columnspan=3, sticky="ew")

        buttons = [
            "7","8","9",
            "4","5","6",
            "1","2","3",
            "Clear","0","Enter"
        ]

        row = 2
        col = 0

        for b in buttons:

            def cmd(x=b):
                if x == "Clear":
                    self.entry.delete(0, tk.END)

                elif x == "Enter":
                    prefix = MANUAL_PREFIX[self.manual_var.get()]
                    self.serial.send(prefix + self.entry.get() + "\n")
                    self.entry.delete(0, tk.END)

                else:
                    self.entry.insert(tk.END, x)

            tk.Button(
                self.button_frame,
                text=b,
                command=cmd,
                bg="#999999",
                fg="black",
                font=("Arial", 11, "bold")
            ).grid(row=row, column=col, sticky="nsew", padx=4, pady=4)

            col += 1
            if col > 2:
                col = 0
                row += 1

        for i in range(3):
            self.button_frame.grid_columnconfigure(i, weight=1)

    # ======================================================
    # SERIAL OUTPUT
    # ======================================================

    def process_queue(self):
        while not self.serial.queue.empty():
            self.output.insert(tk.END, self.serial.queue.get() + "\n")
            self.output.see(tk.END)

        self.root.after(100, self.process_queue)

# ==========================================================
# PORT SELECTOR
# ==========================================================

class PortSelector:

    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Port Selector")

        ttk.Label(self.root, text="Port auswählen").pack()

        self.map = {
            f"{p.device} - {p.description}": p.device
            for p in serial.tools.list_ports.comports()
        }

        self.combo = ttk.Combobox(self.root, values=list(self.map.keys()), state="readonly")
        self.combo.pack()

        if self.map:
            self.combo.current(0)

        tk.Button(self.root, text="Start", command=self.start).pack()

        self.root.mainloop()

    def start(self):
        sel = self.combo.get()
        self.root.destroy()
        GodzillaApp(SerialManager(self.map[sel]))

# ==========================================================
# START
# ==========================================================

if __name__ == "__main__":
    PortSelector()
