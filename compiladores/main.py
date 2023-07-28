import tkinter as tk
from tkinter import scrolledtext
from tkinter import messagebox
import re
import subprocess
import os
from tkinter import ttk

def traducir_a_cplusplus(codigo_pseint):
    # Reemplazar sentencias PSeInt por su equivalente en C++
    codigo_cplusplus = re.sub(r"\bAlgoritmo\b", "#include <iostream>\nusing namespace std;\n\nint main() {", codigo_pseint)
    codigo_cplusplus = re.sub(r"\bDefinir\b", "", codigo_cplusplus)
    codigo_cplusplus = re.sub(r"\bComo\b", "", codigo_cplusplus)
    codigo_cplusplus = re.sub(r"\bLeer\b", "cin >>", codigo_cplusplus)
    codigo_cplusplus = re.sub(r"\bEscribir\b", "cout <<", codigo_cplusplus)
    codigo_cplusplus = re.sub(r"\bFinAlgoritmo\b", "\n\nreturn 0;\n}", codigo_cplusplus)

    # Reemplazar operadores PSeInt por su equivalente en C++
    codigo_cplusplus = re.sub(r"<-", "=", codigo_cplusplus)

    # Reemplazar operaciones matemáticas PSeInt por su equivalente en C++
    codigo_cplusplus = re.sub(r"\bmientras\b", "while", codigo_cplusplus)
    codigo_cplusplus = re.sub(r"\bhacer\b", "do", codigo_cplusplus)
    codigo_cplusplus = re.sub(r"\bfin mientras\b", "while", codigo_cplusplus)
    codigo_cplusplus = re.sub(r"\bsi\b", "if", codigo_cplusplus)
    codigo_cplusplus = re.sub(r"\bsino\b", "else", codigo_cplusplus)
    codigo_cplusplus = re.sub(r"\bfin si\b", "endif", codigo_cplusplus)

    # Suma
    codigo_cplusplus = re.sub(r"\b(?<!\+)num1(?!\+)\s*\+\s*num2\b", "num1 + num2", codigo_cplusplus)
    # Resta
    codigo_cplusplus = re.sub(r"\b(?<!\-)num1(?!\-)\s*\-\s*num2\b", "num1 - num2", codigo_cplusplus)
    # Multiplicación
    codigo_cplusplus = re.sub(r"\bnum1\s*\*\s*num2\b", "num1 * num2", codigo_cplusplus)
    # División
    codigo_cplusplus = re.sub(r"\bnum1\s*/\s*num2\b", "num1 / num2", codigo_cplusplus)

    return codigo_cplusplus

def ejecutar_codigo_cplusplus():
    codigo_cplusplus = txt_codigo_cplusplus.get("1.0", tk.END).strip()

    # Crear un archivo temporal para guardar el código C++
    with open("temp.cpp", "w") as file:
        file.write(codigo_cplusplus)

    # Compilar el código C++
    comando_compilacion = ["g++", "temp.cpp", "-o", "temp"]
    try:
        subprocess.run(comando_compilacion, check=True)
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", "Ocurrió un error al compilar el código: " + str(e))
        return

    # Ejecutar el programa resultante y redirigir la salida a un archivo temporal
    with open("temp_output.txt", "w") as output_file:
        try:
            subprocess.Popen("./temp", stdout=output_file, text=True)
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", "Ocurrió un error al ejecutar el programa: " + str(e))
            return

    # Leer el contenido del archivo temporal con la salida del programa y mostrarlo en una ventana emergente
    with open("temp_output.txt", "r") as output_file:
        resultado = output_file.read()
        ventana_resultado = tk.Toplevel(ventana)
        ventana_resultado.title("Resultado de la ejecución")

        txt_resultado = scrolledtext.ScrolledText(ventana_resultado, width=60, height=10, wrap=tk.WORD)
        txt_resultado.insert(tk.END, resultado)
        txt_resultado.pack(fill=tk.BOTH, expand=True)

        ventana_resultado.mainloop()

    # Eliminar los archivos temporales después de ejecutar el programa
    os.remove("temp.cpp")
    os.remove("temp")
    os.remove("temp_output.txt")

def traducir_codigo_pseint():
    codigo_pseint = txt_codigo_pseint.get("1.0", tk.END).strip()

    # Traducir el código PSeInt a C++
    codigo_cplusplus = traducir_a_cplusplus(codigo_pseint)

    txt_codigo_cplusplus.delete("1.0", tk.END)
    txt_codigo_cplusplus.insert(tk.END, codigo_cplusplus)

ventana = tk.Tk()
ventana.title("Curso: Compiladores")

# Estilos para botones y marcos
style = ttk.Style()
style.configure("TButton", font=("Arial", 12))
style.configure("TFrame", background="#f0f0f0")

frame_entrada = ttk.Frame(ventana)
frame_entrada.pack(pady=10)

lbl_codigo_pseint = ttk.Label(frame_entrada, text="Código en PSeInt:", font=("Arial", 14, "bold"))
lbl_codigo_pseint.pack()

txt_codigo_pseint = scrolledtext.ScrolledText(frame_entrada, width=80, height=15, wrap=tk.WORD, font=("Arial", 12))
txt_codigo_pseint.pack()

frame_salida = ttk.Frame(ventana)
frame_salida.pack(pady=10)

lbl_codigo_cplusplus = ttk.Label(frame_salida, text="Código en C++:", font=("Arial", 14, "bold"))
lbl_codigo_cplusplus.pack()

txt_codigo_cplusplus = scrolledtext.ScrolledText(frame_salida, width=80, height=15, wrap=tk.WORD, font=("Arial", 12))
txt_codigo_cplusplus.pack()

btn_traducir = ttk.Button(ventana, text="Traducir a C++", command=traducir_codigo_pseint)
btn_traducir.pack(pady=5)

btn_ejecutar = ttk.Button(ventana, text="Ejecutar", command=ejecutar_codigo_cplusplus)
btn_ejecutar.pack(pady=5)

def mostrar_acerca_de():
    messagebox.showinfo("Acerca de", "Curso: Compiladores\nVersión 1.0\nAutor: liss")

menu = tk.Menu(ventana)
menu_ayuda = tk.Menu(menu, tearoff=0)
menu_ayuda.add_command(label="Acerca de", command=mostrar_acerca_de)
menu.add_cascade(label="TRADUCTOR DE CODIGO Pseint a C++", menu=menu_ayuda)
ventana.config(menu=menu)

ventana.mainloop()
