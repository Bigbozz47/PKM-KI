import tkinter as tk
from tkinter import ttk

# Data barang dalam dictionary (contoh)
data_barang = {
    '8992761002015': {'nama': 'Coca Cola', 'harga': 6000},
    '8998009010224': {'nama': 'Ultra Milk', 'harga': 7000},
    '8885013130485': {'nama': 'Coffe Crispy', 'harga': 3500},
}

# Data belanjaan dalam bentuk list
belanjaan = []

def hitung_total():
    total_harga = 0
    for item in belanjaan:
        total_harga += item['total']
    total_label.config(text=f"Total Harga Belanjaan: Rp{total_harga:.2f}")

def tambah_ke_tabel(id_barang, kuantitas):
    if id_barang in data_barang:
        harga_barang = data_barang[id_barang]['harga']
        nama_barang = data_barang[id_barang]['nama']
        total = harga_barang * kuantitas

        # Cek apakah barang sudah ada dalam daftar belanjaan
        for item in belanjaan:
            if item['id'] == id_barang:
                item['kuantitas'] += kuantitas
                item['total'] += total
                break
        else:
            belanjaan.append({'id': id_barang, 'nama': nama_barang, 'harga': harga_barang, 'kuantitas': kuantitas, 'total': total})

        update_tabel()
        hitung_total()
        
    else:
        total_label.config(text="ID Barang tidak valid!")

def on_barcode_scan(event):
    id_barang = id_entry.get()
    tambah_ke_tabel(id_barang, 1)
    id_entry.delete(0, 'end')  # Menghapus isi input field setelah pemindaian

def update_tabel():
    for i in tree.get_children():
        tree.delete(i)
    for index, item in enumerate(belanjaan):
        tree.insert("", "end", values=(f"{index+1}", item['nama'], item['harga'], item['kuantitas'], item['total']))

# Membuat jendela utama
window = tk.Tk()
window.title('Mart Trolley')
window.geometry('600x400')

#title
title_label = ttk.Label(master=window, text='Smart Trolley', font='calibri 40')
title_label.pack()

# Membuat label dan input field untuk ID barang
id_label = ttk.Frame(master=window)
id_label.pack(pady=10)

id_entry = ttk.Entry(master=id_label)
id_entry.pack(side='left', padx=10)

# Event binding saat pemindai barcode memasukkan data
id_entry.bind('<KeyRelease>', on_barcode_scan)

# Label untuk menampilkan informasi barang
info_barang = tk.Label(window, text="")
info_barang.pack()

# Tabel untuk menampilkan daftar belanjaan dengan scrollbar
frame = ttk.Frame(window)
frame.pack(padx=10, pady=10, fill='both', expand=True)

tree = ttk.Treeview(frame, columns=("No.", "Nama Barang", "Harga", "Kuantitas", "Total"), show="headings")
tree.heading("No.", text="No.")
tree.heading("Nama Barang", text="Nama Barang")
tree.heading("Harga", text="Harga")
tree.heading("Kuantitas", text="Kuantitas")
tree.heading("Total", text="Total")

vsb = ttk.Scrollbar(frame, orient="vertical", command=tree.yview)
vsb.pack(side='right', fill='y')
tree.configure(yscrollcommand=vsb.set)

tree.pack(fill='both', expand=True)

# Label untuk menampilkan total keseluruhan harga barang belanjaan
total_label = tk.Label(window, text="", font='calibri 24')
total_label.pack()

# Memulai GUI loop
window.mainloop()
