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
# ======================= CONFIG ===========================
# ==========================================================

APP_TITLE = "GODZILLA 3.2 Professional"
BAUDRATE = 57600
FULLSCREEN = True
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
    "Manuell": {}
}

MANUAL_PREFIX = {"Ray": "r","Uhr": "j","Rechte RNBCLD": "o"}

logging.basicConfig(filename="godzilla.log",
                    level=logging.INFO,
                    format="%(asctime)s - %(message)s")

# ==========================================================
# ==================== SERIAL MANAGER ======================
# ==========================================================

class SerialManager:
    def __init__(self, port):
        self.port = port
        self.ser = None
        self.queue = queue.Queue()
        self.running = True
        self.connected = False
        self.connect()
        self.thread = threading.Thread(target=self.read_loop, daemon=True)
        self.thread.start()

    def connect(self):
        try:
            self.ser = serial.Serial(self.port, BAUDRATE, timeout=1)
            self.connected = True
        except:
            self.connected = False

    def read_loop(self):
        while self.running:
            try:
                if self.ser and self.ser.in_waiting:
                    line = self.ser.readline().decode(errors="ignore").strip()
                    self.queue.put(line)
            except:
                self.connected = False
                time.sleep(2)
                self.connect()

    def send(self, command):
        try:
            if self.ser and self.ser.is_open:
                self.ser.write(command.encode())
        except:
            self.connected = False

    def close(self):
        self.running = False
        if self.ser:
            self.ser.close()

# ==========================================================
# ======================= MAIN APP =========================
# ==========================================================

