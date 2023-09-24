import cv2
import numpy as np

# Fungsi untuk mendeteksi orang berdasarkan warna baju
def detect_person(frame):
    # Konversi frame ke ruang warna HSV
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    # Range warna untuk deteksi baju (disesuaikan dengan preferensi Anda)
    lower_color = np.array([0, 10, 60], dtype="uint8")
    upper_color = np.array([20, 150, 255], dtype="uint8")
    
    # Membuat mask untuk memisahkan warna baju
    color_mask = cv2.inRange(hsv_frame, lower_color, upper_color)
    
    # Proses pemrosesan morfologi untuk membersihkan mask
    kernel = np.ones((5, 5), np.uint8)
    color_mask = cv2.morphologyEx(color_mask, cv2.MORPH_OPEN, kernel)
    
    # Mencari kontur objek yang terdeteksi
    contours, _ = cv2.findContours(color_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    # Mencari kontur dengan luas terbesar
    person_contour = max(contours, key=cv2.contourArea) if contours else None
    
    if person_contour is not None:
        # Mendapatkan bounding box orang
        x, y, w, h = cv2.boundingRect(person_contour)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        
        # Menghitung titik tengah objek
        center_x = x + w // 2
        center_y = y + h // 2
        cv2.circle(frame, (center_x, center_y), 5, (0, 0, 255), -1)
    
    return frame, person_contour, (center_x, center_y)

def create_grid_with_indices(frame):
    # Membagi tinggi dan lebar frame menjadi tiga bagian
    height, width, _ = frame.shape
    part_height = height // 3
    part_width = width // 3
    
    # Menggambar garis vertikal dan horizontal untuk membentuk grid
    for row in range(1, 3):
        cv2.line(frame, (0, part_height * row), (width, part_height * row), (0, 255, 0), 2)
    for col in range(1, 3):
        cv2.line(frame, (part_width * col, 0), (part_width * col, height), (0, 255, 0), 2)
    
    # Menambahkan indeks pada setiap bagian
    font = cv2.FONT_HERSHEY_SIMPLEX
    index = 1
    for row in range(3):
        for col in range(3):
            x = col * part_width + part_width // 3
            y = row * part_height + part_height // 2
            cv2.putText(frame, str(index), (x, y), font, 1, (255, 0, 0), 2, cv2.LINE_AA)
            index += 1
    return frame

# Membuka video dari webcam
cap = cv2.VideoCapture(0)

desired_index = 5  # Ubah indeks yang diinginkan

while True:
    # Membaca frame dari video
    ret, frame = cap.read()
    
    if not ret:
        break
    
    # Memanggil fungsi untuk membuat grid dengan indeks
    grid_frame = create_grid_with_indices(frame)
    
    # Deteksi orang dan jaraknya
    detected_frame, person_contour, person_center = detect_person(frame.copy())  # Membuat salinan frame untuk deteksi
    
    # Mendapatkan tinggi dan lebar frame
    height, width, _ = frame.shape
    part_height = height // 3
    part_width = width // 3
    
    # Menampilkan frame hasil deteksi orang
    cv2.imshow('Person Detection', detected_frame)
    
    # Mendapatkan indeks baris dan kolom berdasarkan posisi tengah objek terdeteksi
    if person_contour is not None:
        x, y, w, h = cv2.boundingRect(person_contour)
        col_index = x // part_width
        row_index = y // part_height
        
        # Menghitung indeks berdasarkan posisi berurutan
        calculated_index = row_index * 3 + col_index + 1
        
        # Menampilkan informasi indeks objek terdeteksi
        print("Objek terdeteksi di grid index:", calculated_index)
        
        # Mengecek apakah objek terdeteksi berada di indeks yang diinginkan
        if calculated_index == desired_index:
            print("Objek terdeteksi di grid yang diinginkan (grid index: {})".format(desired_index))
    
    # Tombol 'q' untuk keluar
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Melepaskan sumber daya
cap.release()
cv2.destroyAllWindows()