class GodzillaApp:

    def __init__(self, serial_manager):

        self.serial = serial_manager
        self.root = tk.Tk()
        self.root.title(APP_TITLE)
        self.root.geometry("1000x700")

        if FULLSCREEN:
            self.root.attributes("-fullscreen", True)

        self.root.bind("<F11>", lambda e: self.toggle_fullscreen())
        self.root.bind("<Escape>", lambda e: self.root.destroy())

        self.setup_style()

        self.radio_on = True

        self.create_ui()
        self.process_queue()
        self.update_status()
        self.play_sound()

        self.root.protocol("WM_DELETE_WINDOW", self.on_close)
        self.root.mainloop()

    def setup_style(self):
        self.style = ttk.Style()
        self.style.theme_use("clam")
        self.bg_color = "#1E1E1E"
        self.root.configure(bg=self.bg_color)

    def create_ui(self):

        self.output = tk.Text(self.root,height=36,bg="#121212",
                              fg="#00FF00",insertbackground="white")
        self.output.pack(fill="x", padx=10, pady=10)

        self.tab_var = tk.StringVar(value="Checkin")

        tab_frame = ttk.Frame(self.root)
        tab_frame.pack(pady=5)

        import tkinter.font as tkfont
        tab_font = tkfont.Font(family="Arial", size=30, weight="bold")

        for tab in TAB_CONFIG.keys():
            ttk.Radiobutton(tab_frame,text=tab,value=tab,
                            variable=self.tab_var,
                            command=self.update_buttons,
                            width=15,
                            padding=10,
                            style="Tab.TButton").pack(side="left", padx=5)

        self.style.configure("Tab.TButton", font=tab_font)

        self.button_frame = ttk.Frame(self.root)
        self.button_frame.pack(fill="both", expand=True, padx=10, pady=10)

        self.status_var = tk.StringVar()
        self.status_bar = ttk.Label(self.root, textvariable=self.status_var)
        self.status_bar.pack(fill="x")

        radio_frame = ttk.Frame(self.root)
        radio_frame.pack(pady=5)

        self.radio_toggle_button = ttk.Button(
            radio_frame,
            text="Radio ON",
            command=self.toggle_radio
        )
        self.radio_toggle_button.pack(side="left", padx=10)

        self.radio_canvas = tk.Canvas(
            radio_frame, width=50, height=50,
            bg=self.bg_color, highlightthickness=0
        )
        self.radio_canvas.pack(side="left")

        self.radio_led = self.radio_canvas.create_oval(
            5, 5, 50, 50, fill="#00FF00"
        )

        self.update_radio_led()

        ttk.Button(self.root,text="✖ Schließen",
                   command=self.on_close).pack(anchor="ne", padx=10, pady=10)

        self.update_buttons()

    # ================= RADIO =================

    def toggle_radio(self):
        if self.radio_on:
            self.set_radio(False, "S\n")
        else:
            self.set_radio(True, "s\n")

    def set_radio(self, state, command):
        self.radio_on = state
        self.update_radio_led()
        self.send_command(command)

    def update_radio_led(self):
        if self.radio_on:
            self.radio_canvas.itemconfig(self.radio_led, fill="#00FF00")
            self.radio_toggle_button.config(text="Radio ON")
        else:
            self.radio_canvas.itemconfig(self.radio_led, fill="#FF0000")
            self.radio_toggle_button.config(text="Radio OFF")

    # (Rest bleibt identisch wie dein vorheriger Code: update_buttons, create_manual, etc.)

    def update_buttons(self):
        for widget in self.button_frame.winfo_children():
            widget.destroy()

        selected = self.tab_var.get()
        if selected == "Manuell":
            self.create_manual()
            return

        config = TAB_CONFIG[selected]

        for i, label in enumerate(config["labels"]):
            row = i // COLUMNS
            col = i % COLUMNS
            style_name = self.create_button_style(label)

            if label == "Radio ON":
                cmd = config["commands"][i]
                action = lambda c=cmd: self.set_radio(True, c)
            elif label == "Radio OFF":
                cmd = config["commands"][i]
                action = lambda c=cmd: self.set_radio(False, c)
            else:
                cmd = config["commands"][i]
                action = lambda c=cmd: self.send_command(c)

            ttk.Button(self.button_frame,text=label,
                       style=style_name,
                       command=action).grid(row=row,column=col,
                                            sticky="nsew",padx=5,pady=5)

        for i in range(COLUMNS):
            self.button_frame.grid_columnconfigure(i, weight=1)

    def create_button_style(self, text):
        color_config = BUTTON_COLORS.get(text, BUTTON_COLORS["default"])
        style_name = f"{text}.TButton"
        self.style.configure(style_name,
                             background=color_config["bg"],
                             foreground=color_config["fg"],
                             font=("Arial", 18, "bold"),
                             padding=7)
        self.style.map(style_name,
                       background=[("active", color_config.get("hover_bg",
                                                               color_config["bg"]))])
        return style_name

    def create_manual(self):
        for widget in self.button_frame.winfo_children():
            widget.destroy()

        self.manual_var = tk.StringVar(value="Ray")
        option_frame = ttk.Frame(self.button_frame)
        option_frame.grid(row=0,column=0,columnspan=3,pady=5)

        for option in MANUAL_PREFIX:
            ttk.Radiobutton(option_frame,text=option,value=option,
                            variable=self.manual_var).pack(side="left", padx=15)

        self.entry = ttk.Entry(self.button_frame,font=("Arial",18),justify="right")
        self.entry.grid(row=1,column=0,columnspan=3,pady=10,sticky="ew")

        buttons = ['7','8','9','4','5','6','1','2','3','Clear','0','Enter']
        row = 2; col = 0
        for b in buttons:
            if b=="Enter": action = self.send_manual
            elif b=="Clear": action = lambda: self.entry.delete(0, tk.END)
            else: action = lambda x=b: self.entry.insert(tk.END,x)
            style_name = self.create_button_style(b)
            ttk.Button(self.button_frame,text=b,style=style_name,
                       command=action).grid(row=row,column=col,padx=6,pady=6,sticky="nsew")
            col+=1
            if col>2: col=0; row+=1
        for i in range(3): self.button_frame.grid_columnconfigure(i, weight=1)

    def send_manual(self):
        value = self.entry.get()
        if value:
            prefix = MANUAL_PREFIX[self.manual_var.get()]
            self.send_command(prefix+value+"\n")
            self.entry.delete(0, tk.END)

    def send_command(self, command):
        self.output.delete("1.0", tk.END)
        self.serial.send(command)

    def process_queue(self):
        while not self.serial.queue.empty():
            line = self.serial.queue.get()
            self.output.insert(tk.END,line+"\n")
            self.output.see(tk.END)
        self.root.after(100,self.process_queue)

    def update_status(self):
        if self.serial.connected:
            self.status_var.set("● Verbunden mit "+self.serial.port)
        else:
            self.status_var.set("● Getrennt – Reconnect läuft...")
        self.root.after(1000,self.update_status)

    def toggle_fullscreen(self):
        current = self.root.attributes("-fullscreen")
        self.root.attributes("-fullscreen",not current)

    def play_sound(self):
        try:
            pygame.mixer.init()
            pygame.mixer.music.load("godzilla.wav")
            pygame.mixer.music.play()
        except:
            pass

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

        # Hintergrundbild
        self.original_bg = Image.open("background.png")
        self.bg_image = ImageTk.PhotoImage(self.original_bg)

        self.bg_label = tk.Label(self.root, image=self.bg_image)
        self.bg_label.place(x=0, y=0, relwidth=1, relheight=1)

        self.root.bind("<Configure>", self.resize_background)

        ttk.Label(self.root,text="Hardware-Port auswählen").pack(pady=10)

        self.port_map = self.get_ports()

        self.combo = ttk.Combobox(self.root,
                                  values=list(self.port_map.keys()),
                                  state="readonly",width=50)
        self.combo.pack(pady=10)

        if self.port_map:
            self.combo.current(0)

        ttk.Button(self.root,
                   text="Start GODZILLA 3.2",
                   command=self.start_app).pack(pady=20)

        self.root.mainloop()

    def resize_background(self, event):
        resized = self.original_bg.resize(
            (event.width, event.height),
            Image.LANCZOS
        )
        self.bg_image = ImageTk.PhotoImage(resized)
        self.bg_label.config(image=self.bg_image)

    def get_ports(self):
        ports = serial.tools.list_ports.comports(include_links=True)
        return {f"{p.device} - {p.description}":p.device for p in ports}

    def start_app(self):
        selection = self.combo.get()
        if not selection:
            messagebox.showerror("Fehler","Kein Port gewählt")
            return
        port = self.port_map[selection]
        self.root.destroy()
        serial_manager = SerialManager(port)
        GodzillaApp(serial_manager)

if __name__ == "__main__":
    PortSelector()
